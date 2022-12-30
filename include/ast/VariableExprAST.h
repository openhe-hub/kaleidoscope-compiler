#ifndef KALEIDOSCOPE_COMPILER_VARIABLEEXPRAST_H
#define KALEIDOSCOPE_COMPILER_VARIABLEEXPRAST_H

#include "ast/ExprAST.h"
#include <iostream>

class VariableExprAST: public ExprAST{
private:
    std::string name;
public:
    VariableExprAST(std::string name);
    virtual llvm::Value *codeGen() override;
};

#endif //KALEIDOSCOPE_COMPILER_VARIABLEEXPRAST_H
