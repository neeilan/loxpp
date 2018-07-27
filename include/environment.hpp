#ifndef LOXPP_ENVIRONMENT_HPP
#define LOXPP_ENVIRONMENT_HPP

#include <map>
#include <memory>
#include <string>

#include "interpreter_result.hpp"
#include "token.hpp"

class InterpreterResult;

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
    InterpreterResult get(const Token name);
    InterpreterResult get_at(int distance, const Token name);
    void assign_at(int distance, const Token name, InterpreterResult value);

private:
    Environment* enclosing = nullptr;
    std::map<std::string, InterpreterResult> values;

    Environment* ancestor(int distance);
};

#endif //LOXPP_ENVIRONMENT_HPP
