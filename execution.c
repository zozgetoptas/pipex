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
#include "libft/libft.h"
#include <fcntl.h>
#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

char	*validate_and_get_command_path(char **command_args, char **envp)
{
	char	*command_path;

	if (!command_args[0])
	{
		ft_putstr_fd("pipex: empty command\n", 2);
		free_array(command_args);
		exit(1);
	}
	command_path = find_command_path(command_args[0], envp);
	if (!command_path)
	{
		if (access(command_args[0], F_OK) == 0
			&& access(command_args[0], X_OK) == -1)
		{
			print_error("pipex: permission denied: ", command_args[0]);
			free_array(command_args);
			exit(126);
		}
		else
		{
			print_error("command not found", command_args[0]);
			free_array(command_args);
			exit(127);
		}
	}
	return (command_path);
}

char	*find_command_path(char *command, char **envp)
{
	char	**directories_to_check;
	char	*result;

	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	directories_to_check = get_path_directories(envp);
	if (!directories_to_check)
		return (NULL);
	result = search_in_directories(directories_to_check, command);
	free_array(directories_to_check);
	return (result);
}

char	**get_path_directories(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*search_in_directories(char **directories, char *command)
{
	char	*temp_path;
	char	*full_path;
	int		i;

	i = 0;
	while (directories[i])
	{
		temp_path = ft_strjoin(directories[i], "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
