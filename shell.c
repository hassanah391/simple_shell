#include "shell.h"

/**
 * _getline - takes a line input from user without \n character
 * @command: a pointer to the line input
 * @len: length of the line input
 *
 * Return: command on success and NULL on failure
 */
char *_getline(char *command, size_t len)
{
	ssize_t nread; /* return value of getline() */

	nread = getline(&command, &len, stdin);
	if (nread == -1) /* if getline failed to read */
	{
		free(command);
		if (feof(stdin))  /* Check if EOF (Ctrl+D) is reached */
		{
			printf("\n");
			exit(0);  /* Exit the shell */
		}
		perror("Error: Cannot read input from user\n");
		return (NULL);
	}
	if (command[nread - 1] == '\n') /* Remove \n character from command */
	{
		command[nread - 1] = '\0';
	}
	return (command);
}
/**
 * shell - repeatedly takes a command from a user and executes it
 *
 * Return: 0 on success and -1 on failure
 */
int shell(void)
{
	char *command, *token, *argv[10];
	size_t len = 0;
	pid_t forkvalue; /* return value of fork() */
	int status, i;

	command = NULL; /* intialaize command to NULL to pass it to _getline() */
	do {
		printf("#cisfun$ ");
		command = _getline(command, len);
		if (command == NULL) /* Exit on EOF */
			break;
		{
			/* take arguments from command string and store it in argv */
			token = strtok(command, " ");
			i = 0;
			while (token != NULL)
			{
				argv[i++] = token;
				token = strtok(NULL, " ");
			}
			argv[i] = NULL;
		}
		forkvalue = fork(); /* duplicate current proccess */
		if (forkvalue == 0) /* child proccess */
		{
			if (execve(argv[0], argv, environ) == -1) /* replace current proccess */
			{ /* if execve() failed */
				perror("Error: Cannot execute the command\n");
				free(command);
				return (-1);
			}
		}
		else /* Parent proccess */
		{
			wait(&status); /* make parent proccess to wait child to terminate */
		}
		free(command);
		command = NULL;
	} while (1);
	return (0);
}
