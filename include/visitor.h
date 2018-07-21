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
    virtual T visit(const Unary&) = 0;
    virtual T visit(const Binary&) = 0;
    virtual T visit(const Grouping&) = 0;
    virtual T visit(const Literal&) = 0;
};

#endif //LOXPP_VISITOR_H
