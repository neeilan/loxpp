#include "lox.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


void Lox::runFile(char *path) {
  std::ifstream file(path);
  std::stringstream src_buffer;

  src_buffer << file.rdbuf();

  run(src_buffer.str());
}

void Lox::runPrompt() {
  std::string curr_line;
  while (true) {
    getline(std::cin, curr_line);
    std::cout << "> ";
    run(curr_line);
  }
}

void Lox::run (std::string source) {
  std::cout << source << std::endl;
}

