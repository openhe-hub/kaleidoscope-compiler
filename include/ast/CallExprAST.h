#ifndef KALEIDOSCOPE_COMPILER_CALLEXPRAST_H
#define KALEIDOSCOPE_COMPILER_CALLEXPRAST_H

#include "ast/ExprAST.h"
#include <iostream>
#include <vector>

class CallExprAST: public ExprAST{
private:
    std::string callee;
    std::vector<ExprAST*> args;
public:
    CallExprAST(const std::string &calle,std::vector<ExprAST*> &args);
    virtual llvm::Value *codeGen() override;
};

#endif //KALEIDOSCOPE_COMPILER_CALLEXPRAST_H
