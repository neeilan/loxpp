#ifndef LOXPP_VISITOR_H
#define LOXPP_VISITOR_H

#include <string>

#include "expr.hpp"
#include "expr_subtypes.hpp"

template <class T>
class Visitor {
public:
    virtual ~Visitor() {};
    virtual T visit(const Unary*) = 0;
    virtual T visit(const Binary*) = 0;
    virtual T visit(const Grouping*) = 0;
    virtual T visit(const StrLiteral*) = 0;
    virtual T visit(const NumLiteral*) = 0;
    virtual T visit(const BoolLiteral*) = 0;
};

#endif //LOXPP_VISITOR_H
