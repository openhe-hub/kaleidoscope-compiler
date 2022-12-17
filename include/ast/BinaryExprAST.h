
#ifndef KALEIDOSCOPE_COMPILER_BINARYEXPRAST_H
#define KALEIDOSCOPE_COMPILER_BINARYEXPRAST_H

#include "ast/ExprAST.h"

class BinaryExprAST : public ExprAST {
private:
    char op;
    ExprAST *lhs, *rhs;
public:
    BinaryExprAST(char op,ExprAST *lhs,ExprAST *rhs);

};

#endif //KALEIDOSCOPE_COMPILER_BINARYEXPRAST_H
