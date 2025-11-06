#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <boost/multiprecision/cpp_int.hpp>
#include "commands.hpp"


int numArgs(const std::string& input, const std::string& cmdName) {
    if (input.length() <= cmdName.length() + 1) {
        return 0;
    }
    std::string args = input.substr(cmdName.length() + 1);
    int count = 1;
    for (char c : args) {
        if (c == ' ') {
            count++;
        }
    }
    return count;
}


int handleCommands(
    const std::string& input,
    const std::vector<Command<void(*)(const std::string&)>>& commands
) {
    for (const auto& cmd : commands) {
        if (input.find(cmd.name) == 0) {
            const int argc = numArgs(input, cmd.name);
            if (cmd.requiredArgs > 0 && cmd.requiredArgs > argc) {
                std::cout << "Error: Not enough arguments for operation '" << cmd.name << "'\n";
                return CMD_MISSING_ARGS;
            }

            if (cmd.requiredArgs == 0 && argc == 0) {
                try {
                    cmd.hook("");
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                    return CMD_ERROR;
                }
                return CMD_SUCCESS;
            }

            const auto args = input.substr(cmd.name.length() + 1);
            try {
                cmd.hook(args);
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
                return CMD_ERROR;
            }
            return CMD_SUCCESS;
        }
    }
    return CMD_NOT_FOUND;
}

template<typename T, typename K>
int handleCommands(
    const std::string& input,
    const std::vector<Command<T(*)(K)>>& commands,
    const std::function<void(std::string, T, Command<T(*)(K)>)>& parse
) {
    for (const auto& cmd : commands) {
        if (input.find(cmd.name) == 0) {
            const int argc = numArgs(input, cmd.name);
            if (cmd.requiredArgs > 0 && cmd.requiredArgs > argc) {
                std::cout << "Error: Not enough arguments for operation '" << cmd.name << "'\n";
                return CMD_MISSING_ARGS;
            }

            if (cmd.requiredArgs == 0 && argc == 0) {
                try {
                    cmd.hook(1);
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                    return CMD_ERROR;
                }
                return CMD_SUCCESS;
            }

            const auto args = input.substr(cmd.name.length() + 1);
            try {
                parse(args, cmd.hook(std::stoi(args)), cmd);
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
    const std::function<void(std::string, boost::multiprecision::cpp_int, Command<boost::multiprecision::cpp_int(*)(int)>)>& parse
);

template int handleCommands<std::vector<boost::multiprecision::cpp_int>, int>(
    const std::string& input,
    const std::vector<Command<std::vector<boost::multiprecision::cpp_int>(*)(int)>>& commands,
    const std::function<void(std::string, std::vector<boost::multiprecision::cpp_int>, Command<std::vector<boost::multiprecision::cpp_int>(*)(int)>)>& parse
);

template int handleCommands<std::vector<int>, int>(
    const std::string& input,
    const std::vector<Command<std::vector<int>(*)(int)>>& commands,
    const std::function<void(std::string, std::vector<int>, Command<std::vector<int>(*)(int)>)>& parse
);

template int handleCommands<std::vector<double>, int>(
    const std::string& input,
    const std::vector<Command<std::vector<double>(*)(int)>>& commands,
    const std::function<void(std::string, std::vector<double>, Command<std::vector<double>(*)(int)>)>& parse
);