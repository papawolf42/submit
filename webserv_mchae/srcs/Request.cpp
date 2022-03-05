#include "Request.hpp"
#include "Config.hpp"

Request::Request()
{
	m_request_status = HEADER_PARSING;
}

Request::~Request()
{}

Request::Request(const Request& copy)
{
	*this = copy;
}

Request& Request::operator=(const Request& copy)
{
	m_message		= copy.m_message;
	m_body			= copy.m_body;
	m_method		= copy.m_method;
	m_req_location	= copy.m_req_location;
	m_httpver		= copy.m_httpver;
	
	for (std::map<std::string, std::string>::const_iterator					\
			it = copy.m_headersMap.begin();								\
			it != copy.m_headersMap.end(); it++)
		m_headersMap[it->first] = it->second;
		
	return *this;
}

std::string&	Request::get_m_message()
{
	return m_message;
}

std::string&	Request::get_m_body()
{
	return m_body;
}

std::string&	Request::get_m_method()
{
	return m_method;
}

std::string&	Request::get_m_req_location()
{
	return m_req_location;
}

std::string&	Request::get_m_httpver()
{
	return m_httpver;
}

std::map<std::string, std::string>&	Request::get_m_headersMap()
{
	return m_headersMap;
}

e_req_status&	Request::get_m_request_status()
{
	return m_request_status;
}

Client*	Request::get_m_client()
{
	return m_client;
}

size_t	Request::get_m_remain_body_size()
{
	return m_remain_body_size;
}


void	Request::set_m_message(std::string message)
{
	m_message = message;
}

void	Request::set_m_body(std::string body)
{
	m_body = body;
}

void	Request::set_m_method(std::string method)
{
	m_method = method;
}

void	Request::set_m_req_location(std::string location)
{
	m_req_location = location;
}

void	Request::set_m_httpver(std::string httpver)
{
	m_httpver = httpver;
}

void	Request::set_m_request_status(e_req_status status)
{
	m_request_status = status;
}

void	Request::set_m_client(Client* client)
{
	m_client = client;
}

void	Request::set_m_remain_body_size(size_t len)
{
	m_remain_body_size = len;
}

std::string trim(std::string& str)
{
	std::size_t first = str.find_first_not_of(' ');

	if (std::string::npos == first)
		return (str);

	std::size_t last = str.find_last_not_of(' ');

	return str.substr(first, (last - first + 1));
}

bool	Request::parseHeader(void)
{
	std::size_t					found	  = m_message.find("\r\n");
	std::string					firstline = m_message.substr(0, found);
	std::vector<std::string>	vFirsts;

	ft_split(firstline, " ", vFirsts);
	set_m_method(vFirsts[0]);
	set_m_req_location(vFirsts[1]);
	set_m_httpver(vFirsts[2]);

	if (m_message.length() >= found+2)
		set_m_message(m_message.substr(found+2));
	else
		set_m_message("");

	found								   = m_message.find("\r\n\r\n");
	std::string					tempheader = m_message.substr(0, found);
	std::vector<std::string>	tempVHeaders;

	ft_split(tempheader, "\r\n", tempVHeaders);
	for (std::vector<std::string>::iterator it = tempVHeaders.begin();		\
											it != tempVHeaders.end(); it++)
	{
		std::string	line  = *it;
		std::size_t	idx   = line.find(':');
		std::string	key   = line.substr(0, idx);
		std::string	value = "";
		
		if (line.length() != (found+1))
			value = line.substr(idx+1);
		m_headersMap[trim(key)] = trim(value);
	}
	if (m_message.length() >= found+4)
		set_m_message(m_message.substr(found+4));
	else
		set_m_message("");

	return true;
}

bool	Request::parseBody(void)
{
	if (m_request_status == CONTENT_BODY)
	{
		if (m_remain_body_size <= m_message.length())
		{
			m_body.append(m_message.substr(0, m_remain_body_size));
			m_message.erase(0, m_remain_body_size);
			m_remain_body_size = 0;
			return (checkValidRequest());
		}
		return (false);
	}
	else if (m_request_status == CHUNKED)
	{
		size_t				tmp;
		std::stringstream	ss;
		std::size_t			found = m_message.find("\r\n");

		if (found == std::string::npos)
			return false;
		else
		{
			ss << std::hex << m_message.substr(0, found);
			ss >> tmp;
			
			m_remain_body_size	= tmp + 2;
			m_message			= m_message.substr(found+2);
			m_request_status	= CHUNKED_BODY;
			
			return (parseBody());
		}
	}
	else if (CHUNKED_BODY)
	{
		if (m_remain_body_size <= m_message.size())
		{
			size_t oldbodysize = m_body.size();
			
			m_body.append(m_message.substr(0, m_remain_body_size -2));
			m_message.erase(0, m_remain_body_size);

			m_remain_body_size = 0;
			
			if (m_body.size() == oldbodysize)
			{
				return (checkValidRequest());
			}
			
			m_request_status = CHUNKED;
			
			return (parseBody());
		}
	}
	return (checkValidRequest());
}

bool Request::checkValidRequest(void)
{
	Server*		server	 = m_client->get_m_server();
	Location&	loc		 = server->getPerfectLocation(m_req_location);
	Response&	response = m_client->get_m_response();

	response.set_m_location(&loc);

	if (isValidMethod(loc.get_m_allowed_methods()) == false)
	{
		m_client->set_m_progress_status(MAKE_RESPONSE);
		response.makeErrorResponse(405);
		
		return (false);
	}
	if (isValidRequestMaxBodySize(loc.get_m_max_body_size()) == false)
	{
		m_client->set_m_progress_status(MAKE_RESPONSE);
		response.makeErrorResponse(413);
		
		return (false);
	}

	std::string	root		  = loc.get_m_root();
	std::string	uri			  = loc.get_m_uri();
	std::string	resource_path = root + m_req_location.substr(uri.size());

	response.set_m_resource_path(resource_path);

	std::map<std::string, std::string>::iterator iter;
	for (iter  = loc.get_m_cgi_map().begin();									\
		 iter != loc.get_m_cgi_map().end(); iter++)
	{
		if (resource_path.find(iter->first) != std::string::npos)
		{
			response.set_m_cgi_extension(iter->first);

			break ;
		}
	}
	if (loc.get_m_return_num() != -1)
		response.set_m_return(true);

	set_m_request_status(HEADER_PARSING);
	
	return true;
}

bool	Request::isValidMethod(std::vector<std::string>& methods)
{
	bool	isAllowedCheckOkay = false;

	std::vector<std::string>::iterator	iter;
	for (iter  = methods.begin();							\
		 iter != methods.end(); iter++)
	{
		if (m_method == *iter)
		{
			isAllowedCheckOkay = true;
			
			break ;
		}
	}
	if (isAllowedCheckOkay != true)
		return (false);

	return (true);
}

bool	Request::isValidRequestMaxBodySize(int max_body_size)
{
	if (m_body.size() > (size_t)(max_body_size))
		return (false);

	return (true);
}

void	Request::initRequest()
{
	m_message.clear();
	m_body.clear();
	m_method.clear();
	m_req_location.clear();
	m_httpver.clear();
	m_headersMap.clear();
	m_request_status	= HEADER_PARSING;
	m_remain_body_size	= 0;
}