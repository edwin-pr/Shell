#include "shell.h"

// Global variable to store the debugger mode
bool debugger_mode = false;

// Function to enable or disable the debugger mode
void set_debugger_mode(bool mode)
{
    debugger_mode = mode;
}

// Function to check if the debugger mode is enabled
bool is_debugger_enabled()
{
    return debugger_mode;
}
