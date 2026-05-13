#include "Engine.h"
#include <iostream>
#include <chrono>

void Engine::start() {
    running_ = true;
    producer_ = std::thread(&Engine::producerLoop, this);
    consumer_ = std::thread(&Engine::consumerLoop, this);
    std::cout << "[Engine] Started.\n";
}

void Engine::stop() {
    std::cout << "\n[Engine] Stopping...\n";
    running_ = false;
    sleepCv_.notify_all();
    queue_.stop();
}

void Engine::run() {
    start();
    if (producer_.joinable()) producer_.join();
    if (consumer_.joinable()) consumer_.join();
    std::cout << "[Engine] Shutdown complete.\n";
}

void Engine::producerLoop() {
    while (running_) {
        for (int ch = 0; ch < 3 && running_; ch++) {
            Event event = parser_.parseJson(generator_.generateJson(ch));
            queue_.push(event);
        }
        std::unique_lock<std::mutex> lock(sleepMu_);
        sleepCv_.wait_for(lock, std::chrono::seconds(10),
                          [this] { return !running_.load(); });
    }
}

void Engine::consumerLoop() {
    while (true) {
        auto e = queue_.waitAndPop();
        if (!e) break;
        Result result = controller_.process(*e);
        std::cout << "CH" << e->channelId
                  << " | " << e->value
                  << " | " << Controller::actionToString(result.action)
                  << " | " << result.message << "\n";
    }
}
