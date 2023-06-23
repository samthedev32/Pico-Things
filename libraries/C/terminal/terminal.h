#pragma once

#include <list.h>
#include <string.h>

#define CLI_MAX_COMMAND_LENGTH 64
#define CLI_MAX_ARG_LENGTH 256

typedef int (*CLIFunction_t)(int, char **);

typedef struct {
  const char *name;
  CLIFunction_t function;
} CLI_Command;

list *CLI_Command_List = NULL;

// Register Command
int CLI_Register(const char *name, CLIFunction_t func) {
  CLI_Command *cmd = (CLI_Command *)malloc(sizeof(CLI_Command));
  cmd->name = name;
  cmd->function = func;

  list_add(&CLI_Command_List, (void *)cmd);

  return 0;
}

// Run Command
int CLI_Run(const char *command) {
  char cmd[CLI_MAX_COMMAND_LENGTH];
  int argc;
  char *argv[CLI_MAX_ARG_LENGTH];
  sscanf(command, "%s %[^\n]", &cmd, argv);

  list *i = NULL;
  while (list_iterate(CLI_Command_List, &i)) {
    if (!strcmp(((CLI_Command *)i->userData)->name, cmd))
      return ((CLI_Command *)i->userData)->function(argc, argv);
  }

  return 0;
}