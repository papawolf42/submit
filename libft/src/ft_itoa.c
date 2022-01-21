/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 09:55:05 by gunkim            #+#    #+#             */
/*   Updated: 2022/01/14 04:23:10 by gunkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_preprocess(int n, int *sign, int *digit)
{
	unsigned int	nbr;
	unsigned long	base_ten;

	*sign = 0;
	*digit = 0;
	nbr = n;
	base_ten = 1;
	if (n == 0)
	{
		*digit = 1;
		return (nbr);
	}
	if (n < 0)
	{
		*sign = 1;
		nbr = n * -1;
	}
	while (nbr >= base_ten)
	{
		base_ten *= 10;
		(*digit)++;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				sign;
	int				digit;
	unsigned int	nbr;

	nbr = ft_preprocess(n, &sign, &digit);
	str = (char *)malloc(sizeof(char) * (sign + digit + 1));
	if (str == NULL)
		return (NULL);
	str[sign + digit] = '\0';
	while (digit--)
	{
		str[sign + digit] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
