#ifndef LOXPP_SRC_LOX_H_
#define LOXPP_SRC_LOX_H_

#include <string>

#include "token.hpp"

class Lox {
public:
    static void run_file(const char* path);

    static void run_prompt();

    static void run(const std::string& source);

    static void error(int line, const std::string& message);

    static void error(Token token, const std::string& message);

private:
    static bool hadError;

    static void report(int line, const std::string& occurrence, const std::string& message);

};

#endif

