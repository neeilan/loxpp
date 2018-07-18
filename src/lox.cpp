#include "lox.hpp"
#include "scanner.hpp"
#include "token.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


void Lox::run_file(const char *path) {
    const std::ifstream file(path);
    std::stringstream src_buffer;

    src_buffer << file.rdbuf();

    run(src_buffer.str());

    if (hadError) exit(65);  // data format error
}

void Lox::run_prompt() {
    std::string curr_line;

    while (true) {
        hadError = false;  // reset error status
        getline(std::cin, curr_line);

        std::cout << "> ";
        run(curr_line);
        std::cout << std::endl;
    }
}

void Lox::run(const std::string& source) {
    Scanner scanner(source);
    const std::vector<Token> tokens = scanner.scan_tokens();

    // Print the tokens for now
    for (const Token& token : tokens) {
        std::cout << token.str();
    }
}

void Lox::error(int line, const std::string& message) {
    report(line, "", message);
}

// Private
bool Lox::hadError = false;

void Lox::report(int line,
                 const std::string& occurrence,
                 const std::string& message) {
    std::cout << "[line " << line << "] Error: "
              << occurrence << " : " << message;

    hadError = true;
}
