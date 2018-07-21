#include "ast_printer.hpp"
#include "expr.hpp"

std::string AstPrinter::visit(const Unary* expr) {
    return parenthesize((expr->op).lexeme, expr->right);
}
std::string AstPrinter::visit(const Binary* expr) {
    return parenthesize((expr->op).lexeme, expr->left, expr->right);
}
std::string AstPrinter::visit(const Literal* expr) {
    return std::string(std::string("Unimplemented"));
}

std::string AstPrinter::visit(const Grouping* expr) {
    return parenthesize(std::string("group"), expr->expression);
}

std::string AstPrinter::parenthesize(std::string name, const Expr& expr) {
    return std::string(std::string("Unimplemented"));
}

std::string AstPrinter::parenthesize(std::string s, const Expr& expr1, const Expr& expr2) {
    return std::string(std::string("Unimplemented"));
}