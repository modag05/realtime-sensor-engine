#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>
#include "../JsonParsa/Event.h"

class EventQueue {
public:

    void push(Event event) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(event);
        }
        condVar_.notify_one();
    }

    std::optional<Event> waitAndPop() {
        std::unique_lock<std::mutex> lock(mutex_);
        condVar_.wait(lock, [this] { return !queue_.empty() || stopped_; });
        if (stopped_ && queue_.empty()) return std::nullopt;
        Event event = queue_.front();
        queue_.pop();
        return event;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stopped_ = true;
        }
        condVar_.notify_all();
    }

private:
    std::queue<Event>        queue_;
    mutable std::mutex       mutex_;
    std::condition_variable  condVar_;
    bool                     stopped_ = false;
};
