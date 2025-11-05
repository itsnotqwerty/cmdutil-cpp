#ifndef PARSING_H
#define PARSING_H

#include "commands.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

template<class T>
struct TypeIsIntVector {
    static const bool value = false;
};

template<>
struct TypeIsIntVector<std::vector<int>> {
    static const bool value = true;
};

template<typename T, typename K>
void parseCommand(K number, T result, const Command<T(*)(K)>& op) {
    std::string opName = op.name;
    opName[0] = toupper(opName[0]);
    printf("%s(%d) = ", opName.c_str(), number);
    if constexpr (std::is_same<T, boost::multiprecision::cpp_int>::value) {
        std::cout << result << "\n";
        return;
    } else if constexpr (TypeIsIntVector<T>::value) {
        std::cout << "[";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i < result.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
        return;
    }
    return;
}

template void parseCommand<boost::multiprecision::cpp_int, int>(int number, boost::multiprecision::cpp_int result, const Command<boost::multiprecision::cpp_int(*)(int)>& op);
template void parseCommand<std::vector<int>, int>(int number, std::vector<int> result, const Command<std::vector<int>(*)(int)>& op);

#endif // PARSING_H