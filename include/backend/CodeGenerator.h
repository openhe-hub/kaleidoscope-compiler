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

#include "jit/KaleidoscopeJIT.h"

class CodeGenerator{
private:
    std::unique_ptr<llvm::Module> theModule;
    llvm::LLVMContext *theContext;
    llvm::IRBuilder<> *builder;
    std::map<std::string,llvm::Value*> variables; // map: var => llvm Value ptr
    std::unique_ptr<llvm::legacy::FunctionPassManager> theFPM;
    std::unique_ptr<llvm::orc::KaleidoscopeJIT> theJIT;
public:
    CodeGenerator();
    static llvm::Value *errorV(const char *str);
    void initModule();
    void initFunctionPassManager();
    void initJIT();
    void initModuleAndPassManager();
    llvm::Function *generateFunction(FunctionAST *functionAst);
    llvm::Function *generatePrototype(PrototypeAST *prototypeAst);
    llvm::Function *generateTopLevelExpr(FunctionAST *functionAst);

};

#endif //KALEIDOSCOPE_COMPILER_CODEGENERATOR_H
