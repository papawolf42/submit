#include "Server.hpp"

Server::Server(void)
{
	m_server_block_index = -1;
	m_fd_type			 = FD_SERVER;
	m_port	 			 = -1;
}

Server::Server(const Server &copy)
{
	m_server_block_index = copy.m_server_block_index;
	m_fd				 = copy.m_fd;
	m_fd_type			 = copy.m_fd_type;
	m_ip				 = copy.m_ip;
	m_port				 = copy.m_port;
	m_server_name		 = copy.m_server_name;
	m_locationMap.insert(copy.m_locationMap.begin(), copy.m_locationMap.end());
}
Server::~Server(void)
{}

Server	&Server::operator=(const Server &copy)
{
	m_server_block_index = copy.m_server_block_index;
	m_fd				 = copy.m_fd;
	m_fd_type			 = copy.m_fd_type;
	m_ip				 = copy.m_ip;
	m_port				 = copy.m_port;
	m_server_name		 = copy.m_server_name;
	if (!m_locationMap.empty())
		m_locationMap.clear();
	m_locationMap.insert(copy.m_locationMap.begin(), copy.m_locationMap.end());

	return (*this);
}

void	Server::set_m_server_block_index(int server_block_index)
{
	m_server_block_index = server_block_index;
}

void	Server::set_m_server_name(std::string server_name)
{
	m_server_name = server_name;
}

void	Server::set_m_ip(std::string ip)
{
	m_ip = ip;
}

void	Server::set_m_port(std::string port)
{
	m_port = port;
}

int	Server::get_m_server_block_index(void)
{
	return (m_server_block_index);
}

const std::string&	Server::get_m_server_name(void) const
{
	return (m_server_name);
}

const std::string&	Server::get_m_ip(void) const
{
	return (m_ip);
}

const std::string&	Server::get_m_port(void) const
{
	return (m_port);
}

std::map<std::string, Location>&	Server::get_m_locationMap()
{
	return (m_locationMap);
}

std::ostream&	operator<<(std::ostream &o, Server &server)
{
	o << "==========Server=========="				   << std::endl;
	o << "IP: " << server.get_m_ip()				   << std::endl;
	o << "Port: " << server.get_m_port()			   << std::endl;
	o << "Server_name: " << server.get_m_server_name() << std::endl;

	o << "----------Location----------"				   << std::endl;

	for (std::map<std::string, Location>::iterator							\
		 iter  = server.get_m_locationMap().begin();						\
		 iter != server.get_m_locationMap().end(); iter++)
	{
		o << "maxbody: " << iter->second.get_m_max_body_size()	<< std::endl;
		o << "returnNum: " << iter->second.get_m_return_num()	<< std::endl;
		o << "autoindex: " << iter->second.get_m_auto_index()	<< std::endl;
		o << "root: " << iter->second.get_m_root()				<< std::endl;
		o << "Uri: " << iter->second.get_m_uri()				<< std::endl;
		o << "returnUrl: " << iter->second.get_m_return_url()	<< std::endl;
		o << "AllowedMethods: ";

		for (std::vector<std::string>::iterator								\
			 i  = iter->second.get_m_allowed_methods().begin();				\
			 i != iter->second.get_m_allowed_methods().end(); i++)
			o << *i << " ";
		o << std::endl;
		o << "Indexs: ";

		for (std::vector<std::string>::iterator								\
			 i  = iter->second.get_m_indexes().begin();						\
			 i != iter->second.get_m_indexes().end(); i++)
			o << *i << " ";
		o << std::endl;
		o << "ErrorPages : ";

		for (std::map<int, std::string>::iterator							\
			 i  = iter->second.get_m_error_pages_map().begin();					\
			 i != iter->second.get_m_error_pages_map().end(); i++)
			o << (i->first) << " "<< (i->second) << " ";
		o << std::endl;
		o << "Cgis : ";

		for (std::map<std::string, std::string>::iterator					\
			 i  = iter->second.get_m_cgi_map().begin();							\
			 i != iter->second.get_m_cgi_map().end(); i++)
			o << (i->first) << " "<< (i->second) << " ";
		o << std::endl;
	}
	o << std::endl;

	return o;
}

Location	&Server::getPerfectLocation(std::string &uri)
{
	Location*	ret = &(m_locationMap["/"]);
	std::string	key = "";

	for (std::string::const_iterator										\
		 iter = uri.begin(); iter != uri.end(); iter++)
	{
		key += *iter;
		if (*iter == '/')
		{
			if (m_locationMap.find(key) == m_locationMap.end())
				return (*ret);
			else
				ret = &(m_locationMap[key]);
		}
	}
	if ( *(--key.end()) != '/')
	{
		key += '/';
		if (m_locationMap.find(key) != m_locationMap.end())
		{
			uri = key;
			return (m_locationMap[key]);
		}
	}
	return (*ret);
}