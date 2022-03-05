#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include "../incs/Config.hpp"
#include "../incs/Server.hpp"
#include "../incs/Location.hpp"
#include "../incs/FdBase.hpp"
#include "../incs/Client.hpp"
#include "../incs/Resource.hpp"

# define MAX_FD_SIZE 1024
# define BUFSIZE 1025

class Server;
class Location;
class Config;

class Webserv 
{
	private:
		int							m_kq;
		struct kevent				m_return_events[1024];
		std::vector<struct kevent>	m_change_list;
		std::vector<FdBase *>		m_fd_pool;

	public:
		Webserv(void);
		Webserv(const Webserv &copy);
		virtual ~Webserv();
		Webserv	&operator=(const Webserv &copy);

		void	initServer(void);
		void	startServer(void);
		void	handleReadEvent(int fd);
		int		addNewClient(int fd);
		int		handleReadClientEvent(int fd);
		int		handleReadResource(int fd);
		void	handleWriteEvent(int fd);
		int		sendResponse(int fd, Client* clnt);
		int		writeResource(int fd);
		void	change_events(std::vector<struct kevent> &change_list,		\
							  uintptr_t ident, int16_t filter,				\
							  uint16_t flags, uint32_t fflags,				\
							  intptr_t data, void *udata);

		std::vector<struct kevent>&	get_m_change_list(void);
		void						addFdPool(FdBase* res);
		void						deleteFdPool(FdBase *res);
		void						signalExit(void);
};

#endif