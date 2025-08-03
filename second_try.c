#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include <sys/wait.h>

void    error_exit(char *message)
{
    perror(message);
    exit(1);
}

static void free_array(char **s)
{
    size_t  i = 0;
    while (s && s[i])
    {
        free(s[i]);
        i++;
    }
    if (s)
        free(s);
}

// PATH'i parse et ve komut yolunu bul
char    *find_cmd_path(char *cmd, char **envp)
{
    char    *path_env = NULL;
    char    **path_dirs;
    char    *full_path;
    int     i = 0;
    
    // Komutun zaten tam yol olup olmadığını kontrol et (örn. "/bin/ls").
    if (access(cmd, X_OK) == 0)
        return ft_strdup(cmd);

    // PATH ortam değişkenini bul.
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
        i++;
    }

    if (!path_env)
        return NULL;

    // PATH'i ':' ile ayır. ft_split libft'den gelmeli.
    path_dirs = ft_split(path_env, ':');
    if (!path_dirs)
        return NULL;

    // Her dizinde komut dosyasını ara.
    i = 0;
    while (path_dirs[i])
    {
        // path_dir + "/" + cmd şeklinde birleştir.
        full_path = malloc(ft_strlen(path_dirs[i]) + ft_strlen(cmd) + 2);
        if (!full_path)
        {
            free_array(path_dirs);
            return NULL;
        }
        strcpy(full_path, path_dirs[i]);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        
        if (access(full_path, X_OK) == 0)
        {
            free_array(path_dirs);
            return full_path;
        }
        free(full_path);
        i++;
    }
    
    free_array(path_dirs);
    return NULL;
}

// Komutu çalıştıran ana fonksiyon.
void    execute_command(char *cmd_str, char **envp)
{
    char    **cmd_args;
    char    *cmd_path;

    // Komut stringini boşlukla ayır. ft_split libft'den gelmeli.
    cmd_args = ft_split(cmd_str, ' ');
    if (!cmd_args || !cmd_args[0])
    {
        ft_putstr_fd("pipex: empty command\n", STDERR_FILENO);
        if (cmd_args)
            free_array(cmd_args);
        exit(EXIT_FAILURE);
    }
    
    cmd_path = find_cmd_path(cmd_args[0], envp);
    if (!cmd_path)
    {
        ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
        ft_putstr_fd(cmd_args[0], STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        free_array(cmd_args);
        exit(127);
    }

    if (execve(cmd_path, cmd_args, envp) == -1)
    {
        perror("execve failed");
        free(cmd_path);
        free_array(cmd_args);
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char **argv, char **envp)
{
    int pipe_fds[2];
    pid_t pid1;
    pid_t pid2;

    if (argc != 5)
    {
        write(1, "usage: ./a.out file1 cmd1 cmd2 file2\n", 37);
        return (1);
    }
    if (pipe(pipe_fds) == -1)
    {
        error_exit("error ocurred while opening the pipe");
    }
    pid1 = fork();
    if (pid1 == -1)
        error_exit("failure tryna make the first child process");
    if (pid1 == 0)
    {
        close(pipe_fds[0]);
        int first_file_fd = open(argv[1], O_RDONLY);
        if (first_file_fd == -1)
        {
            perror("no first file opened");
			close(pipe_fds[1]);
            exit(1);
        }
        if (dup2(first_file_fd, 0) == -1) // ilk komutun stdin'i infile olsun
            error_exit("dup2 failed something");
        close (first_file_fd);
		if (dup2(pipe_fds[1], 1) == -1) // ilk komutun stdout'u pipe'ın write ucu olsun
       		error_exit("dup2 failed pipe write");
        close(pipe_fds[1]);
		execute_command(argv[2], envp);     
    }
	close(pipe_fds[1]);
	pid2 = fork();
	if (pid2 == -1)
		error_exit("failure tryna make the second child process");
	if (pid2 == 0)
	{
		int second_file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (second_file_fd == -1)
		{
			perror("something wrong with the second file");
			close(pipe_fds[0]);
			exit (1);
		}
		if (dup2(pipe_fds[0], 0) == -1) // ikinci komutun stdin'i pıpe'ın read ucu olsun
			error_exit("dup2 failed pipe read");
		close(pipe_fds[0]);
		if (dup2(second_file_fd, 1) == -1) // ikinci komutun stdout'u outfile olsun
			error_exit("dup2 failed something");
		close (second_file_fd);
		execute_command(argv[3], envp);
	}
	close(pipe_fds[0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0); 
	return(0);
}