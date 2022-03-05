#ifndef LOCATION_HPP
# define LOCATION_HPP

#include <string>
#include <map>
#include <vector>
#include <limits>

class Location
{
	private:
		int									m_max_body_size;
		int									m_return_num;
		bool								m_auto_index;
		std::string							m_root;
		std::string							m_uri;
		std::string							m_return_url;
		std::vector<std::string>			m_allowed_methods;
		std::vector<std::string>			m_indexes;
		std::map<int, std::string>			m_error_pages_map;
		std::map<std::string, std::string>	m_cgi_map;
	
	public:
		Location(void);
		virtual	~Location(void);
		Location(const Location& src);
		Location&	operator=(const Location& src);

		int&								get_m_max_body_size(void);
		bool&								get_m_auto_index(void);
		std::string&						get_m_uri(void);
		std::string&						get_m_root(void);
		int&								get_m_return_num(void);
		std::string&						get_m_return_url(void);
		std::vector<std::string>&			get_m_allowed_methods(void);
		std::vector<std::string>&			get_m_indexes(void);
		std::map<int, std::string>&			get_m_error_pages_map(void);
		std::map<std::string, std::string>&	get_m_cgi_map(void);

		void	set_m_max_body_size(int size);
		void	set_m_return_num(int return_num);
		void	set_m_auto_index(bool auto_index);
		void	set_m_root(std::string root);
		void	set_m_uri(std::string uri);
		void	set_m_return_url(std::string return_url);
};

#endif