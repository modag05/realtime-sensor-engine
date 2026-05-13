#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "../JsonGenerator/JsonGenerator.h"
#include "../JsonParsa/JsonParser.h"
#include "../Events/EventQueue.h"
#include "../Controller/Controller.h"

class Engine {
public:
    void start();
    void stop();
    void run();

private:
    JsonGenerator           generator_;
    JsonParser              parser_;
    EventQueue              queue_;
    Controller              controller_;
    std::atomic<bool>       running_{false};
    std::thread             producer_;
    std::thread             consumer_;
    std::condition_variable sleepCv_;
    std::mutex              sleepMu_;

    void producerLoop();
    void consumerLoop();
};
