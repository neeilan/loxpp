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

  if (hadError) exit(65);  // data format error
}

void Lox::runPrompt() {
  std::string curr_line;

  while (true) {
    hadError = false;  // reset error status
    getline(std::cin, curr_line);
    
    std::cout << "> ";
    run(curr_line);
  }
}

void Lox::run (std::string source) {
  std::cout << source << std::endl;
}

void Lox::error(int line, std::string message) {
  report(line, "", message);
}

// Private
bool Lox::hadError = false;

void Lox::report(int line,
                 std::string occurrence,
                 std::string message) {
  std::cout << "[line " << line << "] Error: "
    << occurrence  << " : " << message;

  hadError = true;
}
