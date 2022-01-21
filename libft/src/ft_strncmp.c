/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:13:31 by gunkim            #+#    #+#             */
/*   Updated: 2022/01/14 04:29:28 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	while ((*s1 == *s2) && len-- && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (!len)
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
