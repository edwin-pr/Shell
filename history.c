#include "shell.h"

// Function to add a command to the history file
void add_to_history(const char *command)
{
    FILE *history_file = fopen(".history", "a");

    if (history_file != NULL) {
        fprintf(history_file, "%s\n", command);
        fclose(history_file);
    } else {
        perror("Error");
    }
}

// Function to print the history
void print_history(void)
{
    FILE *history_file = fopen(".history", "r");

    if (history_file != NULL) {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, history_file)) != -1) {
            printf("%s", line);
        }

        free(line);
        fclose(history_file);
    } else {
        perror("Error");
    }
}
