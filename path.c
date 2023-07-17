#include "shell.h"

// Function to get the full path of a command
char *get_full_path(char *command)
{
    char *full_path = NULL;
    char *path = getenv("PATH");

    if (path != NULL) {
        char *token;
        char *paths = strdup(path);

        if (!paths) {
            perror("Allocation error");
            exit(EXIT_FAILURE);
        }

        token = strtok(paths, ":");
        while (token != NULL) {
            char *temp_path = malloc(strlen(token) + strlen(command) + 2);
            if (!temp_path) {
                perror("Allocation error");
                exit(EXIT_FAILURE);
            }

            sprintf(temp_path, "%s/%s", token, command);

            // Check if the file exists and is executable
            if (access(temp_path, X_OK) == 0) {
                full_path = temp_path;
                break;
            }

            free(temp_path);
            token = strtok(NULL, ":");
        }
        free(paths);
    }

    return full_path;
}
