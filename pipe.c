#include "shell.h"

// Function to execute commands with pipes
void execute_with_pipe(char **args1, char **args2)
{
    int pipefd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    // Fork the first child process
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return;
    } else if (pid1 == 0) {
        // This is the child process (first command)

        // Close the read end of the pipe
        close(pipefd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Close the write end of the pipe
        close(pipefd[1]);

        // Execute the first command
        if (execvp(args1[0], args1) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // This is the parent process

        // Fork the second child process
        pid2 = fork();
        if (pid2 < 0) {
            perror("fork");
            return;
        } else if (pid2 == 0) {
            // This is the second child process (second command)

            // Close the write end of the pipe
            close(pipefd[1]);

            // Redirect stdin to the read end of the pipe
            dup2(pipefd[0], STDIN_FILENO);

            // Close the read end of the pipe
            close(pipefd[0]);

            // Execute the second command
            if (execvp(args2[0], args2) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // This is the parent process

            // Close both ends of the pipe
            close(pipefd[0]);
            close(pipefd[1]);

            // Wait for both child processes to complete
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }
}
