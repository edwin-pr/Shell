#include "shell.h"

// Function to handle general errors
void handle_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// Function to handle command-specific errors
void command_error(const char *command)
{
    fprintf(stderr, "Error: '%s' command not found\n", command);
}
