#include "shell.h"

/**
* non_interactive - handle inputs from non-interactive mode
*   (pipe lines or script file) (EX: echo "/bin/ls" | ./hsh)
* @programname: the name of the execution file
*
* Return: 0 on success and -1 on failure
*/
int non_interactive(char *programname)
{
    char *inputline = NULL, *argv[10] = {NULL}, *full_path;
    int number_command, status = 0;
    size_t len = 0;
    ssize_t read;

    number_command = 0;

    while ((read = getline(&inputline, &len, stdin)) != -1)
    {
        if (read > 0 && inputline[read - 1] == '\n')
            inputline[read - 1] = '\0';  /* remove \n newline */

        if (inputline[0] == '\0')  /* if user pressed Enter */
            continue;

        number_command++;

        arguments(inputline, argv);
        if (argv[0] == NULL) 
            continue;

        if (strcmp(argv[0], "exit") == 0)
        {
            free(inputline);
            exit(status);
        }
        else if (strcmp(argv[0], "env") == 0)
        {
            _env();
        }
        else
        {
            full_path = handle_path_var(argv[0]);
            if (full_path == NULL)
            {
                fprintf(stderr, "%s: %d: %s: not found\n", programname, number_command, argv[0]);
                status = 127; /* Command not found */
            }
            else
            {
                status = excute_command(full_path, argv, programname, number_command);
                free(full_path);
            }
        }

        memset(argv, 0, sizeof(argv));
    }

    free(inputline);
    return (status);
}