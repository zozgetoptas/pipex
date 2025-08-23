/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:44:31 by ztoptas           #+#    #+#             */
/*   Updated: 2025/06/02 16:22:20 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	const char	*last;
	int			i;

	i = 0;
	last = NULL;
	while (str[i])
	{
		if (str[i] == (char)ch)
			last = str + i;
		i++;
	}
	if ((char)ch == '\0')
		return ((char *)(str + i));
	return ((char *)last);
}
