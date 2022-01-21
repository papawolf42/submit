/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 21:06:50 by gunkim            #+#    #+#             */
/*   Updated: 2022/01/14 04:28:11 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_get_str(char **strs, const char *s, char c)
{
	size_t		num;
	const char	*start;

	num = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		if (*s != c)
			start = s;
		while (*s != c && *s)
			s++;
		strs[num] = (char *)malloc(sizeof(char) * (s - start + 1));
		if (!strs[num])
			return (NULL);
		ft_strlcpy(strs[num], start, s - start + 1);
		num++;
	}
	return (strs);
}

static char	**ft_get_strs(char const *s, char c)
{
	size_t	num;
	char	**strs;

	num = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
			num++;
		while (*s != c && *s)
			s++;
	}
	if (c == '\0')
		num++;
	strs = (char **)ft_calloc((num + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	return (strs);
}

static void	ft_free_all(char **strs)
{
	while (*strs)
	{
		free(*strs);
		(*strs)++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = ft_get_strs(s, c);
	if (strs == NULL)
		return (NULL);
	if (!(ft_get_str(strs, s, c)))
	{
		ft_free_all(strs);
		return (NULL);
	}
	return (strs);
}
