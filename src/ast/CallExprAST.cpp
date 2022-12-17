#include "ast/CallExprAST.h"


CallExprAST::CallExprAST(const std::string &callee, std::vector<ExprAST *> &args) : callee(callee), args(args) {

}
