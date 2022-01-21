/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:01:31 by gunkim            #+#    #+#             */
/*   Updated: 2022/01/14 04:30:15 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_isset(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_pass_set(char const *s1, char const *set,
		size_t direction, size_t strlen)
{
	size_t	i;

	i = 0;
	while (strlen--)
	{
		if (!ft_isset(*s1, set))
			break ;
		i++;
		s1 += direction;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	strlen;
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	strlen = ft_strlen(s1);
	start = ft_pass_set(s1, set, 1, strlen);
	end = strlen - ft_pass_set(s1 + strlen - 1, set, -1, strlen);
	if (start > end)
		start = end;
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, s1 + start, end - start + 1);
	return (trim);
}
