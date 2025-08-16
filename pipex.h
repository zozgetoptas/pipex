/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztoptas <ztoptas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 09:07:59 by ztoptas           #+#    #+#             */
/*   Updated: 2025/08/08 09:07:59 by ztoptas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void error_exit(char *error_message);
void free_array(char **arr);
char **get_path_directories(char **envp);
void print_error(char *prefix, char *cmd);
char *find_command_path(char *command, char **envp);
void cleanup_and_exit(int *pipe_fds, int exit_code);

#endif