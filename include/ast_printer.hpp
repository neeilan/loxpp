#ifndef LOXPP_AST_PRINTER_HPP
#define LOXPP_AST_PRINTER_HPP

#include <string>

#include "expr.hpp"
#include "visitor.h"

class AstPrinter : public Visitor<std::string> {
public:
    std::string print(Expr& expr) {
        return expr.accept(this);
    }

    std::string visit(const Unary*);
    std::string visit(const Binary*);
    std::string visit(const Grouping*);
    std::string visit(const Literal*);
private:
    std::string parenthesize(std::string, const Expr&); // todo: change these to variadic template
    std::string parenthesize(std::string, const Expr&, const Expr&);
};


#endif //LOXPP_AST_PRINTER_HPP