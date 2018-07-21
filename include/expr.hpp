#ifndef LOXPP_SRC_EXPR_H_
#define LOXPP_SRC_EXPR_H_

#include "token.hpp"
#include "visitor.h"

#include <string>


class Expr {
public:
    virtual std::string accept(Visitor<std::string>* visitor) = 0;
    virtual ~Expr() {};
};


class Binary : public Expr {
public:
    Binary(Expr left, Token op, Expr right)
            : left(left), op(op), right(right) {}

    std::string accept(Visitor<std::string>* visitor) { return visitor->visit(this); }

    const Expr& left;
    const Token op;
    const Expr& right;
};


class Grouping : public Expr {
public:
    explicit Grouping(Expr& expression) : expression(expression) {}

    std::string accept(Visitor<std::string>* visitor) { return visitor->visit(this); }

    const Expr& expression;
};

class Literal : public Expr {
public:
    explicit Literal(const std::string& value) : value(value) {}

    std::string accept(Visitor<std::string>* visitor) { return visitor->visit(this); }

    std::string value;
};


class Unary : public Expr {
public:
    Unary(Token op, Expr& right)
            : op(op), right(right) {}

    std::string accept(Visitor<std::string>* visitor) { return visitor->visit(this); }

    const Token op;
    const Expr& right;
};

#endif

