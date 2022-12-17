#ifndef KALEIDOSCOPE_COMPILER_NUMBEREXPRAST_H
#define KALEIDOSCOPE_COMPILER_NUMBEREXPRAST_H

#include "ExprAST.h"

class NumberExprAST : public ExprAST{
private:
    double val;
public:
    NumberExprAST(double val);
};

#endif //KALEIDOSCOPE_COMPILER_NUMBEREXPRAST_H
