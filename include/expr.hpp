#ifndef LOXPP_SRC_EXPR_H_
#define LOXPP_SRC_EXPR_H_

#include "token.hpp"

#include <string>

class Expr {
};


class Binary : public Expr {
public:
    Binary(Expr left, Token operator, Expr right)
            : left(left), operator(

    operator), right(right) {}

private:
    const Expr left;
    const Token operator;
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
    std::string str_value = NULL;
    double num_value = NULL;
};


class Unary : public Expr {
public:
    Unary(Token operator, Expr right)
            : operator(

    operator), right(right) {}

private:
    const Token operator;
    const Expr right;
};

#endif

