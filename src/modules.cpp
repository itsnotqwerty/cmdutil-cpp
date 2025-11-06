#include "modules.hpp"

int registerModule(
    const std::vector<ModuleType>& opList,
    const std::string& input
) {
    return handleCommands(input, opList);
}

template<typename T, typename K>
int registerMathModule(
    const std::vector<MathModuleType<T>>& opList,
    const std::string& input
) {
    return handleCommands<T, K>(input, opList, parseCommand<T, K>);
}

template int registerMathModule<boost::multiprecision::cpp_int, int>(
    const std::vector<MathModuleType<boost::multiprecision::cpp_int>>& opList,
    const std::string& input
);

template int registerMathModule<std::vector<boost::multiprecision::cpp_int>, int>(
    const std::vector<MathModuleType<std::vector<boost::multiprecision::cpp_int>>>& opList,
    const std::string& input
);

template int registerMathModule<std::vector<int>, int>(
    const std::vector<MathModuleType<std::vector<int>>>& opList,
    const std::string& input
);

template int registerMathModule<std::vector<double>, int>(
    const std::vector<MathModuleType<std::vector<double>>>& opList,
    const std::string& input
);