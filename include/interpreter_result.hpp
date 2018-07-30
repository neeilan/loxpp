#ifndef LOXPP_INTERPRETER_RESULT_HPP
#define LOXPP_INTERPRETER_RESULT_HPP

#include <memory>
#include <string>

#include "visitable_types.hpp"
#include "interpreter.h"
#include "environment.hpp"


using std::shared_ptr;

class Interpreter;

class InterpreterResult {
public:
    enum ResultType {
        STR, NUMBER, NIL, BOOL, FUNCTION, CLASS, INSTANCE
    };

    static std::string stringify(InterpreterResult&);

    ResultType kind = NIL;
    std::string str_val;
    double num_val;
    bool bool_val;

    // Function
    bool callable = false;
    int arity;
    const FuncStmt* function;
    Environment<shared_ptr<InterpreterResult> >* closure = nullptr;
    bool is_initializer = false;


    shared_ptr<InterpreterResult> call(
            Interpreter* interpreter,
            std::vector<shared_ptr<InterpreterResult> > args);

    // Class
    std::string name;
    InterpreterResult* class_def = nullptr;
    std::vector<Stmt*> methods;

    // Class (runtime)
    std::map<std::string, shared_ptr<InterpreterResult>> rt_methods;
    std::map<std::string, shared_ptr<InterpreterResult>> fields;
    shared_ptr<InterpreterResult> superclass;

    shared_ptr<InterpreterResult> get(Token property);
    shared_ptr<InterpreterResult> find_method(InterpreterResult* const instance, std::string name);
    void set(Token property, shared_ptr<InterpreterResult> value);

    // Instance
    InterpreterResult* klass = nullptr;

    // Instance method
    shared_ptr<InterpreterResult> bind(InterpreterResult* const instance);

    int get_arity() const;
};


#endif //LOXPP_INTERPRETER_RESULT_HPP
