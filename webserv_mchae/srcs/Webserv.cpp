#include "Webserv.hpp"

Webserv::Webserv(void)
{
	m_fd_pool.resize(MAX_FD_SIZE, NULL);
}

Webserv::Webserv(const Webserv &copy)
{
	*this = copy;
}

Webserv::~Webserv(void)
{
}

Webserv &Webserv::operator=(const Webserv &copy)
{
	m_kq	  = copy.m_kq;
	m_fd_pool = copy.m_fd_pool;
	for (int i = 0; i < MAX_FD_SIZE; i++)
		m_return_events[i] = copy.m_return_events[i];

	return (*this);
}

static void error_handling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void	Webserv::change_events(std::vector<struct kevent> &change_list,		\
							uintptr_t ident, int16_t filter, uint16_t flags,\
							uint32_t fflags, intptr_t data, void *udata)
{
	struct kevent	temp_event;

	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	change_list.push_back(temp_event);
}

void	Webserv::initServer(void)
{
	Config*	config = Config::get_m_config();

	if((m_kq = kqueue()) == -1)
		error_handling("kqueue() error");

	for (std::map<std::string, Server>::iterator							\
		 it  = config->get_m_server_map().begin();							\
		 it != config->get_m_server_map().end();							\
		 it++)
	{
		int					serv_sock;
		struct sockaddr_in	serv_addr;

		serv_sock = socket(PF_INET, SOCK_STREAM, 0);
		it->second.set_m_fd(serv_sock);
		
		if (serv_sock == -1)
			error_handling("socket() error");

		int	opt = 1;

		setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family	  = AF_INET;

		const char*	ip	 = it->second.get_m_ip().c_str();
		const char*	port = it->second.get_m_port().c_str();

		serv_addr.sin_addr.s_addr = inet_addr(ip);
		serv_addr.sin_port		  = htons(std::atoi(port));

		if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)\
				) == -1)
			error_handling("bind() error");
		if (listen(serv_sock, SOMAXCONN) == -1)
			error_handling("listen() error");

		fcntl(serv_sock, F_SETFL, O_NONBLOCK);
		change_events(m_change_list, serv_sock, EVFILT_READ,				\
					  EV_ADD | EV_ENABLE, 0, 0, NULL);
		m_fd_pool[serv_sock] = &(it->second);
	}
}

void	Webserv::startServer(void)
{
	int				new_events;
	struct kevent*	curr_event;

	while (1)
	{
		new_events = kevent(m_kq, &m_change_list[0], m_change_list.size(),	\
							m_return_events, 1024, NULL);
		if (new_events == -1)
			error_handling("kevent() error\n");
		m_change_list.clear();
		for (int i = 0; i < new_events; i++)
		{
			curr_event = &m_return_events[i];
			if (curr_event->flags & EV_ERROR)
				deleteFdPool(m_fd_pool[curr_event->ident]);
			else if (curr_event->filter == EVFILT_READ)
				handleReadEvent(curr_event->ident);
			else if (curr_event->filter == EVFILT_WRITE)
				handleWriteEvent(curr_event->ident);
		}
	}
}

void	Webserv::handleReadEvent(int fd)
{
	if (m_fd_pool[fd]->get_m_fd_type() == FD_SERVER)
		addNewClient(fd);
	else if (m_fd_pool[fd]->get_m_fd_type() == FD_CLIENT)
		handleReadClientEvent(fd);
	else if (m_fd_pool[fd]->get_m_fd_type() == FD_RESOURCE)
		handleReadResource(fd);
}

