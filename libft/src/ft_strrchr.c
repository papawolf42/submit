/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <papawolf@kakao.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 02:22:10 by gunkim            #+#    #+#             */
/*   Updated: 2020/10/21 12:10:32 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	catch;
	int		len;

	if (c == 0)
		return ((char *)s + ft_strlen(s));
	catch = c;
	len = ft_strlen(s);
	while (len--)
		if (s[len] == catch)
			return ((char *)s + len);
	return (0);
}
