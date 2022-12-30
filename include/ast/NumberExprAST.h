#ifndef KALEIDOSCOPE_COMPILER_NUMBEREXPRAST_H
#define KALEIDOSCOPE_COMPILER_NUMBEREXPRAST_H

#include "ExprAST.h"
#include "llvm/IR/IRBuilder.h"

class NumberExprAST : public ExprAST{
private:
    double val;
public:
    NumberExprAST(double val);
    virtual llvm::Value *codeGen() override;
};

#endif //KALEIDOSCOPE_COMPILER_NUMBEREXPRAST_H
