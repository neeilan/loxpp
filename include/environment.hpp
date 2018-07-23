#ifndef LOXPP_ENVIRONMENT_HPP
#define LOXPP_ENVIRONMENT_HPP

#include <map>
#include <string>

#include "interpreter_result.hpp"
#include "token.hpp"

class Environment {
public:
    void define(std::string name, InterpreterResult value);
    InterpreterResult get(Token name);


private:
    std::map<std::string, InterpreterResult> values;
};

#endif //LOXPP_ENVIRONMENT_HPP
