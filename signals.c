#include "shell.h"

// Signal handler function for SIGINT (Ctrl+C)
void sigint_handler(int sig_num)
{
    signal(SIGINT, sigint_handler);
    fflush(stdout);
}

// Signal handler function for SIGTSTP (Ctrl+Z)
void sigtstp_handler(int sig_num)
{
    signal(SIGTSTP, sigtstp_handler);
    fflush(stdout);
}
