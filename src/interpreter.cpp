#include <iostream>
#include <memory>

#include "return.hpp"
#include "interpreter.hpp"
#include "interpreter_result.hpp"
#include "runtime_err.hpp"
#include "expr.hpp"
#include "lox.hpp"

using std::shared_ptr;

void Interpreter::resolve(const Expr *expr, int depth)
{
    locals[expr] = depth;
}

void Interpreter::interpret(const std::vector<Stmt *> &statements)
{
    try
    {
        for (const Stmt *stmt : statements)
        {
            execute(stmt);
        }
    }
    catch (RuntimeErr &err)
    {
        Lox::runtime_error(err);
    }
}

void Interpreter::execute(const Stmt *stmt)
{
    stmt->accept(this);
}

void Interpreter::execute(const std::vector<Stmt *> stmts, Environment<shared_ptr<InterpreterResult>> *exec_env)
{
    Environment<shared_ptr<InterpreterResult>> *prev = environment;

    environment = exec_env;

    try
    {
        for (const Stmt *stmt : stmts)
            stmt->accept(this);
    }
    catch (Return &_r)
    {
        environment = prev;
        return;
    }

    delete exec_env;

    environment = prev;
}

void Interpreter::visit(const VarStmt *stmt)
{
    shared_ptr<InterpreterResult> value = evaluate(*stmt->expression);
    environment->define(stmt->name.lexeme, value);
}

void Interpreter::visit(const ClassStmt *stmt)
{
    auto superclass = shared_ptr<InterpreterResult>();

    if (stmt->superclass)
    {
        superclass = evaluate(*stmt->superclass);
        if (superclass->kind != InterpreterResult::ResultType::CLASS)
        {
            throw RuntimeErr(stmt->superclass->name,
                             "Superclass must be a class.");
        }
    }

    shared_ptr<InterpreterResult> sentinel = std::make_shared<InterpreterResult>();
    sentinel->kind = InterpreterResult::ResultType::NIL;

    // Allows references to the class inside its own methods
    environment->define(stmt->name.lexeme, sentinel);

    std::map<std::string, shared_ptr<InterpreterResult>> methods;

    int init_arity = 0;

    for (const Stmt *method : stmt->methods)
    {
        auto _method = static_cast<const FuncStmt *>(method);

        auto _method_impl = std::make_shared<InterpreterResult>();

        _method_impl->kind = InterpreterResult::ResultType::FUNCTION;
        _method_impl->callable = true;
        _method_impl->function = _method;
        _method_impl->arity = _method->parameters.size();
        _method_impl->is_initializer = _method->name.lexeme == "init";

        if (_method->name.lexeme == "init")
            init_arity = _method->parameters.size();

        methods[_method->name.lexeme] = _method_impl;
    }

    auto klass = std::make_shared<InterpreterResult>();

    klass->superclass = superclass;
    klass->kind = InterpreterResult::ResultType::CLASS;
    klass->name = stmt->name.lexeme;
    klass->rt_methods = methods;
    klass->callable = true; // constructor
    klass->arity = init_arity;
    klass->class_def = klass.get();

    environment->assign(stmt->name, klass);
}

void Interpreter::visit(const ExprStmt *stmt)
{
    evaluate(*stmt->expression);
}

void Interpreter::visit(const BlockStmt *stmt)
{
    Environment<shared_ptr<InterpreterResult>> *previous = environment;

    environment = new Environment<shared_ptr<InterpreterResult>>(previous);

    try
    {
        for (const Stmt *inner_statement : stmt->block_contents)
        {
            execute(inner_statement);
        }
    }
    catch (RuntimeErr &err)
    {
        Lox::runtime_error(err);
    };

    delete environment;
    environment = previous;
}

void Interpreter::visit(const PrintStmt *stmt)
{
    shared_ptr<InterpreterResult> value = evaluate(*(stmt->expression));
    std::cout << InterpreterResult::stringify(*value) << std::endl;
}

void Interpreter::visit(const ReturnStmt *stmt)
{

    if (stmt->value)
    {
        return_val = evaluate(*stmt->value);
    }
    else
    {
        shared_ptr<InterpreterResult> nil_val = std::make_shared<InterpreterResult>();
        nil_val->kind = InterpreterResult::NIL;
        return_val = nil_val;
    }
    throw Return();
}

void Interpreter::visit(const WhileStmt *stmt)
{
    while (is_truthy(*evaluate(*stmt->condition)))
    {
        execute(stmt->body);
    }
}

void Interpreter::visit(const FuncStmt *stmt)
{
    shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();
    result->function = stmt;
    result->kind = InterpreterResult::ResultType::FUNCTION;
    result->arity = stmt->parameters.size();
    result->closure = environment;
    result->callable = true;
    environment->define(stmt->name.lexeme, result);
}

