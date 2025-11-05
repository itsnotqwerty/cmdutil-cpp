#include <iostream>
#include <string>
#include "modules.hpp"

std::vector<boost::multiprecision::cpp_int> fib_cache = {0, 1};
std::vector<boost::multiprecision::cpp_int> factorial_cache = {1, 1};

boost::multiprecision::cpp_int fibonacci(int n) {
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

std::vector<int> factor(int n) {
    if (n <= 0) throw std::invalid_argument("Input must be positive for factorization");
    std::vector<int> factors;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}

void mathutil_help(const std::string& input) {
    std::cout << "Math Utilities Available:\n";
    std::cout << "  fibonacci <n>: Compute the nth Fibonacci number\n";
    std::cout << "  factorial <n>: Compute the factorial of n\n";
    std::cout << "  prime <n>: Compute the nth prime number\n";
    std::cout << "  factorize <n>: Factorize the integer n into its prime factors\n";
    std::cout << "  help: Display this help message\n";
    return;
}

void mathutil(const std::string& input) {
    std::vector<MathModuleType<boost::multiprecision::cpp_int>> bigNumberOperations = {
        {"fibonacci", 1, fibonacci},
        {"factorial", 1, factorial},
        {"prime", 1, prime}
    };

    std::vector<MathModuleType<std::vector<int>>> intArrayOperations = {
        {"factorize", 1, factor}
    };

    ModuleType defaultOperation = {"help", 0, mathutil_help};

    std::vector<int> opCodes = {
        registerModule<boost::multiprecision::cpp_int, int>(bigNumberOperations, input),
        registerModule<std::vector<int>, int>(intArrayOperations, input)
    };

    if (std::all_of(opCodes.begin(), opCodes.end(), [](int n) {return n == CMD_NOT_FOUND;})) {
        if (input.find("help") != 0) {
            std::cout << "Error: Unknown math operation. Use 'mathutil help' for a list of commands.\n";
        }
    } else {
        return;
    }

    defaultOperation.hook("help");
    return;
}