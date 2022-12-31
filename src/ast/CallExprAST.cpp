#include "ast/CallExprAST.h"
#include "backend/CodeGenerator.h"


CallExprAST::CallExprAST(const std::string &callee, std::vector<ExprAST *> &args) : callee(callee), args(args) {

}

llvm::Value *CallExprAST::codeGen(llvm::LLVMContext *theContext, llvm::Module *theModule,
                                  std::map<std::string, llvm::Value *> &variables, llvm::IRBuilder<> *builder) {
    llvm::Function *func=theModule->getFunction(callee);
    if (!func) return CodeGenerator::errorV("unknown function referenced.");
    if (func->arg_size()!=args.size()) return CodeGenerator::errorV("incorrect function arguments passed.");

    std::vector<llvm::Value*> argsVal;
    for (int i = 0; i < args.size(); ++i) {
        argsVal.push_back(args[i]->codeGen(theContext,theModule,variables,builder));
        if (!argsVal.back()) return nullptr;
    }
    return builder->CreateCall(func,argsVal,"calltmp");
}
