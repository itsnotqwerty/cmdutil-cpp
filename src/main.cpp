#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "dice.hpp"
#include "mathutils.hpp"
#include "modules.hpp"

void help(const std::string& input) {
    std::cout << "Available commands:\n";
    std::cout << "  roll <dice>: Roll the specified dice (e.g., 2d6, 1d10-2d4)\n";
    std::cout << "  mathutil <operation> <number>: Perform math operations (e.g., prime, factorize)\n";
    std::cout << "  help: Show this help message\n";
}

int main(int argc, char* argv[]) {
    std::vector<ModuleType> commands = {
        {"roll", 1, rollDice},
        {"mathutil", 0, mathutil},
        {"help", 0, help}
    };

    ModuleType defaultCommand = {"help", 0, help};

    if (argc > 1) {
        std::string command = argv[1];

        for (const auto& cmd : commands) {
            if (command == cmd.name) {
                if (cmd.requiredArgs + 1 >= argc) {
                    std::cout << "Error: Not enough arguments for command '" << cmd.name << "'\n";
                    return 1;
                }
                std::string input;
                for (int i = 2; i < argc; ++i) {
                    input += argv[i];
                    if (i < argc - 1) input += " ";
                }
                cmd.hook(input);
                return 0;
            }
        }
    }
    defaultCommand.hook("help");
    return 0;
}