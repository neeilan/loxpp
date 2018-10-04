#include <iostream>

#include "ast_deleter.hpp"
#include "interpreter.hpp"

void AstDeleter::recursive_delete(const std::vector<Stmt *> &statements)
{
    for (const Stmt *stmt : statements)
    {
        stmt->accept(this);
    }

    for (const Stmt *stmt : stmts_to_delete)
    {
        delete stmt;
    }

    for (const Expr *expr : exprs_to_delete)
    {
        delete expr;
    }
}

void AstDeleter::visit(const VarStmt *stmt)
{
    stmt->expression->accept(this);
    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const ClassStmt *stmt)
{
    for (const Stmt *method : stmt->methods)
    {
        method->accept(this);
    }

    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const ExprStmt *stmt)
{
    stmt->expression->accept(this);
    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const BlockStmt *stmt)
{
    for (const Stmt *inner_statement : stmt->block_contents)
    {
        inner_statement->accept(this);
    }

    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const PrintStmt *stmt)
{
    stmt->expression->accept(this);
    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const ReturnStmt *stmt)
{

    if (stmt->value)
    {
        stmt->value->accept(this);
    }
    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const WhileStmt *stmt)
{
    stmt->condition->accept(this);
    stmt->body->accept(this);
    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const FuncStmt *stmt)
{
    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const IfStmt *stmt)
{
    stmt->condition->accept(this);
    stmt->then_branch->accept(this);

    if (stmt->else_branch)
        stmt->else_branch->accept(this);

    stmts_to_delete.insert(static_cast<const Stmt *>(stmt));
}

void AstDeleter::visit(const Binary *expr)
{
    expr->left.accept(this);
    expr->right.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const StrLiteral *expr)
{
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const NumLiteral *expr)
{
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const BoolLiteral *expr)
{
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Grouping *expr)
{
    expr->expression.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Unary *expr)
{
    expr->right.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Variable *expr)
{
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Assignment *expr)
{
    expr->value.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Logical *expr)
{
    expr->left.accept(this);
    expr->right.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Call *expr)
{
    expr->callee.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Get *expr)
{
    expr->callee.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Set *expr)
{
    expr->callee.accept(this);
    expr->value.accept(this);
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const This *expr)
{
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}

void AstDeleter::visit(const Lambda *expr)
{
    for (Stmt *stmt : expr->body)
    {
        stmt->accept(this);
    }
    exprs_to_delete.insert(static_cast<const Expr *>(expr));
}
