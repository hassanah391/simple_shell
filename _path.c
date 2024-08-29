#include "shell.h"

/**
 * handle_path_var - handle $PATH environment
 * @command: command (no options, no speactial char like | )taken from user
 *
 * handle_path_var: checks the directories listed in the PATH variable
 *                  to find an executable file store in *command arg
 *
 * Return: return full path of the *command if found, otherwise return NULL
 */
char *handle_path_var(char *command)
{
	char *path_env, *path, *path_env_dup;
	char full_path[1024];
	int c = command[0];

	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL);
	if (c != '/' && c != '.')
	{
		/* in case if user just pass the command (EX: "ls" or "cat") */
		path_env_dup = strdup(path_env);
		if (path_env_dup == NULL)
			return (NULL);
		path = strtok(path_env_dup, ":"); /* seperate paths from each other */
		while (path != NULL)
		{
			/* concatanate path with the command so we get (EX: /bin/ls) */
			snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
			if (access(full_path, X_OK) == 0) /* check if full_path exist and x file */
			{
				free(path_env_dup);
				return (strdup(full_path));
			}
			path = strtok(NULL, ":");
		}
		free(path_env_dup);
	}
	else
	{
		/* in case if user pass the full path(EX: "/bin/ls") in *command */
		if (access(command, X_OK) == 0) /* check if *command does exist and x file*/
			return (strdup(command));
	}
	return (NULL);
}
