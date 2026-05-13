#pragma once

#include <string>
#include "../JsonParsa/Event.h"

enum class Action {
    OK,
    WARNING,
    ALERT,
    STOP,
    EMERGENCY_STOP
};

struct Result {
    Action      action;
    std::string message;
};

class Controller {
public:

    Result process(const Event& event) {
        switch (event.channelId) {
            case 0: return handleTemperature(event.value);
            case 1: return handlePressure(event.value);
            case 2: return handleProximity(event.value);
            default: return { Action::OK, "Unknown channel" };
        }
    }

    static std::string actionToString(Action action) {
        switch (action) {
            case Action::OK:             return "OK             🟢";
            case Action::WARNING:        return "WARNING        🟡";
            case Action::ALERT:          return "ALERT          🟠";
            case Action::STOP:           return "STOP           🔴";
            case Action::EMERGENCY_STOP: return "EMERGENCY STOP 🚨";
            default:                     return "UNKNOWN";
        }
    }

private:

    Result handleTemperature(float value) {
        if (value > 80.0f)
            return { Action::EMERGENCY_STOP, "Temperature critical!" };
        if (value > 60.0f)
            return { Action::WARNING, "Temperature high." };
        return { Action::OK, "Temperature normal." };
    }

    Result handlePressure(float value) {
        if (value > 15.0f)
            return { Action::ALERT, "Pressure too high!" };
        return { Action::OK, "Pressure normal." };
    }

    Result handleProximity(float value) {
        if (value == 1.0f)
            return { Action::STOP, "Object detected!" };
        return { Action::OK, "No object detected." };
    }
};