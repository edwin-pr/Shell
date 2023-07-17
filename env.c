#include "shell.h"

// Function to print the environment variables
void print_env(void)
{
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}
