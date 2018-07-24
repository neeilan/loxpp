#ifndef LOXPP_VISITOR_H
#define LOXPP_VISITOR_H

#include <string>

#include "visitable_types.hpp"


class StmtVisitor {
public:
    virtual ~StmtVisitor() {};
    virtual void visit(const Stmt&) = 0;
};

template <class T>
class ExprVisitor {
public:
    virtual ~ExprVisitor() {};
    virtual T visit(const Unary*) = 0;
    virtual T visit(const Binary*) = 0;
    virtual T visit(const Grouping*) = 0;
    virtual T visit(const StrLiteral*) = 0;
    virtual T visit(const NumLiteral*) = 0;
    virtual T visit(const BoolLiteral*) = 0;
    virtual T visit(const Variable*) = 0;
    virtual T visit(const Assignment*) = 0;
};

#endif //LOXPP_VISITOR_H
