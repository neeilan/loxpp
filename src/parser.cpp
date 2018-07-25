#include "parser.h"
#include "lox.hpp"
#include "token.hpp"
#include "stmt.hpp"

#include <memory>
#include <vector>

std::vector<Stmt*> Parser::parse() {
    std::vector<Stmt*> statements;

    while (!at_end()) {
        try {
            statements.push_back(declaration());
        } catch  (ParseErr) {
            synchronize();
        }
    }

    return statements;
}


Stmt* Parser::declaration() {
    if (match({VAR})) {
        return var_declaration();
    } else {
        return statement();
    }
}

Stmt* Parser::var_declaration() {
    Token name = consume(IDENTIFIER, "Expect variable name.");
    Expr* initializer = new StrLiteral("nil", true);

    if (match({EQUAL})) {
        initializer = expression();
    }
    consume(SEMICOLON, "Expect ';' after variable declaration.");
    return new VarStmt(name, initializer);
}

Stmt* Parser::statement() {
    if (match({PRINT})) return print_statement();
    if (match({LEFT_BRACE})) return block_statement();

    return expression_statement();
}

Stmt* Parser::print_statement() {
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return new PrintStmt(value);
}

Stmt* Parser::block_statement() {
    std::vector<Stmt*> stmts;

    while (!check(RIGHT_BRACE) && !at_end()) {
        stmts.push_back(declaration());
    }

    consume(RIGHT_BRACE, "Expect '}' after block.");

    return new BlockStmt(stmts);
}

Stmt* Parser::expression_statement() {
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after expression.");
    return new ExprStmt(value);
}


Expr* Parser::expression() {
    return assignment();
}


Expr* Parser::assignment() {
    // Don't have a lot of lookahead, so use a 'trick' here:
    // All assignment targets are valid exprs (ex - 'a.prop.b')
    // so parse LHS as an Expr and check that it's an l-value.
    Expr* expr = equality();

    if (match({EQUAL})) {
        Token equals = previous();
        Expr* value = assignment(); // right-associative, so recurse

        if (expr->lvalue()) {
            Variable* variable = dynamic_cast<Variable*>(expr);
            return new Assignment(variable->name, *value);
        }

        Lox::error(equals, "Invalid assignment target.");
    }

    // If no assignment found, fall through to
    // the higher-precedence, valid Expr.
    return expr;
}

Expr* Parser::equality() {
    Expr* expr = comparison();

    while (match({BANG_EQUAL, EQUAL_EQUAL})) {
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
    // todo: this can be a switch
    if (match({FALSE}))         return new BoolLiteral(false);
    if (match({TRUE}))          return new BoolLiteral(true);
    if (match({NIL}))           return new StrLiteral("nil", true);
    if (match({NUMBER}))        return new NumLiteral(stod(previous().literal));
    if (match({STRING}))        return new StrLiteral(previous().literal);
    if (match({IDENTIFIER}))    return new Variable(previous());
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