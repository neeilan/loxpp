#ifndef LOXPP_SRC_Stmt_H_
#define LOXPP_SRC_Stmt_H_

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "token.hpp"
#include "expr.hpp"
#include "visitor.h"

#include <string>

class Stmt {
public:
    explicit Stmt(const Expr* expression, bool print=false)
    : expression(expression),
      print(print),
      name(Token(IDENTIFIER, "", "", 0)){}

    // Variable statement
    explicit  Stmt(const Token name, const Expr* initializer) : name(name), expression(initializer) {}


    void accept(StmtVisitor* visitor) const {
        visitor->visit(*this);
    }

    const Expr* expression = nullptr;
    bool print = false;
    const Token name;

};


#endif

