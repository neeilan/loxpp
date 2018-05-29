#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void runFile(char *path);
void runPrompt();
void run(std::string source);

int main(int argc, char **argv) {
  if (argc > 2) {
    std::cout << "Usage: loxpp [source file]" << std::endl;
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }
}

void runFile(char *path) {
  std::ifstream file(path);
  std::stringstream src_buffer;

  src_buffer << file.rdbuf();

  run(src_buffer.str());
}

void runPrompt() {
  std::string curr_line;
  while (true) {
    getline(std::cin, curr_line);
    std::cout << "> ";
    run(curr_line);
  }
}

void run (std::string source) {
  std::cout << source << std::endl;
}

