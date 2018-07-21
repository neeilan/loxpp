#ifndef LOXPP_VISITOR_H
#define LOXPP_VISITOR_H

#include <string>

#include "expr.hpp"

class Expr;
class Binary;
class Grouping;
class Literal;
class Unary;


template <class T>
class Visitor {
public:
    virtual ~Visitor() = 0;
    virtual T visit(Unary*) = 0;
    virtual T visit(Binary*) = 0;
    virtual T visit(Grouping*) = 0;
    virtual T visit(Literal*) = 0;
};

#endif //LOXPP_VISITOR_H
