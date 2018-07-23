#include <map>
#include <string>
#include <interpreter.h>

#include "environment.hpp"
#include "interpreter_result.hpp"
#include "token.hpp"

void Environment::define(std::string name, InterpreterResult value) {
    values[name] = value;
}

InterpreterResult Environment::get(Token name) {
    if (values.count(name.lexeme) > 0) {
        return values[name.lexeme];
    }
    throw RuntimeErr(name, "Undefined variable '" + name.lexeme + "'.");
}