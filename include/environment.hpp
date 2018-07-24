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
            : enclosing(nullptr) {};

    explicit Environment(Environment* enclosing)
            : enclosing(enclosing) {}

    Environment(const Environment& env) {
        this->enclosing = env.enclosing;
        this->values = env.values;
    }

    void define(std::string name, InterpreterResult &value);
    void assign(const Token name, InterpreterResult &value);
    InterpreterResult get(Token name);

private:
    Environment* enclosing;
    std::map<std::string, InterpreterResult> values;
};

#endif //LOXPP_ENVIRONMENT_HPP
