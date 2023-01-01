#ifndef KALEIDOSCOPE_COMPILER_PROTOTYPEAST_H
#define KALEIDOSCOPE_COMPILER_PROTOTYPEAST_H

#include <iostream>
#include <vector>
#include "llvm/IR/IRBuilder.h"

class PrototypeAST {
private:
    std::string name;
    std::vector<std::string> args;
public:
    PrototypeAST(const std::string &name, const std::vector<std::string> &args);
     llvm::Function *codeGen(llvm::LLVMContext *theContext,
                             std::unique_ptr<llvm::Module> &theModule,
                                 std::map<std::string,llvm::Value*> &variables,
                                 llvm::IRBuilder<> *builder) ;
};

#endif //KALEIDOSCOPE_COMPILER_PROTOTYPEAST_H
