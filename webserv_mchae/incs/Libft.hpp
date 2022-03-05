#ifndef LIBFT_HPP
# define LIBFT_HPP

#include <string>
#include <vector>
#include <iostream>

void		ft_split(const std::string& target, const std::string& sep,		\
					 std::vector<std::string>& result);
std::string	ft_getline(std::string& str);

#endif