shared_ptr<InterpreterResult> Interpreter::evaluate(const Expr &expr)
{
    return expr.accept(this);
}

void Interpreter::visit(const IfStmt *stmt)
{
    if (is_truthy(*evaluate(*stmt->condition)))
    {
        execute(stmt->then_branch);
    }
    else if (stmt->else_branch)
    {
        execute((stmt->else_branch));
    }
}

shared_ptr<InterpreterResult> Interpreter::visit(const Binary *expr)
{

    shared_ptr<InterpreterResult> left = evaluate(expr->left);
    shared_ptr<InterpreterResult> right = evaluate(expr->right);

    shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();

    switch (expr->op.type)
    {
    case BANG_EQUAL:
    {
        result->bool_val = !is_equal(*left, *right);
        result->kind = InterpreterResult::ResultType::BOOL;
        break;
    }
    case EQUAL_EQUAL:
    {
        result->bool_val = is_equal(*left, *right);
        result->kind = InterpreterResult::ResultType::BOOL;
        break;
    }
    case GREATER:
    {
        check_numeric_operands(expr->op, *left, *right);
        result->bool_val = left->num_val > right->num_val;
        result->kind = InterpreterResult::ResultType::BOOL;
        break;
    }
    case GREATER_EQUAL:
    {
        check_numeric_operands(expr->op, *left, *right);
        result->bool_val = left->num_val >= right->num_val;
        result->kind = InterpreterResult::ResultType::BOOL;
        break;
    }
    case LESS:
    {
        check_numeric_operands(expr->op, *left, *right);
        result->bool_val = left->num_val < right->num_val;
        result->kind = InterpreterResult::ResultType::BOOL;
        break;
    }
    case LESS_EQUAL:
    {
        check_numeric_operands(expr->op, *left, *right);
        result->bool_val = left->num_val <= right->num_val;
        result->kind = InterpreterResult::ResultType::BOOL;
        break;
    }
    case MINUS:
    {
        check_numeric_operands(expr->op, *left, *right);
        result->num_val = left->num_val - right->num_val;
        result->kind = InterpreterResult::ResultType::NUMBER;
        break;
    }
    case SLASH:
    {
        check_numeric_operands(expr->op, *left, *right);
        result->num_val = left->num_val / right->num_val;
        result->kind = InterpreterResult::ResultType::NUMBER;
        break;
    }
    case STAR:
    {
        check_numeric_operands(expr->op, *left, *right);
        result->num_val = left->num_val * right->num_val;
        result->kind = InterpreterResult::ResultType::NUMBER;
        break;
    }
    case PLUS:
    {
        if (left->kind == InterpreterResult::ResultType::NUMBER && right->kind == InterpreterResult::ResultType::NUMBER)
        {
            result->num_val = left->num_val + right->num_val;
            result->kind = InterpreterResult::ResultType::NUMBER;
            return result;
        }

        if (left->kind == InterpreterResult::ResultType::STR && right->kind == InterpreterResult::ResultType::STR)
        {
            result->str_val = left->str_val + right->str_val;
            result->kind = InterpreterResult::ResultType ::STR;
            return result;
        }

        throw RuntimeErr(expr->op, "Operands must be two strings or two numbers");
    }
    default:
        break;
    }

    return result;
}

shared_ptr<InterpreterResult> Interpreter::visit(const StrLiteral *expr)
{
    shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();
    result->str_val = expr->value;
    result->kind = expr->nil ? InterpreterResult::ResultType::NIL : InterpreterResult::ResultType::STR;
    return result;
}

shared_ptr<InterpreterResult> Interpreter::visit(const NumLiteral *expr)
{
    shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();
    result->num_val = expr->value;
    result->kind = InterpreterResult::ResultType::NUMBER;
    return result;
}

shared_ptr<InterpreterResult> Interpreter::visit(const BoolLiteral *expr)
{
    shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();
    result->bool_val = expr->value;
    result->kind = InterpreterResult::ResultType::BOOL;
    return result;
}

shared_ptr<InterpreterResult> Interpreter::visit(const Grouping *expr)
{
    return evaluate(expr->expression);
}

shared_ptr<InterpreterResult> Interpreter::visit(const Unary *expr)
{
    shared_ptr<InterpreterResult> right = evaluate(expr->right);
    shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();

    switch (expr->op.type)
    {
    case BANG:
    {
        result->bool_val = !is_truthy(*right);
        result->kind = InterpreterResult::ResultType::BOOL;
        return result;
    }
    case MINUS:
    {
        check_numeric_operand(expr->op, *right);
        double val = -(right->num_val);
        result->num_val = val;
        result->kind = InterpreterResult::ResultType::NUMBER;
        return result;
    }
    default:
        return result; // Unreachable
    }
}

shared_ptr<InterpreterResult> Interpreter::visit(const Variable *expr)
{
    return lookup_variable(expr->name, expr);
}

