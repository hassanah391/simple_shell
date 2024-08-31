#include "shell.h"
/**
* _env - prints value of env
*
*/
void _env(void)
{
	char *env_vars[] = {"SHLVL", "HBTN", NULL};
	int i = 0, j;
	char *env_value;

	while (environ[i] != NULL)
	{
		for (j = 0; env_vars[j] != NULL; j++)
		{
			if (strncmp(environ[i], env_vars[j], strlen(env_vars[j])) == 0)
			{
				env_value = environ[i] + strlen(env_vars[j]) + 1;
				printf("%s=%s\n", env_vars[j], env_value);
				break;
			}
		}
		i++;
	}
}