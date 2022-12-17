#include "lexer/Lexer.h"

// get token
int Lexer::getToken() {
    static int lastChar = ' ';
    identifierStr.clear();

    while (isspace(lastChar)) lastChar = getchar();

    if (isalpha(lastChar)) {
        identifierStr += lastChar;
        while (isalnum((lastChar = getchar()))) identifierStr += lastChar;

        if (identifierStr == "def") return tok_def;
        if (identifierStr == "extern") return tok_extern;
        return tok_identifier;
    }

    if (isdigit(lastChar) || lastChar == '.') {
        std::string numStr;
        do {
            numStr += lastChar;
            lastChar = getchar();
        } while (isdigit(lastChar) || lastChar == '.');
        numVal = strtod(numStr.c_str(), nullptr);
        return tok_number;
    }

    if (lastChar == '#') {
        do {
            lastChar = getchar();
        } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');
        if (lastChar != EOF) return getToken();
    }

    if (lastChar == EOF) return tok_eof;

    int thisChar = lastChar;
    lastChar = getchar();
    return thisChar;
}

int Lexer::getNextToken() {
    return curToken = getToken();
}

// error function
ExprAST *Lexer::errorExpr(const char *str) {
    std::cerr << str << std::endl;
    return nullptr;
}

PrototypeAST *Lexer::errorPrototype(const char *str) {
    errorExpr(str);
    return nullptr;
}

FunctionAST *Lexer::errorFunction(const char *str) {
    errorExpr(str);
    return nullptr;
}

// parser

// number_expr = number
ExprAST *Lexer::parseNumberExpr() {
    ExprAST *result = new NumberExprAST(numVal);
    getNextToken();
    return result;
}

// paren_expr = '(' + expr + ')'
ExprAST *Lexer::parseParenExpr() {
    getNextToken(); // eat (
    ExprAST *expr = parseExpression();
    if (!expr) return nullptr;
    if (curToken != ')') return errorExpr(">>>expect(");
    getNextToken();
    return expr;
}

// identifier_expr
//                = identifier
//                = identifier + '(' +expr+')'
ExprAST *Lexer::parseIdentifierExpr() {
    std::string idName = identifierStr;
    getNextToken(); // eat identifier

    // variable
    if (curToken != '(') return new VariableExprAST(idName);
    // function call
    getNextToken();  // eat (
    std::vector<ExprAST *> args;
    if (curToken != ')') {
        while (1) {
            ExprAST *arg = parseExpression();
            if (!arg) return nullptr;
            args.push_back(arg);
            if (curToken == ')') break;
            if (curToken != ',') return errorExpr(">>> expected ')' or ',' in argument list");
            getNextToken();
        }
    }
    getNextToken();
    return new CallExprAST(idName, args);
}

// prototype = identifier + '(' + identifier* + ')'
PrototypeAST *Lexer::parsePrototype() {
    if (curToken != tok_identifier) return errorPrototype(">>>Expected function name in prototype");
    std::string funcName = identifierStr;
    getNextToken();
    if (curToken != '(') return errorPrototype(">>>Expected '(' in prototype");

    std::vector<std::string> argNames;
    while (getNextToken() == tok_identifier) {
        argNames.push_back(identifierStr);
    }
    if (curToken != ')') return errorPrototype(">>>Expected ')' in prototype");
    getNextToken(); // eat (
    return new PrototypeAST(funcName, argNames);
}

// function = 'def' + prototype expression
FunctionAST *Lexer::parseFunction() {
    getNextToken(); // eat 'def'
    PrototypeAST *prototypeAst = parsePrototype();
    if (!prototypeAst) return nullptr;
    ExprAST *expr = parseExpression();
    if (expr) return new FunctionAST(prototypeAst, expr);
    return nullptr;
}

PrototypeAST *Lexer::parseExtern() {
    getNextToken(); // eat extern
    return parsePrototype();
}


// top_level_expr = expression
FunctionAST *Lexer::parseTopLevelExpr() {
    if (ExprAST *expr=parseExpression()){
        // make an anonymous prototype
        PrototypeAST *prototype=new PrototypeAST("",std::vector<std::string>());
        return new FunctionAST(prototype,expr);
    }
    return nullptr;
}


ExprAST *Lexer::parseExpression() {
    ExprAST *lhs=parsePrimary();
    if (!lhs) return nullptr;
    return parseBinOpRHS(0,lhs);
}

ExprAST *Lexer::parseBinOpRHS(int exprPrec, ExprAST *lhs) {
    while (1){
        int tokenPrec=getTokenPrecedence();
        // 1.
        if (tokenPrec<exprPrec) return lhs;
        // 2.
        int op=curToken;
        getNextToken(); // eat op
        ExprAST *rhs= parsePrimary();
        if(!rhs) return nullptr;
        // 3.
        // a+b*c
        int nextPrec=getTokenPrecedence();
        if (tokenPrec<nextPrec){
            rhs= parseBinOpRHS(tokenPrec+1,rhs);
            if (!rhs) return nullptr;
        }
        // a*b+c
        lhs=new BinaryExprAST(op,lhs,rhs);
    }
}

ExprAST *Lexer::parsePrimary() {
    switch (curToken) {
        case tok_number: {
            return parseNumberExpr();
        }
        case tok_identifier: {
            return parseIdentifierExpr();
        }
        case '(': {
            return parseParenExpr();
        }
        default: {
            return errorExpr(">>>unknown token when expecting an expression");
        }
    }
}

int Lexer::getTokenPrecedence() {
    std::map<char,int> precedenceTable;
    precedenceTable['<']=10;
    precedenceTable['+']=20;
    precedenceTable['-']=20;
    precedenceTable['*']=40;

    if(!isascii(curToken)) return -1;
    int tokenPrec=precedenceTable[curToken];
    if (tokenPrec<=0) return -1;
    return precedenceTable[curToken];
}

void Lexer::mainLoop() {
    std::cout<<"<<<";
    getNextToken();
    while (1){
        switch (curToken) {
            case tok_eof:
                return;
            case tok_def:{
                handleDefinition();
            }
                break;
            case tok_extern:{
                handleExtern();
            }
                break;
            case ';': {
                getNextToken();
            }
                break;
            default:{
                handleTopLevelExpression();
            }
                break;
        }
        if(curToken==';') {
            std::cout<<"<<<";
        }
    }
}

void Lexer::handleDefinition() {
    if (parseFunction()){
        std::cout<<">>>Parsed a function definition."<<std::endl;
    } else{
        getNextToken();
    }
}

void Lexer::handleExtern() {
    if (parseExtern()){
        std::cout<<">>>Parsed an extern."<<std::endl;
    } else{
        getNextToken();
    }
}

void Lexer::handleTopLevelExpression() {
    if (parseTopLevelExpr()){
        std::cout<<">>>Parsed a top-level expression."<<std::endl;
    } else{
        getNextToken();
    }
}










