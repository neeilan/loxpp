#ifndef LOXPP_INTERPRETER_H
#define LOXPP_INTERPRETER_H

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "token.hpp"
#include "expr.hpp"
#include "interpreter_result.hpp"
#include "visitor.h"
#include "stmt.hpp"
#include "environment.hpp"


class RuntimeErr : public std::runtime_error {
public:
    RuntimeErr(Token token, const std::string msg) : std::runtime_error(msg), token(token) {}

    Token token;
};

class Interpreter : public ExprVisitor<InterpreterResult>, public StmtVisitor {
public:
    void interpret(const std::vector<Stmt*>& statements);
    void resolve(const Expr* expr, int depth);
    ~Interpreter() {}


protected:
    InterpreterResult visit(const Binary* expr);
    InterpreterResult visit(const StrLiteral* expr);
    InterpreterResult visit(const NumLiteral* expr);
    InterpreterResult visit(const BoolLiteral* expr);
    InterpreterResult visit(const Grouping* expr);
    InterpreterResult visit(const Unary* expr);
    InterpreterResult visit(const Variable* expr);
    InterpreterResult visit(const Assignment* expr);
    InterpreterResult visit(const Logical* expr);
    InterpreterResult visit(const Call* expr);
    InterpreterResult visit(const Get* expr);
    InterpreterResult visit(const Set* expr);

    void visit(const BlockStmt*);
    void visit(const ExprStmt*);
    void visit(const PrintStmt*);
    void visit(const VarStmt*);
    void visit(const ClassStmt*);
    void visit(const IfStmt*);
    void visit(const WhileStmt*);
    void visit(const FuncStmt*);
    void visit(const ReturnStmt*);


private:
    friend class InterpreterResult;

    Environment globals;
    Environment* environment = &globals;
    std::map<const Expr*, int> locals;
    InterpreterResult lookup_variable(const Token name, const Expr* expr);

    InterpreterResult return_val;
    void execute(const Stmt* stmt);
    void execute(const std::vector<Stmt*> stmts, Environment* environment1);
    InterpreterResult evaluate(const Expr& expr);
    bool is_truthy(const InterpreterResult& expr);
    bool is_equal(const InterpreterResult& left, const InterpreterResult& right);
    void check_numeric_operand(const Token op, const InterpreterResult& right);
    void check_numeric_operands(const Token op, const InterpreterResult& left, const InterpreterResult& right);
};

#endif //LOXPP_INTERPRETER_H
