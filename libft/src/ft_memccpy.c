/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:04:10 by gunkim            #+#    #+#             */
/*   Updated: 2022/01/14 04:27:05 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;
	unsigned char		stop;

	pdst = dst;
	psrc = src;
	stop = c;
	while (len--)
	{
		*pdst++ = *psrc++;
		if (*pdst == stop)
			return (pdst);
	}
	return (NULL);
}
