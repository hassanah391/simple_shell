#include "shell.h"
/**
* _env - prints value of env
*
*/
void _env(void)
{
	int i;

	i = 0;

	while (environ[i] != NULL)
	{
		printf("%s", environ[i++]);
		if (environ[i] != NULL)
			printf("\n");
	}
}
