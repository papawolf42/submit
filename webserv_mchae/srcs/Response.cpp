#include "Client.hpp"
#include "Response.hpp"

Response::Response(void)
{
	m_return	 = false;
	m_disconnect = false;
	m_message.clear();
	m_resource_path.clear();
	m_location	 = NULL;
	m_cgi_extension.clear();
	m_write_idx	 = 0;
	m_resourceList.clear();
	m_fd_read	 = -1;
	m_fd_write	 = -1;
}

Response::~Response(void)
{
	if (m_fd_read != -1)
		close(m_fd_read);
	if (m_fd_write != -1)
		close(m_fd_write);
}

Response::Response(const Response& copy)
{
	*this = copy;
}

Response&	Response::operator=(const Response& copy)
{
	m_return		= copy.m_return;
	m_disconnect	= copy.m_disconnect;
	m_client		= copy.m_client;
	m_message		= copy.m_message;
	m_resource_path	= copy.m_resource_path;
	m_location		= copy.m_location;

	m_cgi_extension	= copy.m_cgi_extension;
	m_write_idx		= copy.m_write_idx;

	m_fd_read		= copy.m_fd_read;
	m_fd_write		= copy.m_fd_write;
	
	return (*this);
}

bool	Response::get_m_return(void)
{
	return m_return;
}

bool	Response::get_m_disconnect(void)
{
	return m_disconnect;
}

Client*	Response::get_m_client(void)
{
	return m_client;
}

std::string&	Response::get_m_message(void)
{
	return m_message;
}

std::string	Response::get_m_resource_path(void)
{
	return m_resource_path;
}

Location*	Response::get_m_location(void)
{
	return m_location;
}

std::string	Response::get_m_cgi_extension(void)
{
	return m_cgi_extension;
}

size_t	Response::get_m_write_idx(void)
{
	return m_write_idx;
}

int	Response::get_m_fd_read(void)
{
	return m_fd_read;
}

int	Response::get_m_fd_write(void)
{
	return m_fd_write;
}

std::list<Resource *>&	Response::get_m_resourceList(void)
{
	return m_resourceList;
}

void	Response::set_m_return(bool ret)
{
	m_return = ret;
}

void	Response::set_m_disconnect(bool disconnect)
{
	m_disconnect = disconnect;
}

void	Response::set_m_client(Client* client)
{
	m_client = client;
}

void	Response::set_m_message(std::string message)
{
	m_message = message;
}

void	Response::set_m_resource_path(std::string path)
{
	m_resource_path = path;
}

void	Response::set_m_location(Location *location)
{
	m_location = location;
}

void	Response::set_m_cgi_extension(std::string cgi)
{
	m_cgi_extension = cgi;
}

void	Response::set_m_write_idx(size_t idx)
{
	m_write_idx = idx;
}

void	Response::set_m_fd_read(int fd)
{
	m_fd_read = fd;
}

void	Response::set_m_fd_write(int fd)
{
	m_fd_write = fd;
}

void	Response::makeGetResponse(void)
{
	int			fd;
	struct stat	sb;
	size_t		idx;

	if (isDirectory(m_resource_path))
	{
		if (*(--m_resource_path.end()) != '/')
			m_resource_path += '/';

		bool		is_exist = false;
		std::string	pathwithfile;

		std::vector<std::string>::iterator it;
		for (it  = m_location->get_m_indexes().begin();						\
			 it != m_location->get_m_indexes().end(); it++)
		{
			pathwithfile  = m_resource_path + (*it);
			is_exist	  = doExist(pathwithfile);

			if (is_exist == true)
				break ;
		}
		if (is_exist == false && m_location->get_m_auto_index() == true)
			return (makeAutoIndexPage());
		if (is_exist == false)
			return (makeErrorResponse(403));

		m_resource_path = pathwithfile;
	}
	if (!doExist(m_resource_path))
		return (makeErrorResponse(404));
	if ((fd = open(m_resource_path.c_str(), O_RDONLY)) < 0)
		return (makeErrorResponse(403));
	if (fstat(fd, &sb) < 0)
		return (makeErrorResponse(500));

	addStatusLine(200);
	addDate();
	m_message += "Content-Language: ko-kr\r\n";
	m_message += "Connection: Keep-Alive\r\n";
	m_message += "Keep-Alive: timeout=5, max=1000\r\n";

	idx = m_resource_path.find_first_of('/');
	idx = m_resource_path.find_first_of('.', idx);
	if (idx == std::string::npos)
		addContentType(".arc");
	else
		addContentType(m_resource_path.substr(idx));
	m_message += "Content-Length: " + std::to_string((int)sb.st_size) + "\r\n";
	m_message += "\r\n";
	setResource(fd, READ_RESOURCE);
}

