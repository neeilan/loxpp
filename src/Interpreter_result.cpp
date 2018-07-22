#include <string>

#include "interpreter.h"
#include "interpreter_result.hpp"
#include "expr.hpp"
#include "lox.hpp"

inline bool ends_with(const std::string& s, const std::string& ending) {
    if (ending.size() < s.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), s.rbegin());
}


std::string InterpreterResult::stringify(InterpreterResult &result) {
    if (result.kind == InterpreterResult::ResultType::NIL) return "nil";

    if (result.kind == InterpreterResult::ResultType::NUMBER) {
        std::string text = std::to_string(result.num_val);

        if (ends_with(text, ".0"))
            return text.substr(0, text.size() - 2);

        return text;
    }

    if (result.kind == InterpreterResult::ResultType::STR) {
        return "'" + result.str_val + "'";
    }

    if (result.kind == InterpreterResult::ResultType::BOOL) {
        return result.bool_val ? "true" : "false";
    }

    return "Unable to stringify InterpretedResult";
}