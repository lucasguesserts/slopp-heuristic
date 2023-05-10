#ifndef TIMER_H_
#define TIMER_H_

#include <cstdint>
#include <memory>

class Timer { // NOLINT(cppcoreguidelines-special-member-functions)

public:
    virtual void start() = 0;
    virtual void stop() = 0;

    virtual auto getDurationSeconds() -> double = 0;
    virtual auto getDurationNanoseconds() -> int64_t = 0;

    virtual ~Timer() = default;
};

using TimerPtr = std::unique_ptr<Timer>;

#endif
