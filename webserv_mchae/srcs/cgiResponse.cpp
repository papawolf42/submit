#include "../incs/Client.hpp"
#include "../incs/Response.hpp"

char**	Response::makeCgiEnv(size_t file_len)
{
	char**	ret;
	size_t	idx;

	std::map<std::string, std::string>	cgi_map;
	std::map<std::string, std::string>										\
		&headersMap = m_client->get_m_request().get_m_headersMap();
	std::string&															\
		reqlocation = get_m_client()->get_m_request().get_m_req_location();
	std::string	path_info = reqlocation.substr								\
				(reqlocation.find(m_cgi_extension) + m_cgi_extension.size());
	std::string path_translated = m_resource_path.substr					\
			(0, m_resource_path.find(m_cgi_extension) + m_cgi_extension.size());

	idx = path_info.find('?');
	if (idx != std::string::npos)
		path_info = path_info.substr(0, idx);
	if (path_info == "")
		path_info += '/';
	if (m_client->get_m_request().get_m_method() == "GET")
		cgi_map["CONTENT_LENGTH"] = std::to_string(file_len);
	else
		cgi_map["CONTENT_LENGTH"]												\
			= std::to_string(get_m_client()->get_m_request().get_m_body().size());
	if (headersMap.count("Content-Type") == 1)
		cgi_map["CONTENT_TYPE"] = headersMap["Content-Type"];
	cgi_map["GATEWAY_INTERFACE"] = "CGI/1.1";
	cgi_map["PATH_INFO"] = path_info;
	cgi_map["PATH_TRANSLATED"] = path_translated;
	cgi_map["REMOTE_ADDR"] = m_client->get_m_server()->get_m_ip();
	cgi_map["REQUEST_METHOD"] = m_client->get_m_request().get_m_method();
	if (m_cgi_extension == ".bla")
		cgi_map["REQUEST_URI"] = path_info; // query까지
	else
		cgi_map["REQUEST_URI"] = m_client->get_m_request().get_m_req_location();
	cgi_map["SCRIPT_EXEC"] = m_location->get_m_cgi_map()[m_cgi_extension];
	cgi_map["SERVER_NAME"] = m_client->get_m_server()->get_m_server_name();
	cgi_map["SERVER_PORT"] = m_client->get_m_server()->get_m_port();
	cgi_map["SERVER_PROTOCOL"] = "HTTP/1.1";
	cgi_map["SERVER_SOFTWARE"] = "nginx";
	cgi_map["SCRIPT_FILENAME"] = path_translated;
	cgi_map["REDIRECT_STATUS"]="200";
	cgi_map["SCRIPT_NAME"] = m_location->get_m_cgi_map()[m_cgi_extension];

	for (std::map<std::string, std::string>::iterator						\
			it = headersMap.begin(); it != headersMap.end(); it++)
		cgi_map["HTTP_" + it->first] = it->second;
	if (!(ret = (char**)malloc(sizeof(char*) * (cgi_map.size() + 1))))
		return (NULL);
	
	int i = 0;

	for (std::map<std::string, std::string>::iterator						\
		it = cgi_map.begin(); it != cgi_map.end(); it++)
	{
		ret[i] = strdup((it->first + "=" + it->second).c_str());
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	Response::makeCgiResponse(std::string str)
{
	if (m_client->get_m_progress_status() == MAKE_RESPONSE)
	{
		int read_fds[2];
		int write_fds[2];

		if (m_client->get_m_request().get_m_method() == "POST" && m_cgi_extension == ".php")
		{
			m_client->set_m_cgi_status(CGI_ERROR);
			return (makeErrorResponse(500));
		}

		if (m_client->get_m_cgi_status() == READ_NOT_YET									\
			&& m_client->get_m_request().get_m_method() == "GET" && m_cgi_extension == ".bla")
		{
			int			fd;
			struct stat	sb;

			if (!doExist(m_resource_path))
			{
				m_client->set_m_cgi_status(CGI_ERROR);
				return (makeErrorResponse(404));
			}
			if ((fd = open(m_resource_path.c_str(), O_RDONLY)) < 0)
			{
				m_client->set_m_cgi_status(CGI_ERROR);
				return (makeErrorResponse(403));
			}
			if (fstat(fd, &sb) < 0)
			{
				m_client->set_m_cgi_status(CGI_ERROR);
				return (makeErrorResponse(500));
			}

			setResource(fd, READ_RESOURCE);
			m_client->set_m_cgi_status(READ_DONE);
			return ;
		}
		
		if ((pipe(read_fds)) == -1)
		{
			m_client->set_m_cgi_status(CGI_ERROR);
			return (makeErrorResponse(500));
		}
		if ((pipe(write_fds)) == -1)
		{
			m_client->set_m_cgi_status(CGI_ERROR);
			return (makeErrorResponse(500));
		}
		int pid = fork();
		if (pid == 0)
		{  
			char*	args[3];

			std::string uriuntilparam										\
				= m_resource_path.substr									\
					(0, m_resource_path.find(m_cgi_extension)	\
						+ m_cgi_extension.size());
			args[0] = strdup(m_location->get_m_cgi_map()[m_cgi_extension].c_str());
			args[1] = strdup(uriuntilparam.c_str());
			args[2] = 0;

			char**	cgi_env = makeCgiEnv(str.length());

			dup2(write_fds[0], STDIN_FILENO);
			dup2(read_fds[1], STDOUT_FILENO);
			close(write_fds[0]);
			close(write_fds[1]);
			close(read_fds[0]);
			close(read_fds[1]);

			int ret;
			
			ret = execve(args[0], args, cgi_env);
			exit(ret);
		}
		else if (pid < 0)
		{
			m_client->set_m_cgi_status(CGI_ERROR);
			return (makeErrorResponse(500));
		}
		else 
		{
			close(write_fds[0]);
			close(read_fds[1]);

			m_fd_read = read_fds[0];
			m_fd_write = write_fds[1];

			fcntl(m_fd_write, F_SETFL, O_NONBLOCK);
			if (m_client->get_m_request().get_m_method() == "GET")
				m_client->get_m_request().set_m_body(str);
			setResource(m_fd_write, WRITE_RESOURCE, -1);
			Webserv* testWeb;
			testWeb = Config::get_m_config()->get_m_webserv();

			Resource *res = new Resource(m_fd_read, m_message, m_client,	\
										READ_RESOURCE, -1);
			res->set_m_pid(pid);
			m_resourceList.push_back(res);
			Config::get_m_config()->get_m_webserv()->addFdPool(res);
			Config::get_m_config()->get_m_webserv()->change_events			\
				(Config::get_m_config()->get_m_webserv()->get_m_change_list(), \
				m_fd_read, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
			m_client->set_m_progress_status(FILE_WRITING);
			m_client->set_m_cgi_status(READ_NOT_YET);
		}
	}
	else if (m_client->get_m_progress_status() == FILE_READ_DONE)
	{
		std::string read_result = m_message.substr();
		m_message.clear();

		read_result.erase(0, read_result.find("Status:"));
		size_t status_idx1 = read_result.find("Status: ") + 8;
		size_t status_idx2 = read_result.find("\r\n", status_idx1);
		
		m_message += "HTTP/1.1 "											\
				+ read_result.substr(status_idx1, status_idx2 - status_idx1) \
				+ "\r\n";
		addDate();
		addContentLanguage();
		size_t body_size													\
				= read_result.substr(read_result.find("\r\n\r\n") + 4).size();
		addContentLength(body_size);
		m_message += read_result;
		m_client->set_m_progress_status(MAKE_RESPONSE_DONE);
		if (m_client->get_m_request().get_m_method() == "POST")
		{
			int res_fd;
			if ((res_fd = open(m_resource_path.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0777)) < 0)
			{
				m_client->set_m_cgi_status(CGI_ERROR);
				return (makeErrorResponse(403));
			}
			Resource*	res;
			Webserv*	webserv	= Config::get_m_config()->get_m_webserv();
			std::string	body	= read_result.substr(read_result.find("\r\n\r\n") + 4);

			res = new Resource(res_fd, body, m_client, WRITE_RESOURCE, -1);
			m_resourceList.push_back(res);
			webserv->addFdPool(dynamic_cast<FdBase*>(res));
			webserv->change_events(webserv->get_m_change_list(), res_fd,		\
								EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
			res->is_cgi_post = true;
		}
	}
}
