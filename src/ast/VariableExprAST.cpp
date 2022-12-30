#include "ast/VariableExprAST.h"
#include "backend/CodeGenerator.h"


VariableExprAST::VariableExprAST(std::string name) : name(name) {

}

llvm::Value *VariableExprAST::codeGen(llvm::LLVMContext *theContext, llvm::Module *theModule,
                                      std::map<std::string, llvm::Value *> variables, llvm::IRBuilder<> *builder) {
    llvm::Value *val = variables[name];
    return val ? val : CodeGenerator::errorV("unknown variable name");
}


