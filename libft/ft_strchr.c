/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:43:28 by ztoptas           #+#    #+#             */
/*   Updated: 2025/06/02 16:20:55 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int ch)
{
	int	i;

	i = 0;
	while (s[i] && (char)ch != s[i])
	{
		i++;
	}
	if ((char)ch == s[i])
	{
		return ((char *)(s + i));
	}
	return (NULL);
}
