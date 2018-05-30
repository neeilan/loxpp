#include "scanner.hpp"
#include "token.hpp"

#include <map>

const std::map<std::string, TokenType> Scanner::keywords = {
  { "and",   AND },
  { "class", CLASS },
  { "else",  ELSE },
  { "false", FALSE },
  { "for",   FOR },
  { "fun",   FUN },
  { "if",    IF },
  { "nil",   NIL },
  { "or",    OR },
  { "print", PRINT },
  { "return",RETURN },
  { "super", SUPER },
  { "this",  THIS },
  { "true",  TRUE },
  { "var",   VAR },
  { "while", WHILE }
};

