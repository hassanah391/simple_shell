#include "shell.h"
/**
* non_interactive - handle inputs from non-interactive mode
*   (pipe lines or script file) (EX: echo "/bin/ls" | ./hsh)
* @programname: the name of the excution file
*
* Return: 0 on success and -1 on failure
*/
int non_interactive(char *programname)
{
	char *inputline = NULL, *argv[10], *full_path;
	int number_command;
	size_t len = 0;
	ssize_t read;

	number_command = 0;

	while ((read = getline(&inputline, &len, stdin)) != -1)
	{
		if (read > 0 && inputline[read - 1] == '\n')
			inputline[read - 1] = '\0';  /* Remove trailing newline */

		number_command++;

		arguments(inputline, argv); /* handle arguments and store it in argv */
		if (argv[0] == NULL) /* Skip empty lines */
			continue;

		if (strcmp(argv[0], "exit") == 0) /* if user input "exit" terminate shell */
		{
			free(inputline);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[0], "env") == 0)
		{
			_env();
		}
		else
		{
			full_path = handle_path_var(argv[0]);
			if (full_path == NULL)
			{
				fprintf(stderr, "%s: %d: %s: not found\n",
						programname, number_command, argv[0]);
			}
			else
			{
				excute_command(full_path, argv);
				free(full_path);
			}
		}
	}

	free(inputline);
	return (0);
}