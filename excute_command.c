#include "shell.h"

int ecxute_command(char *command, char *argv[] )
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
			wait(&status); /* make parent proccess to wait child to terminate */
		}
    return (0);
}