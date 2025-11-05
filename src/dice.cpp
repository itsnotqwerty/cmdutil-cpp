#include <random>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include "dice.hpp"

std::vector<Die> parseDice(const std::string& input) {
    std::vector<Die> dice;
    std::regex diePattern(R"((\+|-)?(\d+)d(\d+))");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), diePattern);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        for (int j = 0; j < std::stoi(match.str(2)); ++j) {
            Die die;
            die.sign = (match.str(1) != "-");
            die.sides = std::stoi(match.str(3));
            dice.push_back(die);
        }
    }
    return dice;
}

void rollDice(const std::string& input) {
    std::vector<Die> dice = parseDice(input);
    std::vector<int> results;
    for (const auto& die : dice) {
        std::cout << "Rolling " << (die.sign ? "+" : "-") << "1d" << die.sides << "\n";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, die.sides);
        int roll = dis(gen);
        int signed_roll = die.sign ? roll : -roll;
        results.push_back(signed_roll);
        std::cout << "Result: " << signed_roll << "\n";
    }
    std::cout << "Sum: " << std::accumulate(results.begin(), results.end(), 0) << "\n";
}