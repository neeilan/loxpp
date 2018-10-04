#include <memory>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "interpreter.hpp"

using std::shared_ptr;

int DOUBLE_PRECISION = 4;

inline bool ends_with(const std::string &s, const std::string &ending)
{
    if (ending.size() > s.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), s.rbegin());
}

std::string InterpreterResult::stringify(InterpreterResult &result)
{
    switch (result.kind)
    {
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
    case NUMBER:
    {
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
    Interpreter *interpreter,
    std::vector<shared_ptr<InterpreterResult>> args)
{
    if (kind == ResultType::CLASS)
    {
        auto instance = std::make_shared<InterpreterResult>();
        instance->kind = ResultType::INSTANCE;
        instance->klass = class_def;

        // Run user-defined initializer if present
        if (rt_methods.count("init") > 0)
        {
            rt_methods["init"]->bind(instance.get())->call(interpreter, args);
        }

        return instance;
    }

    Environment<shared_ptr<InterpreterResult>> *call_env = new Environment<shared_ptr<InterpreterResult>>(closure);

    for (int i = 0; i < function->parameters.size(); i++)
    {
        call_env->define(function->parameters[i].lexeme, args[i]);
    }

    interpreter->execute(function->body, call_env);

    // initializer always returns 'this'
    Token this_token(THIS, "this", "", 0);
    return is_initializer ? closure->get_at(0, this_token) : interpreter->return_val;
}

shared_ptr<InterpreterResult> InterpreterResult::get(Token property)
{
    if (fields.count(property.lexeme) > 0)
    {
        return fields[property.lexeme];
    }

    // Possibly a method
    shared_ptr<InterpreterResult> method = klass->find_method(this, property.lexeme);
    if (method->kind != NIL)
        return method;

    throw RuntimeErr(property, "Undefined property '" + property.lexeme + "' in class " + klass->name + ".");
}

void InterpreterResult::set(Token property,
                            shared_ptr<InterpreterResult> value)
{
    fields[property.lexeme] = value;
}

shared_ptr<InterpreterResult> InterpreterResult::find_method(InterpreterResult *const instance,
                                                             std::string name)
{
    if (rt_methods.count(name) > 0)
    {
        return rt_methods[name]->bind(instance);
    }

    if (superclass)
    {
        return superclass->find_method(instance, name);
    }

    auto nil = std::make_shared<InterpreterResult>();
    nil->kind = NIL;
    return nil;
}

shared_ptr<InterpreterResult> InterpreterResult::bind(InterpreterResult *const instance)
{
    // Runtime method with binding
    auto environment = new Environment<shared_ptr<InterpreterResult>>(instance->closure);

    shared_ptr<InterpreterResult> instance_this(instance);

    environment->define("this", instance_this);

    auto bound_method = std::make_shared<InterpreterResult>();
    bound_method->callable = true;
    bound_method->arity = get_arity();
    bound_method->klass = klass;
    bound_method->function = function;
    bound_method->kind = FUNCTION;
    bound_method->is_initializer = is_initializer;
    bound_method->closure = environment;

    return bound_method;
}

int InterpreterResult::get_arity() const
{
    if (kind == CLASS)
    {
        if (rt_methods.count("init") > 0)
        {
            return rt_methods.at("init")->arity;
        }
        else
        {
            return 0;
        }
    }
    else if (kind == FUNCTION)
    {
        return arity;
    }

    throw std::runtime_error("Checking arity of uncallable object");
}
