#ifndef KALEIDOSCOPE_COMPILER_FUNCTIONAST_H
#define KALEIDOSCOPE_COMPILER_FUNCTIONAST_H
#include "ast/PrototypeAST.h"
#include "ast/ExprAST.h"

class FunctionAST{
private:
    PrototypeAST *prototype;
    ExprAST *body;
public:
    FunctionAST(PrototypeAST *prototype,ExprAST *body);
    llvm::Function *codeGen() ;
};

#endif //KALEIDOSCOPE_COMPILER_FUNCTIONAST_H
