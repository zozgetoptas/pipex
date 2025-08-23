#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

void	print_error(char *prefix, char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(prefix, 2);
	ft_putstr_fd("\n", 2);
}

void	error_exit(char *error_message)
{
	perror(error_message);
	exit(1);
}

void	free_array(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
