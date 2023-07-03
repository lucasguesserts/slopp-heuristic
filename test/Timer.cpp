#include "Test.hpp"

#include <chrono>
#include <thread>

#include "Timer/Timer.hpp"
#include "Timer/UserTimer.hpp"
#include "Timer/WallTimer.hpp"

TEST_CASE("WallTimer", "[UserTimer]") {
    const auto sleep_time_nanoseconds = 100000u;
    auto timer = WallTimer::make();
    timer->start();
    std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time_nanoseconds));
    timer->stop();
    CHECK(timer->getDurationNanoseconds() > sleep_time_nanoseconds);
}

auto long_execution_time_function() -> bool {
    const auto number_of_repetitions = 1000u;
    auto acc = 0u;
    for (auto i = 0u; i < number_of_repetitions; ++i) {
        acc += i;
    }
    return acc > 1;
}

TEST_CASE("UserTimer", "[UserTimer]") {
    const auto sleep_time_nanoseconds = 100000u;
    auto timer = UserTimer::make();
    timer->start();
    while (true) {
        timer->stop();
        if (timer->getDurationNanoseconds() > sleep_time_nanoseconds) break;
        timer->start();
        long_execution_time_function();
    }
    CHECK(timer->getDurationNanoseconds() > sleep_time_nanoseconds);
}
