#include "shell.h"

/**
 * main - An Entrance for the shell program
 * @argc: the count of the arguments of the program
 * @argv: vector of the arguments
 *
 * Return: 0 on success and 1 on failure
 */
int main(int argc, char **argv)
{

	(void) argc;
	shell(argv[0]);
	exit(EXIT_SUCCESS);

}
