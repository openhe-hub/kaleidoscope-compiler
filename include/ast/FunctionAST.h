#ifndef KALEIDOSCOPE_COMPILER_FUNCTIONAST_H
#define KALEIDOSCOPE_COMPILER_FUNCTIONAST_H
#include "ast/PrototypeAST.h"
#include "ast/ExprAST.h"

#include "llvm/IR/LegacyPassManager.h"

class FunctionAST{
private:
    PrototypeAST *prototype;
    ExprAST *body;
public:
    FunctionAST(PrototypeAST *prototype,ExprAST *body);
    llvm::Function *codeGen(llvm::LLVMContext *theContext,
                         llvm::Module *theModule,
                         std::map<std::string,llvm::Value*> &variables,
                         llvm::IRBuilder<> *builder,
                         llvm::legacy::FunctionPassManager *theFPM);
};

#endif //KALEIDOSCOPE_COMPILER_FUNCTIONAST_H
