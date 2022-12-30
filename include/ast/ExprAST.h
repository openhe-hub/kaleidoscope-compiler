#ifndef KALEIDOSCOPE_COMPILER_EXPRAST_H
#define KALEIDOSCOPE_COMPILER_EXPRAST_H

#include "llvm/IR/IRBuilder.h"

class ExprAST {
public:
    virtual ~ExprAST();
    virtual llvm::Value *codeGen()=0;
};


#endif //KALEIDOSCOPE_COMPILER_EXPRAST_H
