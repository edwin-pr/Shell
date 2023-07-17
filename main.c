#include "shell.h"

int main(void)
{
    char *line;
    char **args;
    int status;

    do {
        print_prompt();
        line = read_line();
        args = parse_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}

