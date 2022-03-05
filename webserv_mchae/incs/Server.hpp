#ifndef SERVER_HPP
# define SERVER_HPP

#include "FdBase.hpp"
#include "Location.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>

class Server : public FdBase
{
private:
	int								m_server_block_index;
	std::string						m_server_name;
	std::string						m_ip;
	std::string						m_port;
	std::map<std::string, Location>	m_locationMap;

public:
	Server(void);
	Server(const Server &copy);
	virtual ~Server(void);
	Server	&operator=(const Server &copy);

	void	set_m_server_block_index(int server_block_index);
	void	set_m_server_name(std::string server_name);
	void	set_m_ip(std::string ip);
	void	set_m_port(std::string port);

	int								get_m_server_block_index(void);
	const std::string				&get_m_server_name(void) const;
	const std::string				&get_m_ip(void) const;
	const std::string				&get_m_port(void) const;
	std::map<std::string, Location>	&get_m_locationMap();
	
	Location&	getPerfectLocation(std::string &uri);
};

std::ostream&	operator<<(std::ostream &o, Server &server);

#endif