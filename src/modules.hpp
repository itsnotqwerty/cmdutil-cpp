#ifndef MODULES_H
#define MODULES_H

#include "commands.hpp"
#include "parsing.hpp"

#define UNUSED(x) (void)(x)

enum paramTypes {MODULE, SINGLE_ARG, DOUBLE_ARG};

typedef Command<void(*)(const std::string&)> ModuleType;

template<typename T>
using MathModuleType = Command<T(*)(int)>;

int registerModule(
    const std::vector<ModuleType>& opList,
    const std::string& input
);

template<typename T, typename K>
int registerMathModule(
    const std::vector<MathModuleType<T>>& opList,
    const std::string& input
);

#endif // MODULES_H