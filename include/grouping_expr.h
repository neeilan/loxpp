#ifndef LOXPP_GROUPING_EXPR_H
#define LOXPP_GROUPING_EXPR_H

#include "expr.hpp"

class GroupingExpr {
public:
    GroupingExpr(Expr expression) : expression(expression) {}
    Expr expression;
};

#endif //LOXPP_GROUPING_EXPR_H
