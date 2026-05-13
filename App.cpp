#include <csignal>
#include <iostream>
#include "Engine/Engine.h"

static Engine* g_engine = nullptr;

void signalHandler(int) {
    if (g_engine) g_engine->stop();
}

int main() {
    Engine engine;
    g_engine = &engine;
    std::signal(SIGINT, signalHandler);
    engine.run();
}
