#include "shell.h"

/**
 * excute_command - executes command line with args that user passed
 * @command: a command to be executed
 * @argv: arguments (EX: option) in the command line
 *
 * Return: 0 on success and -1 on failure
 */
int excute_command(char *command, char *argv[])
{
    pid_t forkvalue;
    int status;
    int pipefd[2];
    char buffer[4096];
    ssize_t bytes_read;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }

    forkvalue = fork();
    if (forkvalue == -1) {
        perror("fork");
        return -1;
    }

    if (forkvalue == 0) { /* Child process */
        close(pipefd[0]); /* Close read end */
        dup2(pipefd[1], STDOUT_FILENO); /* Redirect stdout to pipe */
        dup2(pipefd[1], STDERR_FILENO); /* Redirect stderr to pipe */
        close(pipefd[1]);

        if (execve(command, argv, environ) == -1) {
            perror("Error: Cannot execute the command");
            exit(EXIT_FAILURE);
        }
    } else { /* Parent process */
        close(pipefd[1]); /* Close write end */

        /* Read from pipe */
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer); /* Print captured output */
        }

        close(pipefd[0]);
        wait(&status);
    }

    return 0;
}