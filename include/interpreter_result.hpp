#ifndef LOXPP_INTERPRETER_RESULT_HPP
#define LOXPP_INTERPRETER_RESULT_HPP

#include <string>
#include "visitable_types.hpp"
#include "interpreter.h"
#include "environment.hpp"

class Interpreter;

class InterpreterResult {
public:
    enum ResultType {
        STR, NUMBER, NIL, BOOL, FUNCTION
    };

    static std::string stringify(InterpreterResult&);
    
    ResultType kind = NIL;
    std::string str_val;
    double num_val;
    bool bool_val;

    bool callable = false;
    int arity;
    const FuncStmt* function;
    Environment* closure = nullptr;

    virtual InterpreterResult call(Interpreter* interpreter,
                                   std::vector<InterpreterResult> args);

};


#endif //LOXPP_INTERPRETER_RESULT_HPP
