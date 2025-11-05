#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <boost/multiprecision/cpp_int.hpp>
#include "commands.hpp"

template<typename T, typename K>
int handleCommands(
    const std::string& input,
    const std::vector<Command<T(*)(K)>>& commands,
    const std::function<void(K, T, Command<T(*)(K)>)>& parse
) {
    for (const auto& cmd : commands) {
        if (input.find(cmd.name) == 0) {
            if (cmd.name == "help") {
                cmd.hook(0);
                return CMD_SUCCESS;
            }
            if (input.length() <= cmd.name.length() + 1) {
                std::cout << "Error: Not enough arguments for operation '" << cmd.name << "'\n";
                return CMD_MISSING_ARGS;
            }
            const auto args = input.substr(cmd.name.length() + 1);
            try {
                parse(std::stoi(args), cmd.hook(std::stoi(args)), cmd);
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
                return CMD_ERROR;
            }
            return CMD_SUCCESS;
        }
    }
    return CMD_NOT_FOUND;
}

template int handleCommands<boost::multiprecision::cpp_int, int>(
    const std::string& input,
    const std::vector<Command<boost::multiprecision::cpp_int(*)(int)>>& commands,
    const std::function<void(int, boost::multiprecision::cpp_int, Command<boost::multiprecision::cpp_int(*)(int)>)>& parse
);

template int handleCommands<std::vector<int>, int>(
    const std::string& input,
    const std::vector<Command<std::vector<int>(*)(int)>>& commands,
    const std::function<void(int, std::vector<int>, Command<std::vector<int>(*)(int)>)>& parse
);