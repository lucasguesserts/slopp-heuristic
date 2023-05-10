#ifndef USER_TIMER_H_
#define USER_TIMER_H_

#include "Timer.hpp"

#include <memory>

#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

class UserTimer : public Timer {

    using BoostTimer = boost::timer::cpu_timer;
    using Duration = boost::chrono::nanoseconds;
    using DurationSeconds = boost::chrono::duration<double>; // seconds, stored with a double

public:
    static auto make() -> TimerPtr {
        return std::make_unique<UserTimer>();
    }

    UserTimer()
        : timer() {
        timer.stop();
    }

    void start() final {
        if (!this->timer.is_stopped()) {
            throw std::runtime_error("timer has already started");
        }
        this->timer.resume();
        return;
    }

    void stop() final {
        if (this->timer.is_stopped()) {
            throw std::runtime_error("timer has already stopped");
        }
        this->timer.stop();
        return;
    }

    auto getDurationSeconds() -> double final {
        return DurationSeconds(this->getDuration()).count();
    }

    auto getDurationNanoseconds() -> int64_t final {
        return static_cast<int64_t>(this->getDuration().count());
    }

private:
    BoostTimer timer;

    auto getDuration() -> Duration {
        if (!this->timer.is_stopped()) {
            throw std::runtime_error("timer is still running");
        }
        return boost::chrono::nanoseconds(this->timer.elapsed().user);
    }
};

#endif
