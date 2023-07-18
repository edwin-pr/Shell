#include "shell.h"

// Function to handle errors in the shell
void handle_shell_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

// Function to handle errors related to commands
void handle_command_error(const char *command)
{
    fprintf(stderr, "Error: '%s' command not found\n", command)
}
