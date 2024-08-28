#include "shell.h"
void _print_env()
{
	int i;
	i = 0;

	while (environ[i] != NULL)
	{
		printf("%s", environ[i++]);
	}
	printf("\n");
}
