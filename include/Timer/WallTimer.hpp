#ifndef WALL_TIMER_H_
#define WALL_TIMER_H_

#include "Timer.hpp"

#include <chrono>
#include <memory>
#include <stdexcept>

class WallTimer : public Timer {

    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::nanoseconds;
    using TimePoint = std::chrono::time_point<Clock>;

public:
    static auto make() -> TimerPtr {
        return std::make_unique<WallTimer>();
    }

    WallTimer()
        : durationTime(0) {}

    void start() final {
        if (this->isActive) {
            throw std::runtime_error("timer has already started");
        }
        this->isActive = true;
        this->startTime = Clock::now();
        return;
    }

    void stop() final {
        if (!this->isActive) {
            throw std::runtime_error("timer has already stopped");
        }
        this->isActive = false;
        this->stopTime = Clock::now();
        this->durationTime += std::chrono::duration_cast<Duration>(this->stopTime - this->startTime);
        return;
    }

    auto getDurationSeconds() -> double final {
        return std::chrono::duration<double>(this->getDuration()).count();
    }

    auto getDurationNanoseconds() -> int64_t final {
        return std::chrono::duration_cast<std::chrono::duration<int64_t, std::nano>>(this->getDuration()).count();
    }

private:
    bool isActive{false};
    TimePoint startTime;
    TimePoint stopTime;
    Duration durationTime;

    auto getDuration() -> Duration {
        if (this->isActive) {
            throw std::runtime_error("timer is still running");
        }
        return this->durationTime;
    }
};

#endif
