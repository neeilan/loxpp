#ifndef LOXPP_UNARYEXPR_H
#define LOXPP_UNARYEXPR_H

#include "expr.hpp"

class unary_expr {
public:
    unary_expr(Token op, Expr right) : op(op), right(right) {}
    Token op;
    Expr right;
};

#endif //LOXPP_UNARYEXPR_H
