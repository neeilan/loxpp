#ifndef LOXPP_SRC_Stmt_H_
#define LOXPP_SRC_Stmt_H_

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "token.hpp"
//#include "visitable_types.hpp"
#include "expr.hpp"
#include "visitor.h"

#include <string>

class Stmt {
public:
    explicit Stmt(const Expr* expression, bool print=false)
    : expression(expression), print(print) {}


    void accept(StmtVisitor* visitor) const {
        visitor->visit(*this);
    }

    const Expr* expression;
    bool print = false;

};


#endif

