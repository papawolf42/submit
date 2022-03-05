#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>

// #include "Client.hpp"
#include "Config.hpp"
#include "Location.hpp"
#include "Resource.hpp"


class Location;
class Client;


class Response 
{
	private:
		bool	m_return;
		bool	m_disconnect;
		Client*	m_client;

		std::string	m_message;
		std::string	m_resource_path;
		Location*	m_location;

		std::string				m_cgi_extension;
		size_t					m_write_idx;
		std::list<Resource *>	m_resourceList;

		int	m_fd_read;
		int	m_fd_write;

	public:
		Response();
		virtual ~Response();
		Response(const Response &copy);
		Response &operator=(const Response &copy);

		//get
		bool					get_m_return();
		bool					get_m_disconnect();
		Client*					get_m_client();
		std::string&			get_m_message();
		std::string				get_m_resource_path();
		Location*				get_m_location();
		std::string				get_m_cgi_extension();
		size_t					get_m_write_idx();
		int						get_m_fd_read();
		int						get_m_fd_write();
		std::list<Resource *>&	get_m_resourceList();

		//set
		void	set_m_return(bool);
		void	set_m_disconnect(bool);
		void	set_m_client(Client* client);
		void	set_m_message(std::string message);
		void	set_m_resource_path(std::string path);
		void	set_m_location(Location *location);
		void	set_m_cgi_extension(std::string cgi);
		void	set_m_write_idx(size_t idx);
		void	set_m_fd_read(int fd);
		void	set_m_fd_write(int fd);
		void	setResource(int res_fd, e_resource_type type, int errornum =-1);

		void	makeCgiResponse(std::string str = "");
		void	makeGetResponse(void);
		void	makePostResponse(void);
		void	makeRedirection(void);
		void	makeDeleteResponse(void);
		void	makeErrorResponse(int err); // 헤더 넣고 바디에 addErrorBody(errorcode) or setResource
		void	makeAutoIndexPage(void);
		void	makeFileList(std::string &body);

		char**	makeCgiEnv(size_t file_len);

		void	addStatusLine(int err);
		void	addDate();
		void	addContentLanguage();
		void	addContentType(std::string type);
		void	addContentLength(int size);
		void	addAllowedMethod();
		void	addEmptyLine();
		void	addErrorBody(int errorcode); // 다양한 errorcode가 들어간 body 만들어서 return
		void	addDefaultErrorBody(std::string& message, int errorcode);  // 실제 errorcode body 만드는 함수
		void	addServer();
		void	addLocation(std::string &url);

		bool	isDirectory(std::string path);
		bool	doExist(std::string path);

		void	initResponse();
};

#endif