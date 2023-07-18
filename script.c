#include "shell.h"

// Function to execute commands from a script file
void execute_script(const char *filename)
{
    FILE *script_file = fopen(filename, "r");

    if (script_file != NULL) {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        char **args;

        while ((read = getline(&line, &len, script_file)) != -1) {
            args = parse_line(line);
            execute(args);

            free(line);
            free(args);
            line = NULL;
        }

        fclose(script_file);
        free(line);
    } else {
        perror("Error");
    }
}
