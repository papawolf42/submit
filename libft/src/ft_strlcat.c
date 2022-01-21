/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <papawolf@kakao.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 19:19:10 by gunkim            #+#    #+#             */
/*   Updated: 2020/10/22 10:45:14 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		s;
	size_t		d;

	s = 0;
	d = ft_strlen(dst);
	if (size <= d)
		return (ft_strlen(src) + size);
	while (src[s] && (d + s + 1 < size))
	{
		dst[d + s] = src[s];
		s++;
	}
	dst[d + s] = '\0';
	return (s + ft_strlen(src + s) + d);
}