shared_ptr<InterpreterResult> Interpreter::visit(const Assignment *expr)
{
    shared_ptr<InterpreterResult> value = evaluate(expr->value);

    if (locals.count(expr) == 0)
    {
        globals.assign(expr->name, value);
    }
    else
    {
        int distance = locals[expr];
        environment->assign_at(distance, expr->name, value);
    }

    return value; // Allows for statements like: print a = 2; -> "2"
}

shared_ptr<InterpreterResult> Interpreter::visit(const Logical *expr)
{
    shared_ptr<InterpreterResult> left = evaluate(expr->left);

    if (expr->op.type == OR)
    {
        if (is_truthy(*left))
            return left;
    }
    else
    {
        if (!is_truthy(*left))
            return left; // ex - if (false and true)
    }

    return evaluate(expr->right);
}

shared_ptr<InterpreterResult> Interpreter::visit(const Call *expr)
{
    shared_ptr<InterpreterResult> callee = evaluate(expr->callee);

    if (!callee->callable)
    {
        throw RuntimeErr(expr->paren, "Can only call functions and classes.");
    }

    std::vector<shared_ptr<InterpreterResult>> args;

    if (expr->args.size() != callee->get_arity())
    {
        throw RuntimeErr(expr->paren,
                         "Expected " + std::to_string(callee->get_arity()) + " arguments but got " + std::to_string(expr->args.size()) + ".");
    }

    for (Expr *arg : expr->args)
    {
        args.push_back(evaluate(*arg));
    }

    return callee->call(this, args);
}

shared_ptr<InterpreterResult> Interpreter::visit(const Get *expr)
{
    shared_ptr<InterpreterResult> callee = evaluate(expr->callee);

    if (callee->kind == InterpreterResult::ResultType::INSTANCE)
    {
        return callee->get(expr->name);
    }

    throw RuntimeErr(expr->name, "Only instances have properties.");
}

shared_ptr<InterpreterResult> Interpreter::visit(const Set *expr)
{
    shared_ptr<InterpreterResult> object = evaluate(expr->callee);

    if (object->kind != InterpreterResult::ResultType::INSTANCE)
    {
        throw RuntimeErr(expr->name, "Only instances have fields.");
    }

    shared_ptr<InterpreterResult> value = evaluate(expr->value);

    object->set(expr->name, value);
    return value;
}

shared_ptr<InterpreterResult> Interpreter::visit(const This *expr)
{
    return lookup_variable(expr->keyword, expr);
}

shared_ptr<InterpreterResult> Interpreter::visit(const Lambda *expr)
{
    shared_ptr<InterpreterResult> result = std::make_shared<InterpreterResult>();
    result->function = new FuncStmt(Token(LAMBDA, "lambda", "", 0), expr->parameters, expr->body);
    result->kind = InterpreterResult::ResultType::FUNCTION;
    result->arity = expr->parameters.size();
    result->closure = environment;
    result->callable = true;
    return result;
}

bool Interpreter::is_truthy(const InterpreterResult &expr)
{
    if (expr.kind == InterpreterResult::ResultType::NIL)
    {
        return false;
    }
    if (expr.kind == InterpreterResult::ResultType::BOOL)
    {
        return expr.bool_val;
    } // number?

    return true;
}

bool Interpreter::is_equal(const InterpreterResult &left, const InterpreterResult &right)
{

    if (left.kind != right.kind)
    {
        return false;
    }

    switch (left.kind)
    {
    case InterpreterResult::ResultType::NIL:
        return true;
    case InterpreterResult::ResultType ::BOOL:
        return left.bool_val == right.bool_val;
    case InterpreterResult::ResultType ::STR:
        return left.str_val == right.str_val;
    case InterpreterResult::ResultType::NUMBER:
        return left.num_val == right.num_val;
    case InterpreterResult::ResultType::FUNCTION:
        return left.function == right.function;
    default:
        throw std::runtime_error("Unknown InterpreterResult kind"); // unreachable
    }
}

void Interpreter::check_numeric_operand(const Token op, const InterpreterResult &right)
{
    if (right.kind != InterpreterResult::ResultType::NUMBER)
        throw RuntimeErr(op, "Operand must be a number");
}

void Interpreter::check_numeric_operands(const Token op, const InterpreterResult &left,
                                         const InterpreterResult &right)
{
    if (left.kind != InterpreterResult::ResultType ::NUMBER || right.kind != InterpreterResult::ResultType::NUMBER)
        throw RuntimeErr(op, "Operands must be a number");
}

shared_ptr<InterpreterResult> Interpreter::lookup_variable(const Token name, const Expr *expr)
{
    if (locals.count(expr) == 0)
    {
        return globals.get(name);
    }

    int distance = locals[expr];
    return environment->get_at(distance, name);
}
