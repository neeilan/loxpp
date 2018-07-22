#ifndef LOXPP_INTERPRETER_RESULT_HPP
#define LOXPP_INTERPRETER_RESULT_HPP

#include <string>

class InterpreterResult {
public:
    enum ResultType {
        STR, NUMBER, NIL, BOOL
    };

    static std::string stringify(InterpreterResult&);

    ResultType kind = NIL;
    std::string str_val;
    double num_val;
    bool bool_val;

};


#endif //LOXPP_INTERPRETER_RESULT_HPP
