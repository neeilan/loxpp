#include <memory>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "interpreter.h"

using std::shared_ptr;

int DOUBLE_PRECISION = 4;

inline bool ends_with(const std::string& s, const std::string& ending)
{
    if (ending.size() > s.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), s.rbegin());
}

std::string InterpreterResult::stringify(InterpreterResult& result)
{
    switch (result.kind) {
        case NIL:
            return "nil";
        case STR:
            return result.str_val;
        case BOOL:
            return result.bool_val ? "true" : "false";
        case FUNCTION:
            return "<fn " + result.function->name.lexeme + ">";
        case CLASS:
            return "<class " + result.name + ">";
        case INSTANCE:
            return "<" + (result.klass)->name + " instance>";
        case NUMBER: {
            std::ostringstream text_strm;

            text_strm << std::fixed << std::setprecision(DOUBLE_PRECISION)
                      << result.num_val;

            const std::string text(text_strm.str());

            const std::string trailing_zeros(DOUBLE_PRECISION, '0');

            if (ends_with(text, trailing_zeros))
                return text.substr(0, text.size() - (DOUBLE_PRECISION + 1));

            return text;
        }
        default:
            return "Unable to stringify InterpretedResult";
    }
}

shared_ptr<InterpreterResult> InterpreterResult::call(
        Interpreter* interpreter,
        std::vector<shared_ptr<InterpreterResult> > args)
{
    if (kind == ResultType::CLASS) {
        auto instance = std::make_shared<InterpreterResult>();
        instance->kind = ResultType::INSTANCE;
        instance->klass = class_def;
        return instance;
    }

    Environment<shared_ptr<InterpreterResult> >* call_env = new Environment<shared_ptr<InterpreterResult> >(closure);

    for (int i = 0; i < function->parameters.size(); i++) {
        call_env->define(function->parameters[i].lexeme, args[i]);
    }

    interpreter->execute(function->body, call_env);

    return interpreter->return_val;
}

shared_ptr<InterpreterResult> InterpreterResult::get(Token property)
{
    if (fields.count(property.lexeme) > 0) {
        return fields[property.lexeme];
    }

    throw RuntimeErr(property, "Undefined property '" + property.lexeme + "' in class " + klass->name + ".");
}

void InterpreterResult::set(Token property,
                            shared_ptr<InterpreterResult> value)
{
    fields[property.lexeme] = value;
}