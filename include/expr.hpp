#ifndef LOXPP_SRC_EXPR_H_
#define LOXPP_SRC_EXPR_H_

#include "token.hpp"

class Expr {
};


class Binary: public Expr {
public:
  Binary(Expr left, Token operator, Expr right);

private:
    const Expr left;
    const Token operator;
    const Expr right;
};


class Grouping: public Expr {
public:
  Grouping(Expr expression);

private:
    Expr expression;
};


class Literal: public Expr {
public:
  Literal(void *value);

private:
    void *value;
};


class Unary: public Expr {
public:
  Unary(Token operator, Expr right);

private:
    const Token operator;
    const Expr right;
};

#endif

