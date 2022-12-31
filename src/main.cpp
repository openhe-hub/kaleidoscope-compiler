#include <iostream>

#include "lexer/Lexer.h"
#include "utils/Utils.h"


int main() {
    Lexer lexer;
    Utils::logWelcome();
    CodeGenerator codeGenerator;
    codeGenerator.initModule();
    lexer.mainLoop(codeGenerator);
    return 0;
}
