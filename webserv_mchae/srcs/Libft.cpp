#include "../incs/Libft.hpp"

void	ft_split(const std::string& target, const std::string& sep,			\
				 std::vector<std::string>& result)
{
	std::string word;

	for (std::string::const_iterator										\
		it = target.begin(); it != target.end(); it++)
	{
		if (sep.find(*it) == std::string::npos)
			word += *it;
		else 
		{
			if (word != "")
			{
				result.push_back(word);
				word.clear();
			}
		}
	}
	if (word != "")
	{
		result.push_back(word);
		word.clear();
	}
}

std::string	ft_getline(std::string& str)
{
	size_t		idx;
	std::string	line;

	idx = str.find("\n");
	if (idx != std::string::npos)
	{
		line = str.substr(0, idx);
		str = str.substr(idx + 1, str.size());
	}
	else
	{
		line = str.substr(0, str.size());
		str = str.substr(str.size());
	}
	return (line);
}
