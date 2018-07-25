#ifndef LOXPP_SRC_Stmt_H_
#define LOXPP_SRC_Stmt_H_

#include <string>
#include <vector>

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "token.hpp"
#include "expr.hpp"
#include "visitor.h"


class Stmt {
public:
    virtual void accept(StmtVisitor *visitor) const = 0;
};

class ExprStmt : public Stmt {
public:
    explicit ExprStmt(const Expr* expression)
            : expression(expression) {}

    virtual void accept(StmtVisitor *visitor) const {
        visitor->visit(this);
    }

    const Expr* expression = nullptr;
};

class PrintStmt : public  Stmt {
public:
    explicit PrintStmt(const Expr* expression)
            : expression(expression) {}

    virtual void accept(StmtVisitor *visitor) const {
        visitor->visit(this);
    }

    const Expr* expression = nullptr;

};

class VarStmt : public Stmt {
public:
    explicit  VarStmt(const Token name, const Expr* initializer)
            : name(name),
              expression(initializer) {}

    virtual void accept(StmtVisitor *visitor) const {
        visitor->visit(this);
    }

    const Token name;
    const Expr* expression = nullptr;
};

class BlockStmt : public Stmt {
public:
    explicit BlockStmt(std::vector<Stmt*> block_contents)
            : block_contents(block_contents) {}

    virtual void accept(StmtVisitor *visitor) const {
        visitor->visit(this);
    }

    std::vector<Stmt*> block_contents;
};

class IfStmt : public Stmt {
public:
    explicit IfStmt(Expr* condition, Stmt* then_branch, Stmt* else_branch)
            : condition(condition),
              then_branch(then_branch),
              else_branch(else_branch) {}

    virtual void accept(StmtVisitor *visitor) const {
        visitor->visit(this);
    }

    const Expr* condition;
    const Stmt* then_branch;
    const Stmt* else_branch;
};

#endif

