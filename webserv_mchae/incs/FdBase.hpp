#ifndef FDBASE_HPP
# define FDBASE_HPP

typedef enum	t_fd_type
{
	FD_SERVER,
	FD_CLIENT,
	FD_RESOURCE
}				e_fd_type;

class FdBase
{
	protected:
		int			m_fd;
		e_fd_type	m_fd_type;

	public:
		FdBase(void);
		FdBase(const FdBase& copy);
		virtual ~FdBase(void);
		FdBase&	operator=(const FdBase& copy);

		int			get_m_fd(void) const;
		e_fd_type	get_m_fd_type(void) const;

		void		set_m_fd(int fd);
		void		set_m_fd_type(e_fd_type fd_type);
};

#endif