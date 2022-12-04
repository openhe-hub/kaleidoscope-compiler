#include <iostream>
#include <cstdlib>

enum Token {
    tok_eof = -1,
    // commands
    tok_def = -2,
    tok_extern = -3,
    // primary
    tok_identifier = -4,
    tok_number = -5
};

static std::string identifierStr;
static double numVal;

static int getToken() {
    static int lastChar = ' ';

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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
