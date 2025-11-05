#ifndef MODULES_H
#define MODULES_H

#include "commands.hpp"

typedef Command<void(*)(const std::string&)> ModuleType;

template<typename T>
using MathModuleType = Command<T(*)(int)>;


#endif // MODULES_H