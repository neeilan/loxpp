#include "ast_printer.hpp"
#include "expr.hpp"

std::string AstPrinter::visit(const Binary* expr) {
    return parenthesize((expr->op).lexeme, &(expr->left), &(expr->right));
}

std::string AstPrinter::visit(const Literal* expr) {
    if (expr->nil) {
        return "nil";
    } else {
        return expr->value;
    }
}

std::string AstPrinter::visit(const Grouping* expr) {
    return parenthesize(std::string("group"), &(expr->expression));
}

std::string AstPrinter::visit(const Unary* expr) {
    return parenthesize((expr->op).lexeme, &(expr->right));
}

std::string AstPrinter::parenthesize(std::string name, const Expr* expr) {
    return "(" + name + " " + expr->accept(this) + ")";
}

std::string AstPrinter::parenthesize(std::string name, const Expr* expr1, const Expr* expr2) {
    return "(" + name + " " + expr1->accept(this) + " " + expr2->accept(this) + ")";
}