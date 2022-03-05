#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "FdBase.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "Server.hpp"

class Server;

typedef enum	t_progress_status
{
	REQUEST_RECEIVING,
	MAKE_RESPONSE,
	FILE_READING,
	FILE_READ_DONE,
	FILE_WRITING,
	FILE_WRITE_DONE,
	MAKE_RESPONSE_DONE
}				e_progress_status;

typedef enum	t_cgi_status
{
	READ_NOT_YET,
	READ_DONE,
	CGI_ERROR
}				e_cgi_status;

class Client : public FdBase
{
	private:
		Request				m_request;
		Response			m_response;
		e_progress_status	m_progress_status;
		Server*				m_server;
		e_cgi_status		m_cgi_status;

	public:
		Client(void);
		Client(Server* server, int clinet_fd);
		Client(const Client& copy);
		virtual	~Client(void);
		Client&	operator=(const Client& copy);

		Request&			get_m_request(void);
		Response&			get_m_response(void);
		e_progress_status&	get_m_progress_status(void);
		Server*				get_m_server(void);
		e_cgi_status		get_m_cgi_status(void);

		void	set_m_cgi_status(e_cgi_status cgi_status);
		void	set_m_progress_status(e_progress_status c_progress_status);

		void	appendRequestMessage(std::string newstr);
		bool	parseRequest(void);
		void	makeResponse(void);
		void	initRequestAndResponse(void);
};

#endif