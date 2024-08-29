#include "shell.h"
/**
* non_interactive - handle inputs from interactive mode
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

	number_command = 0;

		number_command++;

	if (isatty(STDIN_FILENO))
			return (0);

		inputline = _getline(inputline, len);

		arguments(inputline, argv); /* handle arguments and store it in argv */
		if (strcmp(argv[0], "exit") == 0) /* if user input "exit" trminate shell */
		{
			free(inputline);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(argv[0], "env") == 0)
		{
			_env();
		}
		full_path = handle_path_var(argv[0]);
		if (full_path == NULL)
		{
			printf("%s: %d: %s: not found\n", programname, number_command, argv[0]);
		}
		excute_command(full_path, argv);
		free(inputline);
		inputline = NULL;
	return (0);
}
