cmake_minimum_required(VERSION 3.10)
project(loxpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(loxpp
        include/expr.hpp
        include/lox.hpp
        include/scanner.hpp
        include/token.hpp
        src/cli.cpp
        src/lox.cpp
        src/scanner.cpp
        src/token.cpp
        Makefile include/visitor.h src/parser.cpp include/parser.h src/interpreter.cpp include/interpreter.h src/ast_printer.cpp include/ast_printer.hpp include/interpreter_result.hpp src/interpreter_result.cpp include/visitable_types.hpp include/environment.hpp include/return.hpp src/resolver.cpp include/resolver.hpp include/runtime_err.hpp)
