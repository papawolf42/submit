#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <string>
#include <fcntl.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <set>

#include "Server.hpp"
#include "Location.hpp"
#include "Libft.hpp"
#include "Webserv.hpp"

class Server;
class Webserv;

class Config 
{
private:
	Config(const Config& copy);

	Webserv*							m_webserv;
	static Config*						m_config;
	std::map<std::string, Server>		m_server_map;
	std::map<std::string, std::string>	m_mime_typeMap;
	std::map<std::string, std::string>	m_status_codeMap;

public:
	Config(void);
	~Config(void);
	Config&	operator=(const Config& copy);

	void	parseConfig(const std::string& path);
	void	tokenize(std::string& buffer, std::vector<std::string>& tokens);

	Webserv*							get_m_webserv(void);
	static Config*						get_m_config(void);
	std::map<std::string, Server>&		get_m_server_map(void);
	std::map<std::string, std::string>&	get_m_mime_typeMap(void);
	std::map<std::string, std::string>&	get_m_status_codeMap(void);
	Server*								get_last_server(void);

	void	set_m_webserv(Webserv* webserv);

	bool	isValidDirective(std::string directive);
	void	parseServerBlock(std::vector<std::string>::const_iterator& iter, \
							 int server_block_index);
	void	parseLocationBlock												\
		(std::vector<std::string>::const_iterator& iter, Location& location);
};

#endif