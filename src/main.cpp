#include <iostream>
#include "dice.hpp"
#include "mathutils.hpp"
#include "modules.hpp"

void help(const std::string& input) {
    UNUSED(input);
    std::cout << "Available commands:\n";
    std::cout << "  roll <dice>: Roll the specified dice (e.g., 2d6, 1d10-2d4)\n";
    std::cout << "  mathutil <operation> <number>: Perform math operations (e.g., prime, factorize)\n";
    std::cout << "  help: Show this help message\n";
    return;
}

int main(int argc, char* argv[]) {
    std::vector<ModuleType> commands = {
        {"roll", SINGLE_ARG, rollDice},
        {"mathutil", MODULE, mathutil}
    };

    ModuleType defaultCommand = {"help", 0, help};

    std::string input;
    for (int i = 1; i < argc; ++i) {
        input += argv[i];
        if (i < argc - 1) input += " ";
    }

    std::vector<int> opCodes = {
        registerModule(commands, input)
    };

    if (std::all_of(opCodes.begin(), opCodes.end(), [](int n) {return n == CMD_NOT_FOUND;})) {
        if (input.find("help") != 0) {
            std::cout << "Error: Unknown module. Use 'help' for a list of modules.\n";
        }
    } else {
        return 0;
    }

    defaultCommand.hook("help");
    return 0;
}