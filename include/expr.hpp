#ifndef LOXPP_SRC_EXPR_H_
#define LOXPP_SRC_EXPR_H_

#include "token.hpp"

#include <string>

class Expr {
};


class Binary : public Expr {
public:
    Binary(Expr left, Token op, Expr right)
            : left(left), op(op), right(right) {}

private:
    const Expr left;
    const Token op;
    const Expr right;
};


class Grouping : public Expr {
public:
    Grouping(Expr expression) : expression(expression) {}

private:
    Expr expression;
};


class Literal : public Expr {
public:
    Literal(std::string value) : str_value(value) {}

    Literal(double value) : num_value(value) {}

private:
    std::string str_value;
    double num_value;
};


class Unary : public Expr {
public:
    Unary(Token op, Expr right)
            : op(op), right(right) {}

private:
    const Token op;
    const Expr right;
};

#endif

