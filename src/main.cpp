#include <iostream>

#include "lexer/Lexer.h"
#include "utils/Utils.h"


int main() {
    Lexer lexer;
    Utils::logWelcome();
    lexer.mainLoop();
    return 0;
}
