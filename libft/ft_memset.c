/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:24:23 by ztoptas           #+#    #+#             */
/*   Updated: 2025/06/04 12:47:31 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*s, int c, size_t	n)
{
	unsigned char	*x;
	size_t			i;

	i = 0;
	x = (unsigned char *) s;
	while (i < n)
	{
		x[i] = (unsigned char) c;
		i++;
	}
	return (x);
}
