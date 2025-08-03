#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv, char **envp)
{
    int pipe_fds[2];
    // 0 -> read && 1 -> write
    pid_t pid1;
    pid_t pid2;

    if (argc != 5)
    {
        write(2, "usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 48);
        return (1);
    }

    if (pipe(pipe_fds) == -1)
    {
        perror("error ocurred while opening the pipe\n");
        return (1);
    }
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("ilk cocuk surec olusturulamadi\n");
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return (1);
    }
    if (pid1 == 0)
    {
        close (pipe_fds[0]);
        int infile_fd = open(argv[1], O_RDONLY);
        if (infile_fd == -1)
        {
            perror(argv[1]);
            close(pipe_fds[1]);
            exit(1);
        }
        if (dup2(infile_fd, STDERR_FILENO) == -1)
        {
            perror("dup2 infile");
            close (infile_fd);
            close(pipe_fds[1]);
            exit(1);
        }
        close (infile_fd);
        if (dup2(pipe_fds[1], STDERR_FILENO) == -1)
        {
            perror("dup2 pipe_write");
            close(pipe_fds[1]);
            exit(EXIT_FAILURE);
        }
        close(pipe_fds[1]);
        char *cmd_path = "/bin/ls";
        char *cmd_args[3];
        cmd_args[0] = "ls";
        cmd_args[1] = "-l";
        cmd_args[2] = NULL;

        execve(cmd_path, cmd_args, envp);
        perror("execve cmd1"); // execve sadece hata durumunda geri döner
        exit(EXIT_FAILURE);
    }
    else
    {
        close(pipe_fds[1]);
        waitpid(pid1, NULL, 0); // İlk çocuğun bitmesini bekle

        // Ebeveyn, pipe'ın okuma ucunu da kullanmayacak, kapatır.
        close(pipe_fds[0]);
    }
    return(EXIT_SUCCESS);
    
    
    /* 
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2 pipe_read");
        close(pipe_fd[0]);
        close(outfile_fd);
        exit(EXIT_FAILURE);
    }
    close(pipe_fd[0]);

    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 outfile");
        close(outfile_fd);
        exit(EXIT_FAILURE);
    }
        close(outfile_fd);

    printf("file1: %s\n", argv[1]);
    printf("cmd1: %s\n", argv[2]);
    printf("cmd2: %s\n", argv[3]);
    printf("file2: %s\n", argv[4]);

    


    return (EXIT_SUCCESS); */
}