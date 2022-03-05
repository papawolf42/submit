#include "../incs/FdBase.hpp"

FdBase::FdBase(void) : m_fd(-1)
{}

FdBase::FdBase(const FdBase& copy)
{
	*this = copy;
}

FdBase::~FdBase(void)
{}

FdBase&	FdBase::operator=(const FdBase& copy)
{
	m_fd		= copy.get_m_fd();
	m_fd_type	= copy.get_m_fd_type();
	return (*this);
}

int	FdBase::get_m_fd(void) const
{
	return (m_fd);
}

e_fd_type	FdBase::get_m_fd_type(void) const
{
	return (m_fd_type);
}

void	FdBase::set_m_fd(int fd)
{
	m_fd = fd;
}

void	FdBase::set_m_fd_type(e_fd_type fd_type)
{
	m_fd_type = fd_type;
}