#include "shell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// Function to execute commands with redirection
void execute_with_redirection(char **args, char *input_file, char *output_file)
{
    // Open the input file in read-only mode, if provided
    if (input_file != NULL)
    {
        int input_fd = open(input_file, O_RDONLY);
        if (input_fd == -1)
        {
            perror("open");
            return;
        }
        // Redirect stdin to the input file
        if (dup2(input_fd, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close(input_fd);
            return;
        }
        // Close the file descriptor as we don't need it anymore
        close(input_fd);
    }

    // Open the output file in write-only mode with create and truncate flags, if provided
    if (output_file != NULL)
    {
        int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (output_fd == -1)
        {
            perror("open");
            return;
        }
        // Redirect stdout to the output file
        if (dup2(output_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            close(output_fd);
            return;
        }
        // Close the file descriptor as we don't need it anymore
        close(output_fd);
    }

    // Execute the command with arguments
    if (execvp(args[0], args) == -1)
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}
