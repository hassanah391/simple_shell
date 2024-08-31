#ifndef SHELL
#define SHELL

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
extern char **environ;
int shell(char *programname);
void arguments(char *command, char **argv);
char *handle_path_var(char *command);
void _env(void);
int excute_command(char *command, char *argv[]);
int non_interactive(char *programname);
char *_getline(char *inputline, size_t len);

#endif
