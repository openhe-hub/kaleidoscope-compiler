#include "ast/BinaryExprAST.h"
#include "backend/CodeGenerator.h"
#include "llvm/IR/DerivedTypes.h"

BinaryExprAST::BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs) : op(op), lhs(lhs), rhs(rhs) {

}

llvm::Value *BinaryExprAST::codeGen(llvm::LLVMContext *theContext, llvm::Module *theModule,
                                    std::map<std::string, llvm::Value *> &variables, llvm::IRBuilder<> *builder) {
    llvm::Value *lval=lhs->codeGen(theContext,theModule,variables,builder);
    llvm::Value *rval=rhs->codeGen(theContext,theModule,variables,builder);
    if (!lval||!rval) return nullptr;
    switch (op) {
        case '+':return builder->CreateFAdd(lval,rval,"addtmp");
        case '-': return builder->CreateFSub(lval,rval,"subtmp");
        case '*': return builder->CreateFMul(lval,rval,"multmp");
        case '<': {
            lval=builder->CreateFCmpULT(lval,rval,"cmptmp");
            // convert bool 0/1 => double 0.0/1.0
            return builder->CreateUIToFP(lval,llvm::Type::getDoubleTy(*theContext),"booltmp");
        }
        default: return CodeGenerator::errorV("invalid binary operation.");
    }
}
