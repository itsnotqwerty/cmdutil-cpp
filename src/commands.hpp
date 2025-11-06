#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <string>
#include <functional>

enum CMD_STATES {CMD_SUCCESS, CMD_ERROR, CMD_MISSING_ARGS, CMD_NOT_FOUND};

template<typename T>
struct Command {
    std::string name;
    int requiredArgs;
    T hook;
};

int numArgs(const std::string& input, const std::string& cmdName);

int handleCommands(
    const std::string& input,
    const std::vector<Command<void(*)(const std::string&)>>& commands
);

template<typename T, typename K>
int handleCommands(
    const std::string& input,
    const std::vector<Command<T(*)(K)>>& commands,
    const std::function<void(std::string, T, Command<T(*)(K)>)>& parse
);

#endif // COMMANDS_H