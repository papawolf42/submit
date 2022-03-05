#include "../incs/Config.hpp"

Config* Config::m_config = 0;

Config::Config(void)
{
	m_status_codeMap["100"] = "Continue";
	m_status_codeMap["101"] = "Switching Protocols";
	m_status_codeMap["200"] = "OK";
	m_status_codeMap["201"] = "Created";
	m_status_codeMap["202"] = "Accepted";
	m_status_codeMap["203"] = "Non-authoritative Information";
	m_status_codeMap["204"] = "No Content";
	m_status_codeMap["205"] = "Reset Content";
	m_status_codeMap["206"] = "Partial Content";
	m_status_codeMap["300"] = "Multiple Choices";
	m_status_codeMap["301"] = "Moved Permanently";
	m_status_codeMap["302"] = "Found";
	m_status_codeMap["303"] = "See copy";
	m_status_codeMap["304"] = "Not Modified";
	m_status_codeMap["305"] = "Use Proxy";
	m_status_codeMap["307"] = "Temporary Redirect";
	m_status_codeMap["400"] = "Bad Request";
	m_status_codeMap["401"] = "Unauthorized";
	m_status_codeMap["402"] = "Payment Required";
	m_status_codeMap["403"] = "Forbidden";
	m_status_codeMap["404"] = "Not found";
	m_status_codeMap["405"] = "Method Not Allowed";
	m_status_codeMap["406"] = "Not Acceptable";
	m_status_codeMap["407"] = "Proxy Authentication Required";
	m_status_codeMap["408"] = "Required Timeout";
	m_status_codeMap["409"] = "Conflict";
	m_status_codeMap["410"] = "Gone";
	m_status_codeMap["411"] = "Length Required";
	m_status_codeMap["412"] = "Precondition Failed";
	m_status_codeMap["413"] = "Request Entity Too Large";
	m_status_codeMap["414"] = "Request URI Too Long";
	m_status_codeMap["415"] = "Unsupported Media Type";
	m_status_codeMap["416"] = "Requested Range Not Satisfiable";
	m_status_codeMap["417"] = "Expectation Failed";
	m_status_codeMap["418"] = "IM_A_TEAPOT";
	m_status_codeMap["500"] = "Internal Server Error";
	m_status_codeMap["501"] = "Not Implemented";
	m_status_codeMap["502"] = "Bad Gateway";
	m_status_codeMap["503"] = "Service Unavailable";
	m_status_codeMap["504"] = "Gateway Timeout";
	m_status_codeMap["505"] = "HTTP Version Not Supported";
	m_mime_typeMap[".aac"] = "audio/aac";
	m_mime_typeMap[".abw"] = "application/x-abiword";
	m_mime_typeMap[".arc"] = "application/octet-stream";
	m_mime_typeMap[".avi"] = "video/x-msvideo";
	m_mime_typeMap[".azw"] = "application/vnd.amazon.ebook";
	m_mime_typeMap[".bin"] = "application/octet-stream";
	m_mime_typeMap[".bz"] = "application/x-bzip";
	m_mime_typeMap[".bz2"] = "application/x-bzip2";
	m_mime_typeMap[".csh"] = "application/x-csh";
	m_mime_typeMap[".css"] = "text/css";
	m_mime_typeMap[".csv"] = "text/csv";
	m_mime_typeMap[".doc"] = "application/msword";
	m_mime_typeMap[".epub"] = "application/epub+zip";
	m_mime_typeMap[".gif"] = "image/gif";
	m_mime_typeMap[".htm"] = "text/html";
	m_mime_typeMap[".html"] = "text/html";
	m_mime_typeMap[".ico"] = "image/x-icon";
	m_mime_typeMap[".ics"] = "text/calendar";
	m_mime_typeMap[".jar"] = "application/java-archive";
	m_mime_typeMap[".jpeg"] = "image/jpeg";
	m_mime_typeMap[".jpg"] = "image/jpeg";
	m_mime_typeMap[".js"] = "application/js";
	m_mime_typeMap[".json"] = "application/json";
	m_mime_typeMap[".mid"] = "audio/midi";
	m_mime_typeMap[".midi"] = "audio/midi";
	m_mime_typeMap[".mpeg"] = "video/mpeg";
	m_mime_typeMap[".mpkg"] = "application/vnd.apple.installer+xml";
	m_mime_typeMap[".odp"] = "application/vnd.oasis.opendocument.presentation";
	m_mime_typeMap[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	m_mime_typeMap[".odt"] = "application/vnd.oasis.opendocument.text";
	m_mime_typeMap[".oga"] = "audio/ogg";
	m_mime_typeMap[".ogv"] = "video/ogg";
	m_mime_typeMap[".ogx"] = "application/ogg";
	m_mime_typeMap[".pdf"] = "application/pdf";
	m_mime_typeMap[".ppt"] = "application/vnd.ms-powerpoint";
	m_mime_typeMap[".rar"] = "application/x-rar-compressed";
	m_mime_typeMap[".rtf"] = "application/rtf";
	m_mime_typeMap[".sh"] = "application/x-sh";
	m_mime_typeMap[".svg"] = "image/svg+xml";
	m_mime_typeMap[".swf"] = "application/x-shockwave-flash";
	m_mime_typeMap[".tar"] = "application/x-tar";
	m_mime_typeMap[".tif"] = "image/tiff";
	m_mime_typeMap[".tiff"] = "image/tiff";
	m_mime_typeMap[".ttf"] = "application/x-font-ttf";
	m_mime_typeMap[".vsd"] = "application/vnd.visio";
	m_mime_typeMap[".wav"] = "audio/x-wav";
	m_mime_typeMap[".weba"] = "audio/webm";
	m_mime_typeMap[".webm"] = "video/webm";
	m_mime_typeMap[".webp"] = "image/webp";
	m_mime_typeMap[".woff"] = "application/x-font-woff";
	m_mime_typeMap[".xhtml"] = "application/xhtml+xml";
	m_mime_typeMap[".xls"] = "application/vnd.ms-excel";
	m_mime_typeMap[".xml"] = "application/xml";
	m_mime_typeMap[".xul"] = "application/vnd.mozilla.xul+xml";
	m_mime_typeMap[".zip"] = "application/zip";
	m_mime_typeMap[".3gp"] = "video/3gpp audio/3gpp";
	m_mime_typeMap[".3g2"] = "video/3gpp2 audio/3gpp2";
	m_mime_typeMap[".7z"] = "application/x-7z-compressed";
}

Config::~Config(void)
{
	delete m_config;
}

Config::Config(const Config& copy)
{
	*this = copy;
}

Config&	Config::operator=(const Config& copy)
{
	m_webserv			= copy.m_webserv;
	m_server_map		= copy.m_server_map;
	m_mime_typeMap		= copy.m_mime_typeMap;
	m_status_codeMap	= copy.m_status_codeMap;
	return (*this);
}

Config* Config::get_m_config(void)
{
	if (m_config == NULL)
		m_config = new Config();
	return (m_config);
}

Webserv*	Config::get_m_webserv(void)
{
	return (m_webserv);
}

std::map<std::string, Server>&	Config::get_m_server_map(void)
{
	return (m_server_map);
}

std::map<std::string, std::string>&	Config::get_m_mime_typeMap(void)
{
	return (m_mime_typeMap);
}

std::map<std::string, std::string>&	Config::get_m_status_codeMap(void)
{
	return (m_status_codeMap);
}

Server*	Config::get_last_server(void)
{
	std::map<std::string, Server>::iterator	it = m_server_map.end();

	it--;
	return (&(it->second));
}


void	Config::set_m_webserv(Webserv* webserv)
{
	m_webserv = webserv;
}

bool	Config::isValidDirective(std::string directive)
{
	if (directive == "server" ||
		directive == "listen" ||
		directive == "server_name" ||
		directive == "location" ||
		directive == "error_page" ||
		directive == "allowed_methods" ||
		directive == "root" ||
		directive == "index" ||
		directive == "upload_path" ||
		directive == "auto_index" ||
		directive == "request_max_body_size" ||
		directive == "cgi_info" ||
		directive == "return")
		return (true);
	return (false);
}

void	Config::parseConfig(const std::string& path)
{
	std::ifstream	file_stream;
	std::string		buffer;
	std::string		line;

	file_stream.open(path, std::ifstream::in);
	if (file_stream.fail())
		throw ("config file open failure");
	while (getline(file_stream, line))
		buffer = buffer + line + "\n";

	std::vector<std::string> tokens;
	tokenize(buffer, tokens);

	std::vector<std::string>::const_iterator	iter;
	std::vector<std::string>::const_iterator	end = tokens.end();

	int	server_block_index = 0;
	for (iter = tokens.begin(); iter != end; iter++)
	{
		if (*iter++ != "server")
			throw ("config err");
		parseServerBlock(iter, server_block_index);
		server_block_index++;
	}
}

void	Config::tokenize(std::string& buffer, std::vector<std::string>& tokens)
{
	std::string					line;
	std::string					temp;
	std::vector<std::string>	brace;
	std::string::size_type		first;
	std::string::size_type		last;

	while (!buffer.empty())
	{
		last = 0;
		line = ft_getline(buffer);
		while ((first = line.find_first_not_of(" \t", last))				\
				!= std::string::npos)
		{
			if (line[first] == '#')
				break ;
			last = line.find_first_of(" \t", first);
			if (last == std::string::npos)
				last = line.size();
			temp = line.substr(first, last - first);
			if (temp == "{")
				brace.push_back(temp);
			else if (temp == "}")
			{
				if (brace.empty())
					throw ("error in config");
				else
					brace.pop_back();
			}
			if (isValidDirective(temp) && \
				line[line.find_last_not_of(" \t", line.length())] != ';')
			{
				if (temp.compare("location") && temp.compare("server"))
					throw ("error in config");
			}
			if (temp.find(';', temp.length() - 1) != std::string::npos)
			{
				temp.erase(temp.length() - 1);
				tokens.push_back(temp);
				tokens.push_back(";");
			}
			else
				tokens.push_back(temp);
		}
	}
}

void	Config::parseServerBlock(std::vector<std::string>::const_iterator& iter, \
int server_block_index)
{
	std::string	server_name;

	if (*iter != "{")
		throw ("config err");
	while (*(++iter) != "}")
	{
		if (*iter == "server_name")
		{
			iter++;

			server_name = *iter++;
		}
		if (*iter == "listen")
		{
			iter++;

			std::string port = *iter++;
			std::string ip	 = *iter++;
			std::string key	 = ip + ":" + port;
			
			if (get_m_server_map().find(key) != get_m_server_map().end())
			{
				if (get_m_server_map()[key].get_m_server_block_index()		\
					== server_block_index)
					throw ("Duplicated Server Ip:Port");
				while (*(iter + 1) != "server")
					iter++;
				break ;
			}

			get_m_server_map()[key].set_m_ip(ip);
			get_m_server_map()[key].set_m_port(port);
			get_m_server_map()[key].set_m_server_name(server_name);
			get_m_server_map()[key].set_m_server_block_index(server_block_index);
		}
		if (*iter == "location")
		{
			iter++;

			std::string	uri		= *iter++;
			Server		*server	= get_last_server();
			std::map<std::string, Location>&
				location_map = server->get_m_locationMap();

			if (location_map.find(uri) != location_map.end())
				throw ("Duplicated Location Uri");

			location_map[uri].set_m_uri(uri);
			Location&	location = location_map[uri];
			parseLocationBlock(iter, location);
		}
	}
}

void	Config::parseLocationBlock											\
		(std::vector<std::string>::const_iterator& iter, Location& location)
{
	if (*iter != "{")
		throw ("config err");
	while (*(++iter) != "}")
	{
		if (*iter == "error_page")
		{
			iter++;
	
			int ernum = std::atoi((*iter++).c_str());
			location.get_m_error_pages_map()[ernum] = *iter++;
		}
		if (*iter == "allowed_methods")
		{
			iter++;
			std::vector<std::string>	gpd;
			
			gpd.push_back("GET");
			gpd.push_back("POST");
			gpd.push_back("DELETE");

			while (true)
			{
				if (std::find(gpd.begin(), gpd.end(), *iter) == gpd.end())
					break ;
				location.get_m_allowed_methods().push_back(*iter++);
			}
		}
		if (*iter == "root")
		{
			iter++;
			
			location.set_m_root(*iter++);
		}
		if (*iter == "index")
		{
			iter++;

			while(*iter != ";")
				location.get_m_indexes().push_back(*iter++);
		}
		if (*iter == "auto_index")
		{
			iter++;

			if (*iter++ == "on")
				location.set_m_auto_index(true);
			else
				location.set_m_auto_index(false);
		}
		if (*iter == "cgi_info")
		{
			iter++;

			std::string cgikey = *iter++;
			location.get_m_cgi_map()[cgikey] = *iter++;
		}
		if (*iter == "return")
		{
			iter++;
			location.set_m_return_num(std::atoi((*iter++).c_str()));
			location.set_m_return_url(*iter++);
		}
		if (*iter == "request_max_body_size")
		{
			iter++;
			location.set_m_max_body_size(std::atoi((*iter++).c_str()));
		}
	}
}