int	Webserv::addNewClient(int fd)
{
	int	serv_fd = m_fd_pool[fd]->get_m_fd();
	int	clnt_sock;

	if ((clnt_sock = accept(serv_fd, NULL, NULL)) == -1)
		return (-1);
		
	fcntl(clnt_sock, F_SETFL, O_NONBLOCK);

	change_events(m_change_list, clnt_sock,									\
				  EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	change_events(m_change_list, clnt_sock,									\
				  EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);

	Client*	clnt =															\
		new Client((dynamic_cast<Server *>(m_fd_pool[serv_fd])), clnt_sock);
	
	m_fd_pool[clnt_sock] = clnt;
	
	return (0);
}

int	Webserv::handleReadClientEvent(int fd)
{
	Client	*clnt = dynamic_cast<Client *>(m_fd_pool[fd]);
		
	char	buf[BUFSIZE];
	int		n = 1;
	
	memset(buf, 0, BUFSIZE);

	if ((n = recv(fd, buf, BUFSIZE - 1, 0)) == -1)
	{
		deleteFdPool(m_fd_pool[fd]);
		return (-1);
	}
	if (n == 0)
		deleteFdPool(m_fd_pool[fd]);
	else if (n > 0)
	{
		buf[n] = '\0';
		clnt->appendRequestMessage(buf);
		if (clnt->get_m_progress_status() == REQUEST_RECEIVING && clnt->parseRequest())
		{
			clnt->set_m_progress_status(MAKE_RESPONSE);
			clnt->makeResponse();
		}
	}
	return (0);
}

int	Webserv::handleReadResource(int fd)
{
	Resource*	 rsc = dynamic_cast<Resource *>(m_fd_pool[fd]);
	e_rsc_status ret = rsc->isReady();

	if (ret == READY)
	{
		char			buff[BUFSIZE];
		unsigned long	n = 0;
		
		memset(buff, 0, BUFSIZE);
		
		if ((n = read(fd, buff, BUFSIZE - 1)) < 0)
			return (-1);
		buff[n] = '\0';
		rsc->set_m_raw_data(rsc->get_m_raw_data() + buff);
		rsc->get_m_client()->get_m_response().set_m_message(rsc->get_m_client()->get_m_response().get_m_message() + buff);
		if (n < BUFSIZE - 1)
		{
			if (rsc->get_m_client()->get_m_cgi_status() == READ_DONE)
				rsc->get_m_client()											\
				   ->get_m_response().makeCgiResponse(rsc->get_m_raw_data());
			else
			{
				rsc->get_m_client()->set_m_progress_status(FILE_READ_DONE);
				rsc->get_m_client()->makeResponse();
			}
			deleteFdPool(m_fd_pool[fd]);
		}
	}
	else if (ret == CGI_CRASH)
	{
		rsc->get_m_client()->get_m_response().makeErrorResponse(500);
		deleteFdPool(rsc);
		return (-1);
	}
	return (0);
}

void	Webserv::handleWriteEvent(int fd)
{
	Client*	clnt = dynamic_cast<Client *>(m_fd_pool[fd]);

	if (m_fd_pool[fd]->get_m_fd_type() == FD_CLIENT &&		\
		(clnt->get_m_progress_status() == MAKE_RESPONSE_DONE))// ||
		 //clnt->get_m_progress_status() == REQUEST_RECEIVING))
		sendResponse(fd, clnt);
	else if (m_fd_pool[fd]->get_m_fd_type() == FD_RESOURCE)
		writeResource(fd);
}

int	Webserv::sendResponse(int fd, Client* clnt)
{
	size_t		n;
	Response&	rsp = clnt->get_m_response();
	std::string	message = rsp.get_m_message();

	n = write(fd, message.c_str(), message.length());
	if (n < 0)
		return (-1);
	if (n < rsp.get_m_message().length())
		rsp.get_m_message().erase(0, n);
	else
	{
		if (rsp.get_m_disconnect())
			deleteFdPool(clnt);
		else
		{
			clnt->set_m_progress_status(REQUEST_RECEIVING);
			clnt->set_m_cgi_status(READ_NOT_YET);
			clnt->initRequestAndResponse();
		}
	}
	return (0);
}

int	Webserv::writeResource(int fd)
{
	Resource*	res		 = dynamic_cast<Resource *>(m_fd_pool[fd]);
	size_t		n		 = 0;
	std::string	raw_data = res->get_m_raw_data();
	
	n = write(fd, raw_data.c_str(), raw_data.length());
	if (res->is_cgi_post == true)
	{
		res->is_cgi_post = false;
		deleteFdPool(res);
		return (0);
	}
	if (n < 0)
		return (-1);
	if (n < res->get_m_raw_data().length())
		res->set_m_raw_data(raw_data.erase(0,n));
	else
	{
		res->get_m_client()->set_m_progress_status(FILE_WRITE_DONE);
		res->get_m_client()->makeResponse();
		deleteFdPool(res);
	}
	
	return (0);
}

std::vector<struct kevent>&	Webserv::get_m_change_list(void)
{
	return m_change_list;
}

void	Webserv::addFdPool(FdBase* res)
{
	if (m_fd_pool[res->get_m_fd()] == NULL)
		m_fd_pool[res->get_m_fd()] = res;
}

void	Webserv::deleteFdPool(FdBase* instance)
{
	if (instance == NULL)
		return ;
		
	close(instance->get_m_fd());
	if (instance->get_m_fd_type() == FD_CLIENT)
	{
		Client					*clnt	 = dynamic_cast<Client *>(instance);
		Response&				response = clnt->get_m_response();
		std::list<Resource *>&	rspList  = response.get_m_resourceList();

		if (response.get_m_resourceList().size() > 1)
		{
			for (std::list<Resource *>::iterator 							\
				 it = rspList.begin(); it != rspList.end(); it++)
			{
				if (*it)
					deleteFdPool(dynamic_cast<FdBase*>(*it));
			}
		}
	}
	else if (instance->get_m_fd_type() == FD_RESOURCE)
	{
		Resource*	res  = dynamic_cast<Resource *>(instance);
		Client*		clnt = res->get_m_client();
		Response&	response = clnt->get_m_response();
		if (clnt)
		{
			std::list<Resource *> &rspList = response.get_m_resourceList();
			if (!rspList.empty())
			{
				std::list<Resource *>::iterator
					it = std::find(rspList.begin(), rspList.end(), res);
				if (it != rspList.end())
					rspList.erase(it);
			}
		}
	}
	m_fd_pool[instance->get_m_fd()] = NULL;
	if (instance->get_m_fd_type() != FD_SERVER)
		delete instance;
}

void	Webserv::signalExit(void)
{
	for (std::vector<FdBase*>::iterator it = m_fd_pool.begin();				\
										it != m_fd_pool.end(); it++)
	{
		if (*it != NULL)
			deleteFdPool(*it);
	}
}
