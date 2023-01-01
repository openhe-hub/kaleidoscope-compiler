#include "backend/CodeGenerator.h"


CodeGenerator::CodeGenerator() {
    initJIT();
    initModule();
    initFunctionPassManager();
}

void CodeGenerator::initModuleAndPassManager() {
    theModule = std::make_unique<llvm::Module>("my jit",*theContext);
    theModule->setDataLayout(theJIT->getTargetMachine().createDataLayout());
    initFunctionPassManager();
}

void CodeGenerator::initModule() {
    theContext = new llvm::LLVMContext();
    theModule = std::make_unique<llvm::Module>("my jit",*theContext);
    theModule->setDataLayout(theJIT->getTargetMachine().createDataLayout());
    builder = new llvm::IRBuilder<>(*theContext);
}

void CodeGenerator::initFunctionPassManager() {
    theFPM = std::make_unique<llvm::legacy::FunctionPassManager>(theModule.get());
    // add four elementary pass to optimize function generation
    theFPM->add(llvm::createInstructionCombiningPass());
    theFPM->add(llvm::createReassociatePass());
    theFPM->add(llvm::createGVNPass());
    theFPM->add(llvm::createCFGSimplificationPass());
    theFPM->doInitialization();
}

void CodeGenerator::initJIT() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    theJIT = std::make_unique<llvm::orc::KaleidoscopeJIT>();
}

llvm::Function *CodeGenerator::generateFunction(FunctionAST *functionAst) {
    llvm::Function *function = functionAst->codeGen(theContext, theModule, variables, builder, theFPM);
    if (function) {
        std::cout << ">>>Function IR code generated successfully" << std::endl;
        function->print(llvm::errs());
        return function;
    } else {
        std::cout << "Function IR code generated failed." << std::endl;
        return nullptr;
    }
}

llvm::Function *CodeGenerator::generatePrototype(PrototypeAST *prototypeAst) {
    llvm::Function *function = prototypeAst->codeGen(theContext, theModule, variables, builder);
    if (function) {
        std::cout << ">>>Prototype IR code generated successfully" << std::endl;
        function->print(llvm::errs());
        return function;
    } else {
        std::cout << "Prototype IR code generated failed." << std::endl;
        return nullptr;
    }
}

llvm::Function *CodeGenerator::generateTopLevelExpr(FunctionAST *functionAst) {
    llvm::Function *function = functionAst->codeGen(theContext, theModule, variables, builder, theFPM);
    if (function) {
        std::cout << ">>>Top-level expression IR code generated successfully" << std::endl;

        // JIT the module containing the anonymous expression, keeping a handle so
        // we can free it later.
        auto handler = theJIT->addModule(std::move(theModule));
        initModuleAndPassManager();

        // Search the JIT for the __anon_expr symbol.
        auto ExprSymbol = theJIT->findSymbol("__anon_expr");
        assert(ExprSymbol && "Function not found");

        // Get the symbol's address and cast it to the right type (takes no
        // arguments, returns a double) so we can call it as a native function.
        double (*FP)() = (double (*)()) (intptr_t) cantFail(ExprSymbol.getAddress());
        fprintf(stderr, "Evaluated to %f\n", FP());
        // Delete the anonymous expression module from the JIT.
        theJIT->removeModule(handler);

        function->print(llvm::errs());
        return function;
    } else {
        std::cout << "Top-level expression IR code generated failed." << std::endl;
        return nullptr;
    }
}

llvm::Value *CodeGenerator::errorV(const char *str) {
    std::cout << str << std::endl;
    return nullptr;
}








