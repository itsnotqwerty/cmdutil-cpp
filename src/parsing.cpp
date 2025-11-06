#include <regex>
#include "parsing.hpp"
#include "commands.hpp"

template<typename T>
void parseSingleValue(T value, const std::string& args, const std::string& cmdName) {
    std::string opName = cmdName;
    opName[0] = toupper(opName[0]);
    printf("%s(%s) = ", opName.c_str(), args.c_str());
    std::cout << value << "\n";
    return;
}

template<typename T>
void parseMultipleValues(std::vector<T> values, const std::string& args, const std::string& cmdName) {
    const std::vector<std::string> argList = [&]() {
        std::vector<std::string> argsVec;
        std::regex ws_re(R"(\s+)");
        std::regex range_re(R"((\d+),(\d+))");
        std::sregex_token_iterator iter(args.begin(), args.end(), ws_re, -1);
        std::sregex_token_iterator end;
        while (iter != end) {
            if (iter->str().find("-") == 0) {
                std::string flag = *iter;
                if (flag == "-i") {
                    ++iter;
                    if (iter == end) {
                        throw std::invalid_argument("Missing index value after -i flag for command '" + cmdName + "'");
                    }
                    try {
                        std::stoi(iter->str());
                    } catch (const std::invalid_argument& e) {
                        throw std::invalid_argument("Invalid index value after -i flag for command '" + cmdName + "'");
                    }
                    argsVec.push_back(flag + " " + iter->str());
                } else if (flag == "-r") {
                    ++iter;
                    if (iter == end) {
                        throw std::invalid_argument("Missing range value after -r flag for command '" + cmdName + "'");
                    }
                    std::smatch match;
                    std::string rangeStr = iter->str();
                    if (std::regex_match(rangeStr, match, range_re)) {
                        argsVec.push_back(flag + " " + rangeStr);
                    } else {
                        throw std::invalid_argument("Invalid range format after -r flag for command '" + cmdName + "'");
                    }
                } else {
                    throw std::invalid_argument("Unknown flag '" + flag + "' for command '" + cmdName + "'");
                }
            }
            ++iter;
        }
        return argsVec;
    }();
    std::regex indexPattern(R"(-i (\d+))");
    bool indexFlag = false;
    int index = -1;

    std::regex rangePattern(R"(-r (\d+),(\d+))");
    bool rangeFlag = false;
    int rangeStart = -1;
    int rangeEnd = -1;

    for (const auto& arg : argList) {
        std::smatch match;
        if (std::regex_match(arg, match, indexPattern)) {
            indexFlag = true;
            index = std::stoi(match[1]);
            if (index < 0 || index >= static_cast<int>(values.size())) {
                throw std::out_of_range("Index " + std::to_string(index) + " out of range for command '" + cmdName + "'");
            }
        } else if (std::regex_match(arg, match, rangePattern)) {
            rangeFlag = true;
            rangeStart = std::stoi(match[1]);
            rangeEnd = std::stoi(match[2]);
            if (rangeStart < 0 || rangeEnd >= static_cast<int>(values.size()) || rangeStart > rangeEnd) {
                throw std::out_of_range("Invalid range " + std::to_string(rangeStart) + "," + std::to_string(rangeEnd) + " for command '" + cmdName + "'");
            }
        }
    }

    int arg = std::stoi(args);
    std::string opName = cmdName;
    opName[0] = toupper(opName[0]);
    printf("%s(%d) = ", opName.c_str(), arg);

    std::cout << "[";
    if (indexFlag) {
        std::cout << values[index];
    } else if (rangeFlag) {
        for (int i = rangeStart; i <= rangeEnd; ++i) {
            std::cout << values[i];
            if (i < rangeEnd) {
                std::cout << ", ";
            }
        }
    } else {
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << values[i];
            if (i < values.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << "]\n";
    return;
}

template void parseSingleValue<boost::multiprecision::cpp_int>(boost::multiprecision::cpp_int value, const std::string& args, const std::string& cmdName);
template void parseMultipleValues<boost::multiprecision::cpp_int>(std::vector<boost::multiprecision::cpp_int> values, const std::string& args, const std::string& cmdName);
template void parseMultipleValues<int>(std::vector<int> values, const std::string& args, const std::string& cmdName);
template void parseMultipleValues<double>(std::vector<double> values, const std::string& args, const std::string& cmdName);