#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "mathutils.hpp"
#include "commands.hpp"

std::vector<boost::multiprecision::cpp_int> fib_cache = {0, 1};
std::vector<boost::multiprecision::cpp_int> factorial_cache = {1, 1};

boost::multiprecision::cpp_int fib(int n) {
    if (n > 100000) throw std::invalid_argument("Input too large for Fibonacci computation");
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
    if (n > 10000) throw std::invalid_argument("Input too large for factorial computation");
    if (n < factorial_cache.size()) {
        return factorial_cache[n];
    }
    for (int i = factorial_cache.size(); i <= n; ++i) {
        factorial_cache.push_back(factorial_cache[i - 1] * i);
    }
    return factorial_cache[n];
}

boost::multiprecision::cpp_int prime(int n) {
    // Sieve of Eratosthenes to find the nth prime
    if (n < 1) throw std::invalid_argument("Input must be >= 1 for prime");
    if (n > 100000000) throw std::invalid_argument("Input too large for prime computation");
    int limit = (n <= 5) ? 15 : n * (std::log(n) + std::log(std::log(n))); // Approximation for nth prime
    std::vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= limit; ++p) {
        if (is_prime[p]) {
            for (int multiple = p * p; multiple <= limit; multiple += p) {
                is_prime[multiple] = false;
            }
        }
    }
    // Count primes and find the nth prime
    int count = 0;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            count++;
            if (count == n) return i;
        }
    }
    throw std::runtime_error("Unreachable");
}

boost::multiprecision::cpp_int help(int n) {
    std::cout << "Math Utilities Available:\n";
    std::cout << "  fib <n>: Compute the nth Fibonacci number\n";
    std::cout << "  fact <n>: Compute the factorial of n\n";
    std::cout << "  prime <n>: Compute the nth prime number\n";
    std::cout << "  help: Display this help message\n";
    return 0;
}

void mathutil(const std::string& input) {
    std::vector<Command<boost::multiprecision::cpp_int(*)(int)>> operations = {
        {"fib", 1, fib},
        {"fact", 1, factorial},
        {"prime", 1, prime},
        {"help", 0, help}
    };

    Command<boost::multiprecision::cpp_int(*)(int)> defaultOperation = {"help", 0, help};

    for (const auto& op : operations) {
        if (input.find(op.name) == 0) {
            if (op.name == "help") {
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