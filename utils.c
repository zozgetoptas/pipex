/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:08:08 by ztoptas           #+#    #+#             */
/*   Updated: 2025/08/08 09:08:08 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void	error_exit(char *error_message)
{
	perror(error_message); // stderr'e yazar (errno'ya gore cikti)
	exit(1); // programi sonlandirir, kontrolu dogrudan isletim sistemine geri verir
}

void	free_array(char **arr)
{
	size_t i = 0;

	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**get_path_directories(char **envp)
{
	int i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

void	print_error(char *prefix, char *cmd)
{
	ft_putstr_fd(prefix, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

char	*find_command_path(char *command, char **envp)
{
	char	**directories_to_check;
	char	*full_path;
	char	*temp_path;
	int		i;

	i = 0;
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	directories_to_check = get_path_directories(envp);
	if (!directories_to_check)
		return (NULL);
	while (directories_to_check[i])
	{
		temp_path = ft_strjoin(directories_to_check[i], "/");
		if (!temp_path)
			return (free_array(directories_to_check), NULL);
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (!full_path)
			return (free_array(directories_to_check), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_array(directories_to_check), full_path);
		free(full_path);
		i++;
	}
	return (free_array(directories_to_check), NULL);
}