void	Response::makePostResponse(void)
{
	std::string	body = m_client->get_m_request().get_m_body();
	if (body.size() == 0)
		return (makeErrorResponse(411));
	if (isDirectory(m_resource_path))
	{
		makeErrorResponse(400);
		return ;
	}

	int	fd;

	if (doExist(m_resource_path))
	{
		if ((fd = open(m_resource_path.c_str(),								\
					   O_WRONLY | O_APPEND, 0777)) < 0)
		{
			makeErrorResponse(403);
			return ;
		}
		addStatusLine(204);
	}
	else
	{
		if ((fd = open(m_resource_path.c_str(),								\
					   O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
		{
			makeErrorResponse(500);
			return ;
		}
		addStatusLine(201);
	}
	addDate();

	struct stat	sb;

	if (fstat(fd, &sb) < 0)
		return (makeErrorResponse(500));
	
	addContentLength(m_client->get_m_request().get_m_body().size());
	addEmptyLine();
	m_message += m_client->get_m_request().get_m_body() + "\r\n";
	setResource(fd, WRITE_RESOURCE);
	m_client->set_m_progress_status(FILE_WRITING);
}

void	Response::makeRedirection(void)
{
	m_message.clear();
	addStatusLine(m_location->get_m_return_num());
	addDate();
	addServer();
	addLocation(m_location->get_m_return_url());
	addEmptyLine();
	
	m_client->set_m_progress_status(MAKE_RESPONSE_DONE);
	set_m_disconnect(true);
}

void	Response::makeDeleteResponse(void)
{
	m_message.clear();
	if (!doExist(m_resource_path))
	{
		makeErrorResponse(404);
		return ;
	}
	if (isDirectory(m_resource_path))
	{
		makeErrorResponse(403);
		return ;
	}

	int	del = unlink(m_resource_path.c_str());

	if (del < 0)
	{
		makeErrorResponse(403);
		return ;
	}
	addStatusLine(204);
	addDate();
	addServer();
	addContentLength(0);
	addEmptyLine();
	m_client->set_m_progress_status(MAKE_RESPONSE_DONE);
}

void	Response::makeErrorResponse(int errorcode)
{
	m_message.clear();
	addStatusLine(errorcode);
	addDate();
	addContentLanguage();
	addServer();
	addContentType(".html");

	if (errorcode == 405)
		addAllowedMethod();
	if (errorcode == 408)
		m_message += "Connection: close\r\n";
	if (m_location->get_m_error_pages_map().count(errorcode) == 0)
		return(addErrorBody(errorcode));

	std::string	resource_path = m_location->get_m_error_pages_map()[errorcode];
	struct stat	sb;
	int			fd;

	if ((fd = open(resource_path.c_str(), O_RDONLY)) < 0)
		return (addErrorBody(errorcode));
	if (fstat(fd, &sb) < 0)
		return (addErrorBody(errorcode));
	addContentLength(int(sb.st_size));
	addEmptyLine();
	setResource(fd, READ_RESOURCE);
}

void	Response::makeAutoIndexPage(void)
{
	m_message.clear();

	addStatusLine(200);
	addContentLanguage();
	addContentType(".html");
	addDate();

	std::string body = "";
	body += "<!DOCTYPE html>\n";
	body += "<html>\n";
	body += "<head>\n";
	body += "</head>\n";
	body += "<body>";
	body += "autoindex page\n\n";
	body += "<br><br>";
	makeFileList(body);
	body += "</body>\n";
	body += "</html>\n";
	addContentLength(body.size());
	addEmptyLine();
	m_message += body;
	m_client->set_m_progress_status(MAKE_RESPONSE_DONE);

}

void	Response::makeFileList(std::string& body)
{
	Request	request = m_client->get_m_request();

	std::string http_host_port = "http://"									\
							   + request.get_m_headersMap()["Host"]			\
							   + request.get_m_req_location();

    if (http_host_port[http_host_port.length()-1] != '/')
        http_host_port += "/";
		
    DIR*			dir		  = NULL;
	struct dirent*	directory = NULL;

	if ((dir = opendir(m_resource_path.c_str())) == NULL)
		return (makeErrorResponse(500));

	while ((directory = readdir(dir)))
	{
		std::string file_name(directory->d_name);
		if (file_name != "." && file_name != "..")
			body += "<a href=" + http_host_port + file_name + " >"			\
				  + file_name + "</a><br>";
	}
	closedir(dir);
}

void	Response::setResource(int res_fd, e_resource_type type, int errornum)
{
	Resource*	res;
	Webserv*	webserv	= Config::get_m_config()->get_m_webserv();
	std::string	body	= m_client->get_m_request().get_m_body();

	if (type == WRITE_RESOURCE)
	{
		res = new Resource(res_fd, body, m_client, WRITE_RESOURCE, errornum);
		m_resourceList.push_back(res);
		webserv->addFdPool(dynamic_cast<FdBase*>(res));
		webserv->change_events(webserv->get_m_change_list(), res_fd,		\
							EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}
	else if (type == READ_RESOURCE)
	{
		res = new Resource(res_fd, m_message, m_client, READ_RESOURCE, errornum);
		m_resourceList.push_back(res);
		webserv->addFdPool(dynamic_cast<FdBase *>(res));
		webserv->change_events(webserv->get_m_change_list(), res_fd,		\
							   EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);  
	}
}

void	Response::initResponse(void)
{
	m_return	 = false;
	m_disconnect = false;
	m_message.clear();
	m_resource_path.clear();
	m_location	 = NULL;
	m_cgi_extension.clear();
	m_write_idx	 = 0;
	m_resourceList.clear();
	m_fd_read	 = -1;
	m_fd_write	 = -1;
}
