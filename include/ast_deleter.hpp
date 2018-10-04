#ifndef LOXPP_AST_DELETER_HPP
#define LOXPP_AST_DELETER_HPP

#include <set>

#include "expr.hpp"
#include "visitor.hpp"
#include "stmt.hpp"

class AstDeleter : public ExprVisitor<void>,
                   public StmtVisitor
{
  public:
    void recursive_delete(const vector<Stmt *> &statements);

  private:
    std::set<const Expr *> exprs_to_delete;
    std::set<const Stmt *> stmts_to_delete;

    void visit(const Binary *expr);
    void visit(const StrLiteral *expr);
    void visit(const NumLiteral *expr);
    void visit(const BoolLiteral *expr);
    void visit(const Grouping *expr);
    void visit(const Unary *expr);
    void visit(const Variable *expr);
    void visit(const Assignment *expr);
    void visit(const Logical *expr);
    void visit(const Call *expr);
    void visit(const Get *expr);
    void visit(const Set *expr);
    void visit(const This *expr);
    void visit(const Lambda *expr);

    void visit(const BlockStmt *);
    void visit(const ExprStmt *);
    void visit(const PrintStmt *);
    void visit(const VarStmt *);
    void visit(const ClassStmt *);
    void visit(const IfStmt *);
    void visit(const WhileStmt *);
    void visit(const FuncStmt *);
    void visit(const ReturnStmt *);
};

#endif //LOXPP_AST_DELETER_HPP
