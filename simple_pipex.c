#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void    error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

char    **get_cmd(char *cmd)
{
    // Very baic split (doesn't handle quotes/escaping)
    char **args = malloc(100 * sizeof(char *));
    int i = 0;
    args[i] = strtok(cmd, " ");
    while (args[i])
        args[++i] = strtok(NULL, " ");
    return args;
}

void    child1(int pipe_fd[2], char *infile, char *cmd)
{
    int in_fd = open(infile, O_RDONLY);
    if (in_fd < 0)
        error_exit("infile");
    
    dup2(in_fd, STDIN_FILENO); // stdin = infile
    dup2(pipe_fd[1], STDOUT_FILENO); // stdout = write end of pipe
    close(pipe_fd[0]); // close read end
    close(in_fd);

    char **args = get_cmd(cmd);
    execvp(args[0], args);
    error_exit("execvp cmd1");
}

void    child2(int pipe_fd[2], char *outfile, char *cmd)
{
    int out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd < 0)
        error_exit("outfile");
    
    dup2(pipe_fd[0], STDIN_FILENO); // stdin = read end of pipe
    dup2(out_fd, STDOUT_FILENO); // stdout = outfile
    close(pipe_fd[1]); // close write end
    close(out_fd);

    char **args = get_cmd(cmd);
    execvp(args[0], args);
    error_exit("execvp cmd2");
}

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
        return (1);
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
        error_exit("pipe");
    
    pid_t pid1 = fork();
    if (pid1 == 0)
        child1(pipe_fd, argv[1], argv[2]);
    
    pid_t pid2 = fork();
    if (pid2 == 0)
        child2(pipe_fd, argv[4], argv[3]);
    
    // Parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (0);
}
