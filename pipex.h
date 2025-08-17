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

void	error_exit(char *error_message);
void	free_array(char **arr);
char	**get_path_directories(char **envp);
void	print_error(char *prefix, char *cmd);
char	*find_command_path(char *command, char **envp);
char	*search_in_directories(char **directories, char *command);
char	*validate_and_get_command_path(char **command_args, char **envp);
#endif