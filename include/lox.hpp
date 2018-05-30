#ifndef LOXPP_SRX_LOX_H_
#define LOXPP_SRX_LOX_H_

#include <string>

class Lox {
public:
  void runFile(char *path);
  void runPrompt();
  void run(std::string source);
};

#endif

