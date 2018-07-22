#include <sstream>
#include <string>
#include <iomanip>

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
    if (result.kind == InterpreterResult::ResultType::NIL) return "nil";

    if (result.kind == InterpreterResult::ResultType::NUMBER) {

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

    if (result.kind == InterpreterResult::ResultType::STR) {
        return "'" + result.str_val + "'";
    }

    if (result.kind == InterpreterResult::ResultType::BOOL) {
        return result.bool_val ? "true" : "false";
    }

    return "Unable to stringify InterpretedResult";
}