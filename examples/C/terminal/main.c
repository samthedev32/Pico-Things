#include <stdio.h>
#include <terminal.h>

int helloworld(int argc, char **argv) {
  printf("Hello, World!\n");

  return 0;
}

int main() {
  // stdio_init_all();

  // Register Commands
  CLI_Register("say_hello", helloworld);

  CLI_Run("say_hello");

  while (1)
    ;
}