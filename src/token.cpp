#include "token.hpp"

#include <string>

Token::Token(TokenType type,
             std::string lexeme,
             void *literal,
             int line)
             : type(type),
               lexeme(lexeme),
               literal(literal),
               line(line) {}

std::string Token::str() {
 return std::to_string(type)
        + " "
        + lexeme;

        // TODO: Refactor w/ Literal base class
        // + " " + std::to_string(literal);
}

