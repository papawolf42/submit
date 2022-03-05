#include "../incs/Client.hpp"

Client::Client(void)
{
	m_server			= 0;
	m_progress_status	= REQUEST_RECEIVING;
	m_fd_type			= FD_CLIENT;
	m_fd				= -1;
	m_cgi_status		= READ_NOT_YET;
	
	m_request.set_m_client(this);
	m_response.set_m_client(this);
}

Client::Client(Server* server, int clinet_fd)
{
	m_server			= server;
	m_progress_status	= REQUEST_RECEIVING;
	m_fd_type			= FD_CLIENT;
	m_fd				= clinet_fd;
	m_cgi_status		= READ_NOT_YET;

	m_request.set_m_client(this);
	m_response.set_m_client(this);
}

Client::~Client(void)
{}

Client::Client(const Client& copy)
{
	*this = copy;
}

Client&	Client::operator=(const Client& copy)
{
	m_server			= copy.m_server;
	m_progress_status	= copy.m_progress_status;
	m_fd_type			= copy.m_fd_type;
	m_fd				= copy.m_fd;
	m_cgi_status		= copy.m_cgi_status;
	
	return (*this);
}

Request&	Client::get_m_request(void)
{
	return (m_request);
}

Response&	Client::get_m_response(void)
{
	return (m_response);
}

e_progress_status&	Client::get_m_progress_status(void)
{
	return (m_progress_status);
}

Server*	Client::get_m_server(void)
{
	return (m_server);
}

e_cgi_status	Client::get_m_cgi_status(void)
{
	return (m_cgi_status);
}

void	Client::set_m_cgi_status(e_cgi_status cgi_status)
{
	m_cgi_status = cgi_status;
}

void	Client::set_m_progress_status(e_progress_status c_progress_status)
{
	m_progress_status = c_progress_status;
}

void	Client::appendRequestMessage(std::string newstr)
{
	get_m_request().get_m_message() += newstr;
}

bool	Client::parseRequest(void)
{
	if (m_request.get_m_request_status() == HEADER_PARSING)
	{
		std::size_t idx = m_request.get_m_message().find("\r\n\r\n");
		if (idx == std::string::npos)
			return false;
		m_request.parseHeader();
		m_request.set_m_request_status(BODY_PARSING);
	}
	if (m_request.get_m_request_status() == BODY_PARSING)
	{
		if ((m_request.get_m_headersMap().count("Transfer-Encoding") == 1) && \
			(m_request.get_m_headersMap()["Transfer-Encoding"] == "chunked"))
		{
			m_request.set_m_request_status(CHUNKED);
			return (m_request.parseBody());
		}
		else if (m_request.get_m_headersMap().count("Content-Length"))
		{
			m_request.set_m_remain_body_size								\
				(atoi(m_request.get_m_headersMap()["Content-Length"].c_str()));
			if (m_request.get_m_remain_body_size() == 0)
				return (m_request.checkValidRequest());
			m_request.set_m_request_status(CONTENT_BODY);
			return (m_request.parseBody());
		}
		else
			return (m_request.checkValidRequest());
	}
	
	return (m_request.parseBody());
}

void	Client::makeResponse(void)
{
	if(m_request.get_m_method() == "DELETE")
	{
		if (get_m_progress_status() == MAKE_RESPONSE)
			m_response.makeDeleteResponse();
		else if (get_m_progress_status() == FILE_READ_DONE)
			set_m_progress_status(MAKE_RESPONSE_DONE);
		return ;
	}
    if(m_response.get_m_cgi_extension() != "" && get_m_cgi_status() != CGI_ERROR)
        return (m_response.makeCgiResponse());
    if (m_response.get_m_return()) 
        return (m_response.makeRedirection());
    if (m_request.get_m_method() == "GET")
    {
		if (get_m_progress_status() == MAKE_RESPONSE)
			m_response.makeGetResponse();
		else if (get_m_progress_status() == FILE_READ_DONE)
			set_m_progress_status(MAKE_RESPONSE_DONE);
		return ;
	}
	if (m_request.get_m_method() == "POST")
	{
		if (get_m_progress_status() == MAKE_RESPONSE)
			m_response.makePostResponse();
		else if (get_m_progress_status() == FILE_WRITE_DONE)
			set_m_progress_status(MAKE_RESPONSE_DONE);
	}
}

void	Client::initRequestAndResponse(void)
{
	m_request.initRequest();
	m_response.initResponse();
}
