#ifndef LOXPP_SRC_Stmt_H_
#define LOXPP_SRC_Stmt_H_

#include <string>
#include <vector>

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "token.hpp"
#include "expr.hpp"
#include "visitor.h"


class Stmt {
public:
    explicit Stmt(const Expr* expression, bool print=false)
    : expression(expression),
      print(print),
      name(Token(NIL, "nil", "nil", 0)){}

    // Variable statement
    explicit  Stmt(const Token name, const Expr* initializer)
            : var(true),
              name(name),
              expression(initializer) {}

    // Block
    explicit Stmt(std::vector<Stmt> block_contents)
            : block(true),
              block_contents(block_contents),
              name(Token(NIL, "nil", "nil", 0)) {}

    void accept(StmtVisitor* visitor) const {
        visitor->visit(*this);
    }

    bool print = false;
    bool var = false;
    bool block = false;

    std::vector<Stmt> block_contents;

    const Expr* expression = nullptr;
    const Token name;

};


#endif

