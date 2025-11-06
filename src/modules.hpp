#ifndef MODULES_H
#define MODULES_H

#include "commands.hpp"
#include "parsing.hpp"

#define UNUSED(x) (void)(x)

enum paramTypes {MODULE, SINGLE_ARG, DOUBLE_ARG};

typedef Command<void(*)(const std::string&)> ModuleType;

template<typename T>
using MathModuleType = Command<T(*)(int)>;

template<typename T, typename K>
int registerModule(
    const std::vector<MathModuleType<T>>& opList,
    const std::string& input
) {
    return handleCommands<T, K>(input, opList, parseCommand<T, K>);
}

#endif // MODULES_H