#include "Resource.hpp"

Resource::Resource(int fd, std::string& response_message, Client* clnt,		\
				   e_resource_type type, int err) :			\
	m_raw_data(response_message),
	m_client(clnt),
	m_resource_type(type),
	m_response_error_num(err)
{
	m_fd		  = fd;
	m_fd_type	  = FD_RESOURCE;
	m_pid		  = -1;
	m_is_seeked	  = false;
	m_write_index = 0;
	is_cgi_post	  = false;
}

Resource::~Resource()
{}

Resource::Resource(Resource & rsc) :
	m_raw_data(rsc.m_raw_data)
{
	*this = rsc;
}

Resource&	Resource::operator=(Resource& rsc)
{
	m_fd				 = rsc.m_fd;
	m_fd_type			 = rsc.m_fd_type;
	m_pid				 = rsc.m_pid;
	m_is_seeked			 = rsc.m_is_seeked;
	m_raw_data			 = rsc.m_raw_data;
	m_response_error_num = rsc.m_response_error_num;
	m_resource_type		 = rsc.m_resource_type;
	m_write_index		 = rsc.m_write_index;
	is_cgi_post	  = false;

	return *this;
}

std::string&	Resource::get_m_raw_data()
{
	return m_raw_data;
}

Client*	Resource::get_m_client()
{
	return m_client;
}

e_resource_type	Resource::get_m_resource_type()
{
	return m_resource_type;
}

int	Resource::get_m_response_error_num()
{
	return m_response_error_num;
}

size_t	Resource::get_m_write_index()
{
	return m_write_index;
}

int	Resource::get_m_pid()
{
	return m_pid;
}

bool	Resource::get_m_is_seeked()
{
	return m_is_seeked;
}

void	Resource::set_m_raw_data(const std::string& raw_data)
{
	m_raw_data = raw_data;
}

void	Resource::set_m_client(Client * clnt)
{
	m_client = clnt;
}

void	Resource::set_m_resource_type(e_resource_type type)
{
	m_resource_type = type;
}

void	Resource::set_m_response_error_num(int err_num)
{
	m_response_error_num = err_num;
}

void	Resource::set_m_write_index(size_t idx)
{
	m_write_index = idx;
}

void	Resource::set_m_pid(int pid)
{
	m_pid = pid;
}

void	Resource::set_m_is_seeked(bool seeked)
{
	m_is_seeked = seeked;
}

e_rsc_status	Resource::isReady(void)
{
	int	status;

	if (m_pid == -1)
		return (READY);
	if (waitpid(m_pid, &status, WNOHANG) == 0)
		return (NOT_YET);
	if (WIFEXITED(status) == 0)
		return (CGI_CRASH);

	return (READY);
}