#ifndef KALEIDOSCOPE_COMPILER_EXPRAST_H
#define KALEIDOSCOPE_COMPILER_EXPRAST_H

#include "llvm/IR/IRBuilder.h"

class ExprAST {
public:
    virtual ~ExprAST();
    virtual llvm::Value *codeGen(llvm::LLVMContext *theContext,
                                 llvm::Module *theModule,
                                 std::map<std::string,llvm::Value*> variables,
                                 llvm::IRBuilder<> *builder)=0;
};


#endif //KALEIDOSCOPE_COMPILER_EXPRAST_H
