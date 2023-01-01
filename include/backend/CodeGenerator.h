#ifndef KALEIDOSCOPE_COMPILER_CODEGENERATOR_H
#define KALEIDOSCOPE_COMPILER_CODEGENERATOR_H

#include "llvm/IR/IRBuilder.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

#include "ast/FunctionAST.h"
#include "ast/PrototypeAST.h"

class CodeGenerator{
private:
    llvm::Module *theModule;
    llvm::LLVMContext *theContext;
    llvm::IRBuilder<> *builder;
    std::map<std::string,llvm::Value*> variables; // map: var => llvm Value ptr
    llvm::legacy::FunctionPassManager *theFPM;
public:
    CodeGenerator();
    static llvm::Value *errorV(const char *str);
    void initModule();
    void initFunctionPassManager();
    llvm::Function *generateFunction(FunctionAST *functionAst);
    llvm::Function *generatePrototype(PrototypeAST *prototypeAst);
    llvm::Function *generateTopLevelExpr(FunctionAST *functionAst);

};

#endif //KALEIDOSCOPE_COMPILER_CODEGENERATOR_H
