#ifndef LOXPP_PARSER_H
#define LOXPP_PARSER_H

#include <vector>

#include "token.hpp"
#include "expr.hpp"

class ParseErr;

class Parser {
public:
    Parser(std::vector<Token>& tokens) : tokens(tokens) {}
    Expr parse();
private:
    std::vector<Token> tokens;
    Expr expression();
    Expr equality();
    bool match(std::vector<TokenType> types);
    bool check(TokenType type);
    Token advance();
    bool at_end();
    Token peek();
    Token previous();
    Expr addition();
    Expr multiplication();
    Expr unary();
    Expr primary();
    Token consume(TokenType type, std::string msg);
    ParseErr error(Token token, std::string msg);
    void synchronize();
};


#endif //LOXPP_PARSER_H
