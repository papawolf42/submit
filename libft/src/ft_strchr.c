/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <papawolf@kakao.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 01:50:58 by gunkim            #+#    #+#             */
/*   Updated: 2020/10/21 11:54:15 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char		catch;
	size_t		len;

	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	catch = c;
	len = ft_strlen(s);
	while (len--)
	{
		if (*s == catch)
			return ((char *)s);
		s++;
	}
	return (0);
}
