#include "ast/FunctionAST.h"
#include "llvm/IR/Verifier.h"

FunctionAST::FunctionAST(PrototypeAST *prototype, ExprAST *body) : prototype(prototype), body(body) {

}

llvm::Function *FunctionAST::codeGen(llvm::LLVMContext *theContext, llvm::Module *theModule,
                                     std::map<std::string, llvm::Value *> &variables, llvm::IRBuilder<> *builder) {
    variables.clear();
    llvm::Function *theFunction =prototype->codeGen(theContext,theModule,variables,builder);
    if (!theFunction) return nullptr;

    llvm::BasicBlock *block=llvm::BasicBlock::Create(*theContext,"entry",theFunction);
    builder->SetInsertPoint(block);
    if (llvm::Value *retVal=body->codeGen(theContext,theModule,variables,builder)){
        builder->CreateRet(retVal);
        llvm::verifyFunction(*theFunction);
        return theFunction;
    }
    theFunction->eraseFromParent();
    return nullptr;
}
