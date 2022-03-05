#include "../incs/Location.hpp"

Location::Location(void)
{
	m_max_body_size	= INT_MAX;
	m_auto_index	= false;
	m_return_num	= -1;
}

Location::~Location(void)
{}

Location::Location(const Location& src)
{
	*this = src;
}

Location&	Location::operator=(const Location& src)
{
	m_max_body_size	= src.m_max_body_size;
	m_return_num	= src.m_return_num;
	m_auto_index	= src.m_auto_index;
	m_root			= src.m_root;
	m_uri			= src.m_uri;
	m_return_url	= src.m_return_url;
	m_allowed_methods	= src.m_allowed_methods;
	m_error_pages_map	= src.m_error_pages_map;
	m_cgi_map			= src.m_cgi_map;

	return (*this);
}

int&	Location::get_m_max_body_size(void)
{
	return (m_max_body_size);
}

bool&	Location::get_m_auto_index(void)
{
	return (m_auto_index);
}

std::string&	Location::get_m_uri(void)
{
	return (m_uri);
}

std::string&	Location::get_m_root(void)
{
	return (m_root);
}

int&	Location::get_m_return_num(void)
{
	return (m_return_num);
}

std::string&	Location::get_m_return_url(void)
{
	return (m_return_url);
}

std::vector<std::string>&	Location::get_m_allowed_methods(void)
{
	return (m_allowed_methods);
}

std::vector<std::string>&	Location::get_m_indexes(void)
{
	return (m_indexes);
}

std::map<int, std::string>&	Location::get_m_error_pages_map(void)
{
	return (m_error_pages_map);
}

std::map<std::string, std::string>&	Location::get_m_cgi_map(void)
{
	return (m_cgi_map);
}

void	Location::set_m_max_body_size(int size)
{
	m_max_body_size = size;
}

void	Location::set_m_return_num(int return_num)
{
	m_return_num = return_num;
}

void	Location::set_m_auto_index(bool auto_index)
{
	m_auto_index = auto_index;
}

void	Location::set_m_root(std::string root)
{
	m_root = root;
}

void	Location::set_m_uri(std::string uri)
{
	m_uri = uri;
}

void	Location::set_m_return_url(std::string return_url)
{
	m_return_url = return_url;
}
