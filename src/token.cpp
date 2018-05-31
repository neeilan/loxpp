#include "token.hpp"

#include <string>
#include <vector>

// Since enum names cannot be printed directly, we use this
// workaround.
static std::vector<std::string> token_names {
  "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", 
  "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",

  "BANG", "BANG_EQUAL",
  "EQUAL", "EQUAL_EQUAL",
  "GREATER", "GREATER_EQUAL",
  "LESS", "LESS_EQUAL",

  "IDENTIFIER", "STRING", "NUMBER",

  "AND", "CLASS", "ELSE", "FALSE","FUN", "FOR", "IF", "NIL", "OR",
  "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE"
};


Token::Token(TokenType type,
             std::string lexeme,
             void *literal,
             int line)
             : type(type),
               lexeme(lexeme),
               literal(literal),
               line(line) {}

std::string Token::str() {
 return token_names[type]
        + " "
        + lexeme;

        // TODO: Refactor w/ Literal base class
        // + " " + std::to_string(literal);
}

