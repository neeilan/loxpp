#ifndef LOXPP_VISITOR_H
#define LOXPP_VISITOR_H

#include <string>

#include "visitable_types.hpp"
#include "expr.hpp"


class StmtVisitor {
public:
    virtual ~StmtVisitor() {};
    virtual void visit(const BlockStmt*) = 0;
    virtual void visit(const ExprStmt*) = 0;
    virtual void visit(const PrintStmt*) = 0;
    virtual void visit(const VarStmt*) = 0;
    virtual void visit(const IfStmt*) = 0;
    virtual void visit(const WhileStmt*) = 0;
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
    virtual T visit(const Logical*) = 0;
};

#endif //LOXPP_VISITOR_H
