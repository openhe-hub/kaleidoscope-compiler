#include "ast/PrototypeAST.h"
#include "backend/CodeGenerator.h"

PrototypeAST::PrototypeAST(const std::string &name, const std::vector<std::string> &args)
        : name(name), args(args) {}

llvm::Function *PrototypeAST::codeGen(llvm::LLVMContext *theContext, llvm::Module *theModule,
                                      std::map<std::string, llvm::Value *> &variables, llvm::IRBuilder<> *builder) {
    //1. create params: n*double
    std::vector<llvm::Type *> doubles(args.size(), llvm::Type::getDoubleTy(*theContext));
    //2. create function type with n * double, num of param is unchangeable
    llvm::FunctionType *functionType = llvm::FunctionType::get(llvm::Type::getDoubleTy(*theContext), doubles, false);
    //3. create function
    llvm::Function *function = llvm::Function::Create(functionType,
                                                      llvm::Function::ExternalLinkage, name, theModule);
    // test if duplicated
    if (function->getName() != name) {
        // remove and use the defined one
        function->eraseFromParent();
        function = theModule->getFunction(name);
    }

    // test if defined
    if (!function->empty()) {
        CodeGenerator::errorV("redefinition of function");
        return nullptr;
    }

    // test if diff param num
    if (function->arg_size() != args.size()) {
        CodeGenerator::errorV("redeclare of function with different param numbers.");
        return nullptr;
    }

    // 4. set param name tag
    int idx = 0;
    for (llvm::Function::arg_iterator it = function->arg_begin();
         it != function->arg_end() && idx < args.size(); it++, idx++) {
        it->setName(args[idx]);
        variables[args[idx]] = it;
    }

    return function;
}
