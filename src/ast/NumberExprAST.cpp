#include "ast/NumberExprAST.h"

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;

NumberExprAST::NumberExprAST(double val):val(val) {

}

llvm::Value *NumberExprAST::codeGen(llvm::LLVMContext *theContext, llvm::Module *theModule,
                                    std::map<std::string, llvm::Value *> variables, llvm::IRBuilder<> *builder) {
    return llvm::ConstantFP::get(*theContext,llvm::APFloat(val));
}