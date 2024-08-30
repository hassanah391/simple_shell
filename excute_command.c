#include "shell.h"

/**
* excute_command - excutes command line withe args that user passed
* @command: a command to be excute
* @argv: arguments(EX: option) in the command line
*
* Return: 0 on success and -1 on failure
*/
int excute_command(char *command, char *argv[])
{
	pid_t forkvalue; /* return value of fork() */
	int status;

	forkvalue = fork(); /* duplicate current proccess */
	if (forkvalue == 0) /* child proccess */
	{
		if (execve(command, argv, environ) == -1) /* replace current proccess */
		{ /* if execve() failed */
			perror("Error: Cannot execute the command\n");
			return (-1);
		}
	}
	else /* Parent proccess */
	{
		printf("HAHAHAHHAHAHAHA******\n");
		wait(&status); /* make parent proccess to wait child to terminate */
	}
	return (0);
}
