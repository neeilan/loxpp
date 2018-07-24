#include <iostream>

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "expr.hpp"
#include "lox.hpp"

inline std::string operator_name(TokenType op) {
    switch (op) {
        case MINUS: return "-";
        case STAR : return "*";
        case PLUS : return "+";
        case SLASH : return "-";
        default: return "UNKNOWN OP";
    }
}


void Interpreter::interpret(const std::vector<Stmt>& statements) {
    try {
        for (const Stmt& stmt : statements) {
            execute(stmt);
        }
    } catch (RuntimeErr err) {
        Lox::runtime_error(err);
    }
}

void Interpreter::execute(const Stmt& stmt) {
    stmt.accept(this);
}


void Interpreter::visit(const Stmt &stmt) {

    InterpreterResult value = evaluate(*stmt.expression);

    if (stmt.var) {
        environment.define(stmt.name.lexeme, value);
        return;
    }

    if (stmt.print) {
        std::cout << InterpreterResult::stringify(value) << std::endl;
    }
}

InterpreterResult Interpreter::evaluate(const Expr &expr) {
    return expr.accept(this);
}

InterpreterResult Interpreter::visit(const Binary* expr) {

    InterpreterResult left = evaluate(expr->left);
    InterpreterResult right = evaluate(expr->right);

    InterpreterResult result;

    switch (expr->op.type) {
        case BANG_EQUAL : {
            result.bool_val = !is_equal(left, right);
            result.kind = InterpreterResult::ResultType::BOOL;
            break;
        }
        case EQUAL_EQUAL : {
            result.bool_val = !is_equal(left, right);
            result.kind = InterpreterResult::ResultType::BOOL;
            break;
        }
        case GREATER : {
            check_numeric_operands(expr->op, left, right);
            result.bool_val = left.num_val > right.num_val;
            result.kind = InterpreterResult::ResultType::BOOL;
            break;
        }
        case GREATER_EQUAL : {
            check_numeric_operands(expr->op, left, right);
            result.bool_val = left.num_val >= right.num_val;
            result.kind = InterpreterResult::ResultType::BOOL;
            break;
        }
        case LESS : {
            check_numeric_operands(expr->op, left, right);
            result.bool_val = left.num_val < right.num_val;
            result.kind = InterpreterResult::ResultType::BOOL;
            break;
        }
        case LESS_EQUAL : {
            check_numeric_operands(expr->op, left, right);
            result.bool_val = left.num_val <= right.num_val;
            result.kind = InterpreterResult::ResultType::BOOL;
            break;
        }
        case MINUS: {
            check_numeric_operands(expr->op, left, right);
            result.num_val = left.num_val - right.num_val;
            result.kind = InterpreterResult::ResultType::NUMBER;
            break;
        }
        case SLASH: {
            check_numeric_operands(expr->op, left, right);
            result.num_val = left.num_val / right.num_val;
            result.kind = InterpreterResult::ResultType::NUMBER;
            break;
        }
        case STAR: {
            check_numeric_operands(expr->op, left, right);
            result.num_val = left.num_val * right.num_val;
            result.kind = InterpreterResult::ResultType::NUMBER;
            break;
        }
        case PLUS : {
            if (left.kind == InterpreterResult::ResultType::NUMBER && right.kind == InterpreterResult::ResultType::NUMBER) {
                result.num_val = left.num_val + right.num_val;
                result.kind = InterpreterResult::ResultType::NUMBER;
                return result;
            }

            if (left.kind == InterpreterResult::ResultType::STR && right.kind == InterpreterResult::ResultType::STR) {
                result.str_val = left.str_val + right.str_val;
                result.kind = InterpreterResult::ResultType ::STR;
                return result;
            }

            throw RuntimeErr(expr->op, "Operands must be two strings or two numbers");
        }
        default:
            break;
    }

    return result;

}

InterpreterResult Interpreter::visit(const StrLiteral* expr) {
    InterpreterResult result;
    result.str_val = expr->value;
    result.kind = InterpreterResult::ResultType::STR;
    return result;
}

InterpreterResult Interpreter::visit(const NumLiteral *expr) {
    InterpreterResult result;
    result.num_val = expr->value;
    result.kind = InterpreterResult::ResultType::NUMBER;
    return result;
}

InterpreterResult Interpreter::visit(const BoolLiteral* expr) {
    InterpreterResult result;
    result.bool_val = expr->value;
    result.kind = InterpreterResult::ResultType::BOOL;
    return result;
}

InterpreterResult Interpreter::visit(const Grouping* expr) {
    return evaluate(expr->expression);
}

InterpreterResult Interpreter::visit(const Unary* expr) {
    InterpreterResult right = evaluate(expr->right);
    InterpreterResult result;

    switch(expr->op.type) {
        case BANG: {
            result.bool_val = !is_truthy(right);
            result.kind = InterpreterResult::ResultType::BOOL;
            return result;
        }
        case MINUS: {
            check_numeric_operand(expr->op, right);
            double val =  -(right.num_val);
            result.num_val = val;
            result.kind = InterpreterResult::ResultType::NUMBER;
            return result;
        }
        default:
            return result; // Unreachable
    }
}

InterpreterResult Interpreter::visit(const Variable *expr) {
    return environment.get(expr->name);
}

InterpreterResult Interpreter::visit(const Assignment *expr) {
    InterpreterResult value = evaluate(expr->value);
    environment.assign(expr->name, value);
    return value; // Allows for statements like: print a = 2; -> "2"
}

bool Interpreter::is_truthy(const InterpreterResult &expr) {
    if (expr.kind == InterpreterResult::ResultType::NIL) {
        return false;
    }
    if (expr.kind == InterpreterResult::ResultType::BOOL) {
        return expr.bool_val;
    }
    return true;
}

bool Interpreter::is_equal(const InterpreterResult &left, const InterpreterResult &right) {

    if (left.kind != right.kind) {
        return false;
    }

    switch (left.kind) {
        case InterpreterResult::ResultType::NIL :
            return true;
        case InterpreterResult::ResultType ::BOOL:
            return left.bool_val == right.bool_val;
        case InterpreterResult::ResultType ::STR:
            return left.str_val == right.str_val;
        case InterpreterResult::ResultType::NUMBER:
            return left.num_val == right.num_val;
        default:
            throw std::runtime_error("Unknown InterpreterResult kind"); // unreachable
    }
}



void Interpreter::check_numeric_operand(const Token op, const InterpreterResult &right) {
    if (right.kind != InterpreterResult::ResultType::NUMBER)
        throw RuntimeErr(op, "Operand must be a number");
}

void Interpreter::check_numeric_operands(const Token op, const InterpreterResult &left,
                                         const InterpreterResult &right) {
    if (left.kind != InterpreterResult::ResultType ::NUMBER
        || right.kind != InterpreterResult::ResultType::NUMBER)
        throw RuntimeErr(op, "Operands must be a number");
}