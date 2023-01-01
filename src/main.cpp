#include <iostream>

#include "lexer/Lexer.h"
#include "utils/Utils.h"


int main(int argc, char **argv) {
    Lexer lexer;
    Utils::logWelcome();
    CodeGenerator codeGenerator;
    lexer.mainLoop(codeGenerator);
    return 0;
}
