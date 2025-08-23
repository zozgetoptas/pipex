/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:37:09 by ztoptas           #+#    #+#             */
/*   Updated: 2025/06/04 13:33:32 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_len(long n, int sign)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	if (sign < 0)
		count++;
	return (count);
}

static long	ft_sign(int n, int *sign)
{
	long	n2;

	n2 = n;
	if (n2 < 0)
		*sign = -1;
	else
		*sign = 1;
	n2 *= (*sign);
	return (n2);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;
	long	n2;

	n2 = ft_sign(n, &sign);
	len = ft_len(n2, sign);
	str = malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = '0' + (n2 % 10);
		n2 /= 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}
