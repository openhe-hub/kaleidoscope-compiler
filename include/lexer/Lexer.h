#ifndef KALEIDOSCOPE_COMPILER_LEXER_H
#define KALEIDOSCOPE_COMPILER_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "ast/ExprAST.h"
#include "ast/PrototypeAST.h"
#include "ast/FunctionAST.h"
#include "ast/NumberExprAST.h"
#include "ast/VariableExprAST.h"
#include "ast/CallExprAST.h"
#include "ast/BinaryExprAST.h"

class Lexer{
private:
    enum Token {
        tok_eof = -1,
        // commands
        tok_def = -2,
        tok_extern = -3,
        // primary
        tok_identifier = -4,
        tok_number = -5
    };

    std::string identifierStr;
    double numVal;
    int curToken;

    int getTokenPrecedence();
public:
    // get token
    int getToken();
    int getNextToken();
    // error function
    ExprAST *errorExpr(const char *str);
    PrototypeAST *errorPrototype(const char *str);
    FunctionAST *errorFunction(const char *str);
    // parser
    ExprAST *parseNumberExpr();
    ExprAST *parseParenExpr();
    ExprAST *parseIdentifierExpr();

    ExprAST *parseExpression();
    ExprAST *parseBinOpRHS(int exprPrec,ExprAST *lhs);

    PrototypeAST *parsePrototype();
    FunctionAST *parseFunction();
    FunctionAST *parseTopLevelExpr();
    PrototypeAST *parseExtern();

    ExprAST *parsePrimary();
    // top-level parser
    void handleDefinition();
    void handleExtern();
    void handleTopLevelExpression();

    void mainLoop();
};

#endif //KALEIDOSCOPE_COMPILER_LEXER_H
