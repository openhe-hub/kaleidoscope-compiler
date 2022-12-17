#include "ast/BinaryExprAST.h"

BinaryExprAST::BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs) : op(op), lhs(lhs), rhs(rhs) {

}
