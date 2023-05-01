#include "fibonacci.hpp"

#include <vector>

constexpr auto initial_fibonacci_values = {0lu, 1lu};

auto fibonacci(const Value n) -> decltype(n) {
    static auto values = std::vector<Value>{initial_fibonacci_values};
    if (n < values.size()) {
        return values[n];
    } else {
        const auto result = fibonacci(n - 1) + fibonacci(n - 2);
        values.push_back(result);
        return result;
    }
}
