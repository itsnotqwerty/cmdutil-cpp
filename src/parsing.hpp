#ifndef PARSING_H
#define PARSING_H

#include "commands.hpp"
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>

template<class T>
struct TypeIsBigNumVector {
    static const bool value = false;
};

template<>
struct TypeIsBigNumVector<std::vector<boost::multiprecision::cpp_int>> {
    static const bool value = true;
};

template<class T>
struct TypeIsIntVector {
    static const bool value = false;
};

template<>
struct TypeIsIntVector<std::vector<int>> {
    static const bool value = true;
};

template<class T>
struct TypeIsDoubleVector {
    static const bool value = false;
};

template<>
struct TypeIsDoubleVector<std::vector<double>> {
    static const bool value = true;
};

template<typename T>
void parseSingleValue(T value, const std::string& args, const std::string& cmdName);

template<typename T>
void parseMultipleValues(std::vector<T> values, const std::string& args, const std::string& cmdName);

template<typename T, typename K>
void parseCommand(std::string args, T result, const Command<T(*)(K)>& op) {
    if constexpr (std::is_same<T, boost::multiprecision::cpp_int>::value) {
        parseSingleValue<boost::multiprecision::cpp_int>(result, args, op.name);
        return;
    } else if constexpr (TypeIsBigNumVector<T>::value) {
        parseMultipleValues<boost::multiprecision::cpp_int>(result, args, op.name);
        return;
    } else if constexpr (TypeIsIntVector<T>::value) {
        parseMultipleValues<int>(result, args, op.name);
        return;
    } else if constexpr (TypeIsDoubleVector<T>::value) {
        parseMultipleValues<double>(result, args, op.name);
        return;
    }
    return;
}

template void parseCommand<boost::multiprecision::cpp_int, int>(std::string args, boost::multiprecision::cpp_int result, const Command<boost::multiprecision::cpp_int(*)(int)>& op);
template void parseCommand<std::vector<int>, int>(std::string args, std::vector<int> result, const Command<std::vector<int>(*)(int)>& op);
template void parseCommand<std::vector<boost::multiprecision::cpp_int>, int>(std::string args, std::vector<boost::multiprecision::cpp_int> result, const Command<std::vector<boost::multiprecision::cpp_int>(*)(int)>& op);
template void parseCommand<std::vector<double>, int>(std::string args, std::vector<double> result, const Command<std::vector<double>(*)(int)>& op);

#endif // PARSING_H