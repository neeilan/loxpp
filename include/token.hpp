#ifndef LOXPP_SRC_TOKEN_H_
#define LOXPP_SRC_TOKEN_H_

#include <string>

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  END_OF_FILE
};

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const void *literal;  // TODO: look into std::optional here
  const int line; 

  Token(TokenType type,
        std::string lexeme,
        void *literal,
        int line);

  std::string str();
};

#endif

