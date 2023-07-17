#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>

// Function prototypes
void print_prompt(void);
char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
int builtin_exit(char **args);
int builtin_cd(char **args);
int builtin_setenv(char **args);
int builtin_unsetenv(char **args);

#endif /* SHELL_H */

