#include <map>
#include <string>
#include <interpreter.h>

#include "environment.hpp"
#include "interpreter_result.hpp"
#include "token.hpp"

void Environment::define(std::string name, InterpreterResult &value) {
    values[name] = value;
}

InterpreterResult Environment::get(const Token name) {
    if (values.count(name.lexeme) > 0) {
        return values[name.lexeme];
    }

    if (enclosing) {
        return enclosing->get(name);
    }

    throw RuntimeErr(name, "Undefined variable '" + name.lexeme + "'.");
}

InterpreterResult Environment::get_at(int distance, const Token name) {
    return (ancestor(distance)->values)[name.lexeme];
}

void Environment::assign_at(int distance, const Token name, InterpreterResult value) {
    ancestor(distance)->values.at(name.lexeme) = value;
}

Environment* Environment::ancestor(int distance) {
//    if (distance == 0) return this;

    Environment* curr_environment = this;
    for (int i = 0; i < distance; i++) {
        curr_environment = curr_environment->enclosing;
    }

    return curr_environment;
}

void Environment::assign(const Token name, InterpreterResult &value) {
    if (values.count(name.lexeme) > 0) {
        values[name.lexeme] = value;
        return;
    }

    if (enclosing) {
        enclosing->assign(name, value);
        return;
    }

    throw RuntimeErr(name, "Undefined assignment target '" + name.lexeme + "'.");
}
