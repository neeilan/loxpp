#ifndef LOXPP_RESOLVER_HPP
#define LOXPP_RESOLVER_HPP

#include <string>
#include <map>
#include <vector>

#include "interpreter.hpp"
#include "interpreter_result.hpp"
#include "token.hpp"
#include "visitor.hpp"
#include "visitable_types.hpp"

enum FunctionType
{
    NOT_IN_FN,
    METHOD,
    FUNCTION,
    INITIALIZER,
    LAMBDA_FN
};

enum ClassType
{
    NOT_IN_CLASS,
    IN_CLASS
};

// true in map == 'is finished being initialized in this scope'
using scope_map = std::map<std::string, bool>;

class Resolver : public ExprVisitor<void>, public StmtVisitor
{
  public:
    Resolver(Interpreter *interpreter1) : interpreter(interpreter1) {}
    void resolve(const std::vector<Stmt *> statements);

  private:
    Interpreter *interpreter;
    std::vector<scope_map *> scopes;
    ClassType current_class = NOT_IN_CLASS;
    FunctionType current_function = NOT_IN_FN;

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

    void begin_scope();
    void end_scope();
    void resolve(const Stmt *stmt);
    void resolve(const Expr *expr);
    void resolve_local(const Expr *expr, const Token name);
    void resolve_fn(FunctionType declaration, const FuncStmt *fn);
    void declare(const Token);
    void define(const Token);
};

#endif //LOXPP_RESOLVER_HPP
