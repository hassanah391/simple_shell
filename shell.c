#include "shell.h"

/**
 * arguments - handle inputline (arguments) and store it in argv
 * @inputline: An input that a user enter
 * @argv: for storing arguments (command+options)
 *
 * arguments: takes the inputline string and take out
 *            arguments (command+options) from it
 */
void arguments(char *inputline, char **argv)
{
	int i = 0;
	char *token;
	/* take arguments from inputline string and store it in argv */
	token = strtok(inputline, " ");
	i = 0;
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
}
/**
 * _getline - read a input line from user without \n character
 * @inputline: a pointer to the inputline string
 * @len: length of the inputline string
 *
 * Return: input line (command) on success and NULL on failure
 */
char *_getline(char *inputline, size_t len)
{
	ssize_t nread; /* return value of getline() */

	nread = getline(&inputline, &len, stdin);
	if (nread == -1) /* if getline failed to read */
	{
		free(inputline);
		if (feof(stdin))  /* Check if EOF (Ctrl+D) is reached */
		{
			printf("\n");
			exit(0);  /* Exit the shell */
		}
		perror("Error: Cannot read input from user\n");
		return (NULL);
	}
	if (inputline[nread - 1] == '\n') /* Remove \n character from inputline */
	{
		inputline[nread - 1] = '\0';
	}
	return (inputline);
}
/**
 * shell - repeatedly takes a input line (command) from a user and executes it
 *
 * Return: 0 on success and -1 on failure
 */
int shell(void)
{
	char *inputline = NULL, *argv[10], *full_path;
	size_t len = 0;

	do {
		printf("#cisfun$ "); /* Prompt for the shell */
		inputline = _getline(inputline, len);
		if (strcmp(inputline, "\0") == 0) /* Re-prompt if user presses Enter */
		{
			free(inputline);
			inputline = NULL;
			continue;
		}
		arguments(inputline, argv); /* handle arguments and store it in argv */
		if (strcmp(argv[0], "exit") == 0) /* if user input "exit" trminate shell */
		{
			free(inputline);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[0], "env") == 0)
			_print_env();

		full_path = handle_path_var(argv[0]);
		if (full_path == NULL)
		{
			printf("Error: command does not exist");
			continue;
		}
		ecxute_command(full_path, argv);

		free(inputline);
		inputline = NULL;
	} while (1);
	return (0);
}
