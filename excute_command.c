#include "shell.h"

/**
* excute_command - executes command line with args that user passed
* @command: a command to be executed
* @argv: arguments (EX: option) in the command line
* @programname: name of the shell program
* @number_command: number of the current command
*
* Return: exit status of the command
*/
int excute_command(char *command, char **argv,
	char *programname, int number_command)
{
	pid_t forkvalue;
	int status;

	forkvalue = fork();
	if (forkvalue == -1)
	{
		perror("Error: Fork failed\n");
		return (1);
	}
	else if (forkvalue == 0) /* child process */
	{
		if (execve(command, argv, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: %s\n",
			programname, number_command, argv[0], strerror(errno));
			exit(126); /* Permission denied */
		}
	}
	else /* Parent process */
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
