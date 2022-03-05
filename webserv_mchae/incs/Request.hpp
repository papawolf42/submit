#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

#include "Libft.hpp"

class Client;
class Location;

typedef enum t_req_status
{
	HEADER_PARSING, 
	BODY_PARSING,
	CHUNKED,
	CHUNKED_BODY,
	CONTENT_BODY
} 			e_req_status;

class Request 
{
	private:
		std::string							m_message;
		std::string							m_body;
		std::string							m_method;
		std::string							m_req_location;
		std::string							m_httpver;
		std::map<std::string, std::string>	m_headersMap;
		e_req_status						m_request_status;
		Client*								m_client;
		size_t								m_remain_body_size;	

	public:
		Request();
		virtual ~Request();
		Request(const Request &copy);
		Request	&operator=(const Request &copy);

		//get
		std::string&						get_m_message();
		std::string&						get_m_body();
		std::string&						get_m_method();
		std::string&						get_m_req_location();
		std::string&						get_m_httpver();
		std::map<std::string, std::string>&	get_m_headersMap();
		e_req_status&						get_m_request_status();
		Client*								get_m_client();
		size_t								get_m_remain_body_size();

		//set
		void	set_m_message(std::string);
		void	set_m_body(std::string);
		void	set_m_method(std::string);
		void	set_m_req_location(std::string);
		void	set_m_httpver(std::string);
		void	set_m_request_status(e_req_status);
		void	set_m_client(Client* client);
		void	set_m_remain_body_size(size_t len);

		bool	parseHeader(void);
		bool	parseBody(void);
		bool	checkValidRequest(void);
		bool	isValidMethod(std::vector<std::string>& methods);
		bool	isValidRequestMaxBodySize(int max_body_size);

		void	initRequest();
};

#endif