#include "shell.h"
#include <glob.h>

// Function to expand wildcards in arguments
char **expand_wildcards(char **args)
{
    glob_t globbuf;
    int i, flags = 0;

    // Count the number of arguments
    for (i = 0; args[i] != NULL; i++)
        ;

    // Loop through arguments and expand wildcards
    for (i = 1; args[i] != NULL; i++) {
        if (strchr(args[i], '*') != NULL || strchr(args[i], '?') != NULL) {
            flags |= GLOB_NOCHECK;
            break;
        }
    }

    if (glob(args[1], flags, NULL, &globbuf) != 0) {
        perror("Error");
        return args;
    }

    // Remove the wildcard argument and append expanded files
    free(args[1]);
    args[1] = strdup(globbuf.gl_pathv[0]);
    for (i = 1; i < globbuf.gl_pathc; i++) {
        args = realloc(args, (i + 2) * sizeof(char *));
        if (!args) {
            perror("Allocation error");
            exit(EXIT_FAILURE);
        }
        args[i + 1] = strdup(globbuf.gl_pathv[i]);
    }
    args[i + 1] = NULL;

    // Free memory used by glob
    globfree(&globbuf);

    return args;
}

