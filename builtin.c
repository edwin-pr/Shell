#include "shell.h"

int builtin_exit(char **args)
{
    return 0; // Returning 0 will signal the shell to exit
}

int builtin_cd(char **args)
{
    if (args[1] == NULL) {
        // No argument provided to cd, go to home directory
        char *home_dir = getenv("HOME");
        if (home_dir == NULL) {
            perror("cd");
            return 1;
        }
        if (chdir(home_dir) != 0) {
            perror("cd");
        }
    } else {
        // Change to the specified directory
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
    return 1;
}

int builtin_setenv(char **args)
{
    if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Error: Usage: setenv VARIABLE VALUE\n");
    } else {
        if (setenv(args[1], args[2], 1) != 0) {
            perror("setenv");
        }
    }
    return 1;
}

int builtin_unsetenv(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "Error: Usage: unsetenv VARIABLE\n");
    } else {
        if (unsetenv(args[1]) != 0) {
            perror("unsetenv");
        }
    }
    return (1);
}
