#include "shell.h"
/**
* _print_env - prints value of env
*
*/
void _print_env(void)
{
	int i;

	i = 0;

	while (environ[i] != NULL)
	{
		printf("%s", environ[i++]);
	}
	printf("\n");
}
