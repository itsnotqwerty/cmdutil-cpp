#ifndef DICE_H
#define DICE_H

#include <string>
#include <vector>

struct Die {
    int sides;
    bool sign;
};

std::vector<Die> parseDice(const std::string& input);
void rollDice(const std::string& input);

#endif // DICE_H