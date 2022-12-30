#ifndef KALEIDOSCOPE_COMPILER_CODEGENERATOR_H
#define KALEIDOSCOPE_COMPILER_CODEGENERATOR_H

#include "llvm/IR/IRBuilder.h"

class CodeGenerator{
private:
    llvm::Module *theModule;
    llvm::LLVMContext *theContext;
    llvm::IRBuilder<> *builder;
    std::map<std::string,llvm::Value*> variables; // map: var => llvm Value ptr
public:
    static llvm::Value *errorV(const char *str);

};

#endif //KALEIDOSCOPE_COMPILER_CODEGENERATOR_H
