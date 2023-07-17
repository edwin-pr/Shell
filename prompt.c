#include "shell.h"

void print_prompt(void)
{
    char *username = getenv("USER");
    char *current_dir = getcwd(NULL, 0);

    if (username != NULL && current_dir != NULL) {
        printf("%s@%s$ ", username, current_dir);
    } else {
        perror("Prompt error");
        exit(EXIT_FAILURE);
    }

    free(current_dir);
}

