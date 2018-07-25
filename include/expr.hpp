#ifndef LOXPP_SRC_EXPR_H_
#define LOXPP_SRC_EXPR_H_

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "token.hpp"
#include "visitor.h"

#include <string>

class Expr {
public:
    virtual std::string accept(ExprVisitor<std::string>* visitor) const = 0;
    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const = 0;
    virtual bool lvalue() const { return false; }
    virtual ~Expr() {};
};


class Binary : public Expr {
public:
    Binary(Expr& left, Token op, Expr& right)
            : left(left), op(op), right(right) {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    const Expr& left;
    const Token op;
    const Expr& right;
};


class Grouping : public Expr {
public:
    explicit Grouping(Expr& expression) : expression(expression) {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    const Expr& expression;
};

class StrLiteral : public Expr {
public:
    explicit StrLiteral(const std::string& value, bool nil = false) :
            value(value),
            nil(nil)
    {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    bool nil;
    std::string value;
};

class NumLiteral : public Expr {
public:
    explicit NumLiteral(double value, bool nil = false) :
            value(value),
            nil(nil)
    {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    bool nil;
    double value;
};

class BoolLiteral : public Expr {
public:
    explicit  BoolLiteral(bool value) : value(value) {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    bool value;
};


class Unary : public Expr {
public:
    Unary(Token op, Expr& right)
            : op(op), right(right) {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    const Token op;
    const Expr& right;
};

class Variable : public Expr {
public:
    Variable(Token name)
            : name(name) {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    virtual bool lvalue() const { return true; }

    const Token name;
};

class Assignment : public Expr {
public:
    Assignment(Token name, Expr& value)
            : name(name), value(value) {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    const Token name;
    const Expr& value;
};


class Logical : public Expr {
public:
    Logical(Expr& left, Token op, Expr& right)
            : left(left),
              op(op),
              right(right) {}

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual InterpreterResult accept(ExprVisitor<InterpreterResult>* visitor) const {
        return visitor->visit(this);
    }

    const Expr& left;
    const Token op;
    const Expr& right;
};

#endif

