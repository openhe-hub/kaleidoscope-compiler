#ifndef KALEIDOSCOPE_COMPILER_LEXER_H
#define KALEIDOSCOPE_COMPILER_LEXER_H

#include <iostream>
#include <string>

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
public:
    int getToken();

};

#endif //KALEIDOSCOPE_COMPILER_LEXER_H
