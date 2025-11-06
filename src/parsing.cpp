#include "parsing.hpp"

template<typename T>
void parseSingleValue(T value) {
    std::cout << value << "\n";
    return;
}

template<typename T>
void parseMultipleValues(std::vector<T> values) {
    std::cout << "[";
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i < values.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
    return;
}

template void parseSingleValue<boost::multiprecision::cpp_int>(boost::multiprecision::cpp_int value);
template void parseMultipleValues<boost::multiprecision::cpp_int>(std::vector<boost::multiprecision::cpp_int> values);
template void parseMultipleValues<int>(std::vector<int> values);
template void parseMultipleValues<double>(std::vector<double> values);