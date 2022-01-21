/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <papawolf@kakao.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 03:19:03 by gunkim            #+#    #+#             */
/*   Updated: 2020/10/21 09:07:43 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	const unsigned char	*ptr;
	unsigned char		catch;

	ptr = b;
	catch = (unsigned char)c;
	while (len--)
	{
		if (*ptr == catch)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
