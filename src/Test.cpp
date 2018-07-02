#include <vector>

#include "expr.hpp"
#include "token.hpp"
#include "literal_value.hpp"

namespace AST {

  class Test {
  };
  class Binary : public Test {
  public:
    Expr left;
    Token op;
    Expr right;

    Binary(Expr left,Token op,Expr right) { 
      this->left = left;
      this->op = op;
      this->right = right;
    }
  };

  class Grouping : public Test {
  public:
    Expr expression;

    Grouping(Expr expression) { 
      this->expression = expression;
    }
  };

  class Literal : public Test {
  public:
    LiteralValue value;

    Literal(LiteralValue value) { 
      this->value = value;
    }
  };

  class Unary : public Test {
  public:
    Token op;
    Expr right;

    Unary(Token op,Expr right) { 
      this->op = op;
      this->right = right;
    }
  };

};
