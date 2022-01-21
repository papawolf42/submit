/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <papawolf@kakao.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 01:10:27 by gunkim            #+#    #+#             */
/*   Updated: 2020/10/21 08:45:10 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;

	pdst = dst;
	psrc = src;
	if (pdst < psrc)
		while (len--)
			*pdst++ = *psrc++;
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
