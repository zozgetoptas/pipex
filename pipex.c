/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:07:51 by ztoptas           #+#    #+#             */
/*   Updated: 2025/08/08 09:07:51 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

static void	execute_command(char *command, char **envp)
{
	char	**command_args;
	char	*command_path;

	command_args = ft_split(command, ' ');
	if (!command_args)
		error_exit("pipex: memory allocation failed");
	command_path = validate_and_get_command_path(command_args, envp);
	if (execve(command_path, command_args, envp) == -1)
	{
		print_error("pipex: execve failed: ", command_args[0]);
		free(command_path);
		free_array(command_args);
		exit(1);
	}
}

static void	first_child_process(int *pipe_fds, char **argv, char **envp)
{
	int	first_file_fd;

	close(pipe_fds[0]);
	first_file_fd = open(argv[1], O_RDONLY);
	if (first_file_fd == -1)
	{
		ft_putstr_fd("-bash: ", 2);
		perror(argv[1]);
		close(pipe_fds[1]);
		exit(1);
	}
	if (dup2(first_file_fd, 0) == -1)
	{
		close(pipe_fds[1]);
		close(first_file_fd);
		error_exit("dup2 infile failed");
	}
	close(first_file_fd);
	if (dup2(pipe_fds[1], 1) == -1)
		error_exit("dup2 pipe write failed");
	close(pipe_fds[1]);
	execute_command(argv[2], envp);
}

static void	second_child_process(int *pipe_fds, char **argv, char **envp)
{
	int	second_file_fd;

	close(pipe_fds[1]);
	second_file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (second_file_fd == -1)
	{
		ft_putstr_fd("-bash: ", 2);
		perror(argv[4]);
		close(pipe_fds[0]);
		exit(1);
	}
	if (dup2(pipe_fds[0], 0) == -1)
	{
		close(pipe_fds[0]);
		close(second_file_fd);
		error_exit("dup2 pipe read failed");
	}
	close(pipe_fds[0]);
	if (dup2(second_file_fd, 1) == -1)
	{
		close(second_file_fd);
		error_exit("dup2 outfile failed");
	}
	close(second_file_fd);
	execute_command(argv[3], envp);
}

static void	create_processes(int *pipe_fds, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		error_exit("failure creating first child process");
	if (pid1 == 0)
		first_child_process(pipe_fds, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("failure creating second child process");
	if (pid2 == 0)
		second_child_process(pipe_fds, argv, envp);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipe_fds[2];

	if (argc != 5)
	{
		ft_putstr_fd("usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	if (pipe(pipe_fds) == -1)
		error_exit("error occurred while opening the pipe");
	create_processes(pipe_fds, argv, envp);
	return (0);
}
