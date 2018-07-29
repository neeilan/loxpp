#ifndef LOXPP_SRC_EXPR_H_
#define LOXPP_SRC_EXPR_H_

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "token.hpp"
#include "visitor.h"

#include <memory>
#include <string>
#include <vector>

using std::shared_ptr;

class Expr {
public:
    virtual void accept(ExprVisitor<void>* visitor) const = 0;
    virtual std::string accept(ExprVisitor<std::string>* visitor) const = 0;
    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const = 0;
    virtual bool lvalue() const { return false; }
    virtual bool is_object_field() const { return false; }
    virtual bool callable() const { return false; }
    virtual ~Expr() {};
};


class Binary : public Expr {
public:
    Binary(Expr& left, Token op, Expr& right)
            : left(left), op(op), right(right) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    const Expr& left;
    const Token op;
    const Expr& right;
};


class Grouping : public Expr {
public:
    explicit Grouping(Expr& expression) : expression(expression) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
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

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
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

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    bool nil;
    double value;
};

class BoolLiteral : public Expr {
public:
    explicit  BoolLiteral(bool value) : value(value) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    bool value;
};


class Unary : public Expr {
public:
    Unary(Token op, Expr& right)
            : op(op), right(right) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    const Token op;
    const Expr& right;
};

class This : public Expr {
public:
    This(Token keyword)
            : keyword(keyword) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    const Token keyword;
};

class Variable : public Expr {
public:
    Variable(Token name)
            : name(name) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    virtual bool lvalue() const { return true; }

    const Token name;
};

class Assignment : public Expr {
public:
    Assignment(Token name, Expr& value)
            : name(name), value(value) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
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

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    const Expr& left;
    const Token op;
    const Expr& right;
};

class Call : public Expr {
public:
    Call(Expr& callee, Token paren, std::vector<Expr*> args)
            : callee(callee),
              paren(paren),
              args(args) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    const Expr& callee;
    const Token paren;
    const std::vector<Expr*> args;
};

class Get : public Expr {
public:
    Get(Expr& callee, Token name)
            : callee(callee),
              name(name) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    virtual bool is_object_field() const { return true; }

    Expr& callee;
    const Token name;
};

class Set : public Expr {
public:
    Set(Expr& callee, Token name, Expr& value)
            : callee(callee),
              name(name),
              value(value) {}

    virtual void accept(ExprVisitor<void>* visitor) const {
        return visitor->visit(this);
    }

    virtual std::string accept(ExprVisitor<std::string>* visitor) const {
        return visitor->visit(this);
    }

    virtual shared_ptr<InterpreterResult> accept(ExprVisitor<shared_ptr<InterpreterResult> >* visitor) const {
        return visitor->visit(this);
    }

    Expr& callee;
    const Token name;
    const Expr& value;
};

#endif

