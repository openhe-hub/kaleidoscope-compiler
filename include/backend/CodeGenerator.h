#ifndef KALEIDOSCOPE_COMPILER_CODEGENERATOR_H
#define KALEIDOSCOPE_COMPILER_CODEGENERATOR_H

#include "llvm/IR/IRBuilder.h"

#include "ast/FunctionAST.h"
#include "ast/PrototypeAST.h"

class CodeGenerator{
private:
    llvm::Module *theModule;
    llvm::LLVMContext *theContext;
    llvm::IRBuilder<> *builder;
    std::map<std::string,llvm::Value*> variables; // map: var => llvm Value ptr
public:
    static llvm::Value *errorV(const char *str);
    void initModule();
    llvm::Function *generateFunction(FunctionAST *functionAst);
    llvm::Function *generatePrototype(PrototypeAST *prototypeAst);
    llvm::Function *generateTopLevelExpr(FunctionAST *functionAst);

};

#endif //KALEIDOSCOPE_COMPILER_CODEGENERATOR_H
