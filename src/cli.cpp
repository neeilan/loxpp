#include "lox.hpp"

#include <iostream>


int main(int argc, char **argv) {
  if (argc > 2) {
    std::cout << "Usage: loxpp [source file]" << std::endl;
    exit(0);
  }

  Lox interpreter;

  if (argc == 2) {
    interpreter.runFile(argv[1]);
  } else {
    interpreter.runPrompt();
  }
}
