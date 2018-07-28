#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "expr.hpp"
#include "lox.hpp"


int DOUBLE_PRECISION = 4;

inline bool ends_with(const std::string& s, const std::string& ending) {
    if (ending.size() > s.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), s.rbegin());
}


std::string InterpreterResult::stringify(InterpreterResult &result) {
    if (result.kind == ResultType::NIL) return "nil";

    if (result.kind == ResultType::NUMBER) {

        std::ostringstream text_strm;

        text_strm << std::fixed
                  << std::setprecision(DOUBLE_PRECISION)
                  << result.num_val;

        const std::string text(text_strm.str());

        const std::string trailing_zeros(DOUBLE_PRECISION, '0');

        if (ends_with(text, trailing_zeros))
            return text.substr(0, text.size() - (DOUBLE_PRECISION + 1));

        return text;
    }

    if (result.kind == ResultType::STR) {
        return result.str_val;
    }

    if (result.kind == ResultType::BOOL) {
        return result.bool_val ? "true" : "false";
    }

    if (result.kind == ResultType::FUNCTION) {
        return "<fn " + result.function->name.lexeme + ">";
    }

    if (result.kind == ResultType::CLASS) {
        return "<class " + result.name + ">";
    }

    if (result.kind == ResultType::INSTANCE) {
        return "<" + (result.klass)->name + " instance>";
    }

    return "Unable to stringify InterpretedResult";
}

InterpreterResult InterpreterResult::call(Interpreter *interpreter, std::vector<InterpreterResult> args) {

    if (kind == ResultType::CLASS) {
        InterpreterResult instance;
        instance.kind = ResultType::INSTANCE;
        instance.klass = class_def;
        return instance;
    }

    Environment* call_env = new Environment(closure);

    for (int i = 0; i < function->parameters.size(); i++) {
        call_env->define(function->parameters[i].lexeme, args[i]);
    }


//    BlockStmt* body = new BlockStmt(function->body);


    interpreter->execute(function->body, call_env);

//    delete body;
    //delete call_env;

    return interpreter->return_val;
}

InterpreterResult InterpreterResult::get(Token property) {
    if (fields.count(property.lexeme) > 0) {
        return fields[property.lexeme];
    }

    throw RuntimeErr(property, "Undefined property '" + property.lexeme + "' in class " + klass->name + ".");
}

void InterpreterResult::set(Token property, InterpreterResult value) {
    fields[property.lexeme] = value;
}