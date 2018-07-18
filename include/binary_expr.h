#ifndef LOXPP_BINARYEXPR_H
#define LOXPP_BINARYEXPR_H

#include "expr.hpp"
#include "token.hpp"

class BinaryExpr {
public:
    BinaryExpr(Expr left, Token op, Expr right) : left(left), op(op), right(right) {}
    Expr left;
    Token op;
    Expr right;
};


#endif //LOXPP_BINARYEXPR_H
