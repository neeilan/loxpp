#include "parser.h"
#include "lox.hpp"
#include "token.hpp"

#include <memory>
#include <vector>


Expr* Parser::parse() {
    try {
        return expression();
    } catch (ParseErr) {
        return (nullptr);
    }
}

Expr* Parser::expression() {
    return equality();
}

Expr* Parser::equality() {
    Expr* expr = comparison();

    while (match(std::vector<TokenType >(BANG_EQUAL, EQUAL_EQUAL))) { // todo: fix this constructor
        Token op = previous();
        Expr* right = comparison();
        expr = (new Binary(*expr, op, *right));

    }

    return expr;
}

bool Parser::match(const std::vector<TokenType>& types) {
    for (const TokenType& type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(const TokenType& type) {
    if (at_end()) return false;

    return peek().type == type;
}

Token& Parser::advance() {
    if (!at_end()) current++;
    return previous();
}

bool Parser::at_end() {
    return peek().type == END_OF_FILE;
}

/* Current (unconsumed) token */
Token& Parser::peek() {
    return tokens[current];
}

/* Most recently consumed token */
Token& Parser::previous() {
    return tokens[current - 1];
}

Expr* Parser::comparison() {
    Expr* expr = addition();

    while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
        Token& op = previous();
        Expr* right = addition();
        expr = (new Binary(*expr, op, *right));
    }

    return expr;
}

Expr* Parser::addition() {
    Expr* expr = multiplication();

    while (match({ MINUS, PLUS })) {
        Token& op = previous();
        Expr* right = multiplication();
        expr = (new Binary(*expr, op, *right));
    }

    return expr;

}

Expr* Parser::multiplication() {
    Expr* expr = unary();

    while (match({ STAR, SLASH })) {
        Token& op = previous();
        Expr* right = unary();
        expr = (new Binary(*expr, op, *right));
    }

    return expr;
}

Expr* Parser::unary() {
    if (match({ BANG, MINUS })) {
        Token& op = previous();
        Expr* right = unary(); /* Unary is right-recursive */
        return (new Unary(op, *right));
    }

    return primary();
}

Expr* Parser::primary() {
    if (match({FALSE}))     return new BoolLiteral(false);
    if (match({TRUE}))      return new BoolLiteral(true);
    if (match({NIL}))       return new StrLiteral("nil", true);
    if (match({NUMBER}))    return new NumLiteral(stod(previous().literal));
    if (match({STRING}))    return new StrLiteral(previous().literal);
    if (match({LEFT_PAREN})) {
        Expr* expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return (new Grouping(*expr));
    }
    throw error(peek(), "Expect expression.");
}

/* Error handling and recovery */

Token& Parser::consume(TokenType type, std::string msg) {
    if (check(type)) return advance();
    throw error(peek(), msg); /* Report error with current token */
}

ParseErr Parser::error(Token token, std::string msg) {
    Lox::error(token, msg);
    return ParseErr(msg);

}
void Parser::synchronize() {
    advance();

    while (!at_end()) {
        switch (peek().type) {
            case CLASS:
            case FUN:
            case IF:
            case FOR:
            case WHILE:
            case VAR:
            case PRINT:
            case RETURN:
                return;
            default:
                break;
        }

        advance();
    }
}