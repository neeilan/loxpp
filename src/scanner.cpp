#include "scanner.hpp"
#include "token.hpp"
#include "lox.hpp"

#include <map>
#include <string>
#include <vector>

  #include <iostream>
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


Scanner::Scanner(std::string source) : source(source) {}

std::vector<Token> Scanner::scan_tokens() {
    while (!is_at_end()) {
      // Invariant: All lexemes before current have been scanned
      start = current;
      scan_token();
    }

    tokens.push_back(Token(END_OF_FILE, "", NULL, line));
    return tokens;
}


bool Scanner::is_at_end() {
  return current >= source.length();
}

void Scanner::scan_token() {
  char c = advance();

  switch (c) {
    case '(': add_token(LEFT_PAREN); break;
    case ')': add_token(RIGHT_PAREN); break;
    case '{': add_token(LEFT_BRACE); break;
    case '}': add_token(RIGHT_BRACE); break;
    case ',': add_token(COMMA); break;
    case '.': add_token(DOT); break;
    case '-': add_token(MINUS); break;
    case '+': add_token(PLUS); break;
    case ';': add_token(SEMICOLON); break;
    case '*': add_token(STAR); break;
    case '!': add_token(match('=') ? BANG_EQUAL : BANG); break;
    case '=': add_token(match('=') ? EQUAL_EQUAL : EQUAL); break;
    case '<': add_token(match('=') ? LESS_EQUAL : LESS); break;
    case '>': add_token(match('=') ? GREATER_EQUAL : GREATER); break; 
    default:
      Lox::error(line, "Unexpected character.");
      break;
  }
}


char Scanner::advance() {
  return source[current++];
}


void Scanner::add_token(TokenType type) {
  add_token(type, NULL);
}

void Scanner::add_token(TokenType type, void *literal) {
  std::string text = source.substr(start, current - start);
  tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected) {
  if (is_at_end() || source[current] != expected) return false;

  current++;
  return true;
}

// Stubs, so the code compiles
bool Scanner::is_alpha(char c) { return true; }
bool Scanner::is_alphanumeric(char c) { return true; }
bool Scanner::is_digit(char c) { return true; }
char Scanner::peek() { return 'a'; }
char Scanner::peek_next() { return 'a'; }
void Scanner::string() {}
void Scanner::number() {}
void Scanner::identifier() {}

