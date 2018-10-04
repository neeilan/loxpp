#ifndef LOXPP_INTERPRETER_H
#define LOXPP_INTERPRETER_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "token.hpp"
#include "expr.hpp"
#include "interpreter_result.hpp"
#include "visitor.hpp"
#include "stmt.hpp"
#include "environment.hpp"

using std::shared_ptr;
using std::vector;

class Interpreter : public ExprVisitor<shared_ptr<InterpreterResult>>,
                    public StmtVisitor {
public:
    void interpret(const vector<Stmt*>& statements);
    void resolve(const Expr* expr, int depth);
    ~Interpreter() {}

protected:
    shared_ptr<InterpreterResult> visit(const Binary* expr);
    shared_ptr<InterpreterResult> visit(const StrLiteral* expr);
    shared_ptr<InterpreterResult> visit(const NumLiteral* expr);
    shared_ptr<InterpreterResult> visit(const BoolLiteral* expr);
    shared_ptr<InterpreterResult> visit(const Grouping* expr);
    shared_ptr<InterpreterResult> visit(const Unary* expr);
    shared_ptr<InterpreterResult> visit(const Variable* expr);
    shared_ptr<InterpreterResult> visit(const Assignment* expr);
    shared_ptr<InterpreterResult> visit(const Logical* expr);
    shared_ptr<InterpreterResult> visit(const Call* expr);
    shared_ptr<InterpreterResult> visit(const Get* expr);
    shared_ptr<InterpreterResult> visit(const Set* expr);
    shared_ptr<InterpreterResult> visit(const This* expr);
    shared_ptr<InterpreterResult> visit(const Lambda* expr);

    void visit(const BlockStmt*);
    void visit(const ExprStmt*);
    void visit(const PrintStmt*);
    void visit(const VarStmt*);
    void visit(const ClassStmt*);
    void visit(const IfStmt*);
    void visit(const WhileStmt*);
    void visit(const FuncStmt*);
    void visit(const ReturnStmt*);

private:
    friend class InterpreterResult;

    Environment<shared_ptr<InterpreterResult> > globals;
    Environment<shared_ptr<InterpreterResult> >* environment = &globals;

    std::map<const Expr*, int> locals;

    shared_ptr<InterpreterResult> return_val;

    void execute(const Stmt* stmt);
    void execute(const vector<Stmt*> stmts,
                 Environment<shared_ptr<InterpreterResult> >* environment1);

    shared_ptr<InterpreterResult> evaluate(const Expr& expr);
    shared_ptr<InterpreterResult> lookup_variable(const Token name,
                                                  const Expr* expr);

    bool is_truthy(const InterpreterResult& expr);
    bool is_equal(const InterpreterResult& left, const InterpreterResult& right);

    void check_numeric_operand(const Token op, const InterpreterResult& right);
    void check_numeric_operands(const Token op, const InterpreterResult& left,
                                const InterpreterResult& right);
};

#endif // LOXPP_INTERPRETER_H
