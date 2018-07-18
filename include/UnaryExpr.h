//
// Created by Neeilan Selvalingam on 7/17/18.
//

#ifndef LOXPP_UNARYEXPR_H
#define LOXPP_UNARYEXPR_H

#include "expr.hpp"

class UnaryExpr {
public:
    UnaryExpr(Token op, Expr right) : op(op), right(right) {}
    Token op;
    Expr right;
};

#endif //LOXPP_UNARYEXPR_H
