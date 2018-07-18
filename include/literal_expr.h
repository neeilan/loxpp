#ifndef LOXPP_LITERAL_EXPR_H
#define LOXPP_LITERAL_EXPR_H

#include "expr.hpp"
#include "literal_value.hpp"

class LiteralExpr {
public:
    LiteralExpr(LiteralValue value) : value(value) {}
    LiteralValue value;
};

#endif //LOXPP_LITERAL_EXPR_H
