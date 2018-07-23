#ifndef LOXPP_INTERPRETER_H
#define LOXPP_INTERPRETER_H

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
    void interpret(const std::vector<Stmt>& statements);
    ~Interpreter() {}

protected:
    InterpreterResult visit(const Binary* expr);
    InterpreterResult visit(const StrLiteral* expr);
    InterpreterResult visit(const NumLiteral* expr);
    InterpreterResult visit(const BoolLiteral* expr);
    InterpreterResult visit(const Grouping* expr);
    InterpreterResult visit(const Unary* expr);
    InterpreterResult visit(const Variable* expr);

    void visit(const Stmt& stmt);

private:
    Environment environment;
    void execute(const Stmt& stmt);
    InterpreterResult evaluate(const Expr& expr);
    bool is_truthy(const InterpreterResult& expr);
    bool is_equal(const InterpreterResult& left, const InterpreterResult& right);
    void check_numeric_operand(const Token op, const InterpreterResult& right);
    void check_numeric_operands(const Token op, const InterpreterResult& left, const InterpreterResult& right);
};

#endif //LOXPP_INTERPRETER_H
