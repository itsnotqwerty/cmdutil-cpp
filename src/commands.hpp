#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <string>

template<typename T>
struct Command {
    std::string name;
    int requiredArgs;
    T hook;
};

template<typename T, typename K>
int handleCommands(
    const std::string& input,
    const std::vector<Command<T(*)(K)>>& commands,
    const std::function<void(K, T, Command<T(*)(K)>)>& parse
);

#endif // COMMANDS_H