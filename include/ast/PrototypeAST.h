#ifndef KALEIDOSCOPE_COMPILER_PROTOTYPEAST_H
#define KALEIDOSCOPE_COMPILER_PROTOTYPEAST_H

#include <iostream>
#include <vector>

class PrototypeAST{
private:
    std::string name;
    std::vector<std::string> args;
public:
    PrototypeAST(const std::string &name,const std::vector<std::string> &args);
};

#endif //KALEIDOSCOPE_COMPILER_PROTOTYPEAST_H
