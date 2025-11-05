#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "mathutils.hpp"
#include "commands.hpp"

std::vector<boost::multiprecision::cpp_int> fib_cache = {0, 1};
std::vector<boost::multiprecision::cpp_int> factorial_cache = {1, 1};

boost::multiprecision::cpp_int fib(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n < fib_cache.size()) {
        return fib_cache[n];
    }
    for (int i = fib_cache.size(); i <= n; ++i) {
        fib_cache.push_back(fib_cache[i - 1] + fib_cache[i - 2]);
    }
    return fib_cache[n];
}

boost::multiprecision::cpp_int factorial(int n) {
    if (n < 0) throw std::invalid_argument("Negative input for factorial");
    if (n < factorial_cache.size()) {
        return factorial_cache[n];
    }
    for (int i = factorial_cache.size(); i <= n; ++i) {
        factorial_cache.push_back(factorial_cache[i - 1] * i);
    }
    return factorial_cache[n];
}

boost::multiprecision::cpp_int help(int n) {
    std::cout << "Math Utilities Available:\n";
    std::cout << "  fib <n>: Compute the nth Fibonacci number\n";
    std::cout << "  fact <n>: Compute the factorial of n\n";
    return 0;
}

void mathutil(const std::string& input) {
    std::vector<Command<boost::multiprecision::cpp_int(*)(int)>> operations = {
        {"fib", 1, fib},
        {"fact", 1, factorial},
        {"help", 0, help}
    };

    Command<boost::multiprecision::cpp_int(*)(int)> defaultOperation = {"help", 0, help};

    for (const auto& op : operations) {
        if (input.find(op.name) == 0) {
            if (op.requiredArgs == 0) {
                op.hook(0);
                return;
            }
            if (input.length() <= op.name.length() + 1) {
                std::cout << "Error: Not enough arguments for operation '" << op.name << "'\n";
                return;
            }
            try {
                int number = std::stoi(input.substr(op.name.length() + 1));
                boost::multiprecision::cpp_int result = op.hook(number);
                std::string opName = op.name;
                opName[0] = toupper(opName[0]);
                std::cout << opName << "(" << number << ") = " << result << "\n";
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            return;
        }
    }

    defaultOperation.hook(0);
}