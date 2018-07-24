#ifndef LOXPP_ENVIRONMENT_HPP
#define LOXPP_ENVIRONMENT_HPP

#include <map>
#include <memory>
#include <string>

#include "interpreter_result.hpp"
#include "token.hpp"

class Environment;

class Environment {
public:
    explicit Environment()
            : enclosing(std::shared_ptr<Environment>(nullptr)) {};

    explicit Environment(std::shared_ptr<Environment> enclosing)
            : enclosing(enclosing) {}

    void define(std::string name, InterpreterResult &value);
    void assign(const Token name, InterpreterResult &value);
    InterpreterResult get(Token name);

private:
    const std::shared_ptr<Environment> enclosing;
    std::map<std::string, InterpreterResult> values;
};

#endif //LOXPP_ENVIRONMENT_HPP
