#ifndef LOXPP_SRX_LOX_H_
#define LOXPP_SRX_LOX_H_

#include <string>

class Lox {
public:
  static void runFile(char *path);
  static void runPrompt();
  static void run(std::string source);
  static void error(int line, std::string message);

private:
  static bool hadError;
  static void report(int line,
                     std::string occurrence,
                     std::string message);

};

#endif

