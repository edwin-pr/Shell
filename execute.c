#include "shell.h"

int execute(char **args)
{
    if (args[0] == NULL) {
        // Empty command, do nothing
        return 1;
    }

    // Check if the command is a built-in command
    if (strcmp(args[0], "exit") == 0) {
        return builtin_exit(args);
    } else if (strcmp(args[0], "cd") == 0) {
        return builtin_cd(args);
    } else if (strcmp(args[0], "setenv") == 0) {
        return builtin_setenv(args);
    } else if (strcmp(args[0], "unsetenv") == 0) {
        return builtin_unsetenv(args);
    }

    // Not a built-in command, execute using execvp
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process: execute the command using execvp
        if (execvp(args[0], args) == -1) {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Forking error
        perror("fork");
    } else {
        // Parent process: wait for the child to complete
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
