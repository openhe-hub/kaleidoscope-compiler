#include "backend/CodeGenerator.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"


void CodeGenerator::initModule() {
    theContext = new llvm::LLVMContext();
    theModule = new llvm::Module("my cool jit", *theContext);
    builder = new llvm::IRBuilder<>(*theContext);
}

llvm::Function *CodeGenerator::generateFunction(FunctionAST *functionAst) {
    llvm::Function *function=functionAst->codeGen(theContext,theModule,variables,builder);
    if(function){
        std::cout<<">>>Function IR code generated successfully"<<std::endl;
        function->print(llvm::errs());
        return function;
    }else{
        std::cout<<"Function IR code generated failed."<<std::endl;
        return nullptr;
    }
}

llvm::Function *CodeGenerator::generatePrototype(PrototypeAST *prototypeAst) {
    llvm::Function *function=prototypeAst->codeGen(theContext,theModule,variables,builder);
    if(function){
        std::cout<<">>>Prototype IR code generated successfully"<<std::endl;
        function->print(llvm::errs());
        return function;
    }else{
        std::cout<<"Prototype IR code generated failed."<<std::endl;
        return nullptr;
    }
}

llvm::Function *CodeGenerator::generateTopLevelExpr(FunctionAST *functionAst) {
    llvm::Function *function=functionAst->codeGen(theContext,theModule,variables,builder);
    if(function){
        std::cout<<">>>Top-level expression IR code generated successfully"<<std::endl;
        function->print(llvm::errs());
        return function;
    }else{
        std::cout<<"Top-level expression IR code generated failed."<<std::endl;
        return nullptr;
    }
}

llvm::Value *CodeGenerator::errorV(const char *str) {
    std::cout<<str<<std::endl;
    return nullptr;
}
