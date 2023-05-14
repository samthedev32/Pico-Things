#pragma once

#include "list.h"

typedef int (*CLIFunction_t)(const char *);

typedef struct
{
    const char *name;
    CLIFunction_t function;
} CLI_Command;

list *CLI_Command_List = NULL;

// Register Command
int CLI_Register(const char *name, CLIFunction_t func)
{
    CLI_Command *cmd = (CLI_Command *)malloc(sizeof(CLI_Command));
    cmd->name = name;
    cmd->function = func;

    list_add(&CLI_Command_List, (void *)cmd);

    return 0;
}

// Run Command
int CLI_Run(const char *command)
{
    list *i = NULL;
    while (list_iterate(CLI_Command_List, &i))
    {
        if (((CLI_Command *)i->userData)->name == command)
            return ((CLI_Command *)i->userData)->function(command);
    }

    return 0;
}