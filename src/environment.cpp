#include <map>
#include <string>
#include <interpreter.h>

#include "environment.hpp"
#include "interpreter_result.hpp"
#include "token.hpp"

void Environment::define(std::string name, InterpreterResult &value) {
    values[name] = value;
}

InterpreterResult Environment::get(Token name) {
    if (values.count(name.lexeme) > 0) {
        return values[name.lexeme];
    }

    if (enclosing) {
        return enclosing->get(name);
    }

    throw RuntimeErr(name, "Undefined variable '" + name.lexeme + "'.");
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
