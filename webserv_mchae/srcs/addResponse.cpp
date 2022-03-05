#include "../incs/Client.hpp"
#include "../incs/Response.hpp"
#include "../incs/Config.hpp"

bool	Response::isDirectory(std::string path)
{
	struct stat	info;

	if (stat(path.c_str(), &info) != 0)
		return (false);
	else if (info.st_mode & S_IFDIR)
		return (true);
	else
		return (false);
}

bool	Response::doExist(std::string path)
{
	struct stat info;

	return (stat(path.c_str(), &info) == 0);
}

void	Response::addStatusLine(int status)
{
	std::string	statuscode;
	std::string codemsg;

	statuscode	= std::to_string(status);
	codemsg		= Config::get_m_config()->get_m_status_codeMap()[statuscode];
	m_message += "HTTP/1.1 " + statuscode + " " + codemsg + "\r\n";
}

void	Response::addDate(void)
{
	time_t		rawtime;
	struct tm*	timeinfo;
	char		buff[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buff, 80, "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
	m_message += "Date: " + std::string(buff) + "\r\n";
}

void	Response::addContentLanguage(void)
{
	m_message += "Content-Language: ko-kr\r\n";
}

void	Response::addContentType(std::string type)
{
	std::string contenttype = "";
	if (Config::get_m_config()->get_m_mime_typeMap().count(type) == 0)
		contenttype = "application/octet-stream";
	else
		contenttype = Config::get_m_config()->get_m_mime_typeMap()[type];
	m_message += "Content-Type: " + contenttype + "\r\n";
}

void	Response::addContentLength(int size)
{
	m_message += "Content-Length: " + std::to_string(size) + "\r\n";
}

void	Response::addEmptyLine(void)
{
	m_message += "\r\n";
}

void	Response::addErrorBody(int error)
{
	std::string body = "";
	
	body += "<!DOCTYPE html>\n";
	body += "<html>\n";
	body += "<head>\n";
	body += "</head>\n";
	body += "<body>";
	body += std::to_string(error);
	body += "</body>\n";
	body += "</html>\n";
	addContentLength(body.size());
	addEmptyLine();
	m_message += body;
	m_client->set_m_progress_status(MAKE_RESPONSE_DONE);
}

void	Response::addServer(void)
{
	std::string server_name = m_client->get_m_server()->get_m_server_name();

	m_message += "Server: " + server_name + "\r\n";
}

void 	Response::addLocation(std::string& url)
{
	m_message += "Location: " + url + "\r\n";

}

void	Response::addAllowedMethod(void)
{
	std::string method = "";
	for (std::vector<std::string>::iterator									\
		it = m_location->get_m_allowed_methods().begin();					\
		it != m_location->get_m_allowed_methods().end();					\
		it++)
		method = method + *it + ' ';
	m_message += "Allowed: " + method + "\r\n";
}
