#include <string>

#include "lox.hpp"
#include "resolver.hpp"

void Resolver::resolve(const std::vector<Stmt *> statements) {
    for (const Stmt* stmt : statements) {
        resolve(stmt);
    }
}

void Resolver::resolve(const Stmt *stmt) {
    stmt->accept(this);
}

void Resolver::resolve(const Expr *expr) {
    expr->accept(this);
}

void Resolver::visit(const BlockStmt* stmt) {
    begin_scope();
    resolve(stmt->block_contents);
    end_scope();
}

void Resolver::visit(const VarStmt *stmt) {
    declare(stmt->name);
    if (stmt->expression) {
        resolve(stmt->expression);
    }
    define(stmt->name);
}

void Resolver::visit(const Variable *expr) {
    if (!scopes.empty()
        && scopes.back()->count(expr->name.lexeme) > 0
        && scopes.back()->at(expr->name.lexeme) == false) {
        Lox::error(expr->name,
                  "Cannot read local variable in its own initializer.");
    }

    resolve_local(expr, expr->name);
}

void Resolver::visit(const Assignment *expr) {
    resolve(&expr->value); // resolve RHS, in case it references other vars
    resolve_local(expr, expr->name); // resolve the var being assigned to
}

void Resolver::visit(const FuncStmt *stmt) {
    declare(stmt->name);
    define(stmt->name);
    resolve_fn(stmt);
}

void Resolver::visit(const ClassStmt* stmt) {
    declare(stmt->name);
    define(stmt->name);
}

void Resolver::resolve_local(const Expr *expr, const Token name) {
    for (int i = scopes.size() - 1; i >= 0; i--) {
        if (scopes[i]->count(name.lexeme) > 0) {
            /*
             * Tell interpreter the # of scopes between current scope and the scope
             * where the variable should resolve. If the variable was found in the
             * current scope, pass in 0. In the immediately enclosing scope, 1
             */
            interpreter->resolve(expr, scopes.size() - 1 - i);
            return;
        }
    }

    // Not found. Assume it is global.

}

void Resolver::resolve_fn(const FuncStmt *fn) {
    begin_scope();

    for (const Token& param : fn->parameters) {
        declare(param);
        define(param);
    }

    resolve(fn->body);
    end_scope();
}

void Resolver::begin_scope() {
    scopes.push_back(new std::map<std::string, bool>());
}

void Resolver::end_scope() {
    //delete scopes.back();
    scopes.pop_back();
}

void Resolver::define(const Token name) {
    if (scopes.empty()) return;

    // mark as initialized & available for use
    std::map<std::string, bool>* scope = scopes.back();

    if (scope->count(name.lexeme) > 0) {
        scope->erase(name.lexeme);
    }

    scope->insert(std::pair<std::string, bool>(name.lexeme, true));
}

void Resolver::declare(const Token name) {
    if (scopes.empty()) return;

    // mark as declared but uninitialized for use
    std::map<std::string, bool>* scope = scopes.back();
    scope->insert(std::pair<std::string, bool>(name.lexeme, false));
}

// Other syntax tree nodes

// Statements
void Resolver::visit(const ExprStmt* stmt) {
    resolve(stmt->expression);
}

void Resolver::visit(const IfStmt* stmt) {
    resolve(stmt->condition);

    resolve(stmt->then_branch);

    if (stmt->else_branch)
        resolve(stmt->else_branch);
}

void Resolver::visit(const PrintStmt* stmt) {
    resolve(stmt->expression);
}

void Resolver::visit(const ReturnStmt* stmt) {
    if (stmt->value)
        resolve(stmt->value);
}

void Resolver::visit(const WhileStmt* stmt) {
    resolve(stmt->condition);
    resolve(stmt->body);
}

// Expressions

void Resolver::visit(const Binary* expr) {
    resolve(&expr->left);
    resolve(&expr->right);
}

void Resolver::visit(const Call *expr) {
    resolve(&expr->callee);

    for (const Expr* arg : expr->args) {
        resolve(arg);
    }
}

void Resolver::visit(const Get *expr) {
    resolve(&expr->callee);
}

void Resolver::visit(const Set *expr) {
    resolve(&expr->value);
    resolve(&expr->callee);
}

void Resolver::visit(const Grouping *expr) {
    resolve(&expr->expression);
}

void Resolver::visit(const Logical *expr) {
    resolve(&expr->left);
    resolve(&expr->right);
}

void Resolver::visit(const Unary *expr) {
    resolve(&expr->right);
}

// since literals contain no variables, nothing to be done
void Resolver::visit(const BoolLiteral *expr) {}
void Resolver::visit(const NumLiteral *expr) {}
void Resolver::visit(const StrLiteral *expr) {}

