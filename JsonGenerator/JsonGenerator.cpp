#include "JsonGenerator.h"
#include <string>
#include <random>
#include <sstream>
#include <iomanip>



 std::string JsonGenerator::generateJson(int channelId) {
      std::string msg = std::string("{\"channelId\":") + std::to_string(channelId) + 
                          ",\"temperature\":" + std::to_string(tempDist_(rng_)) + 
                          ",\"pressure\":" + std::to_string(pressDist_(rng_)) + 
                          ",\"proximity\":" + std::to_string(proxDist_(rng_)) + "}";
        
        return msg;
    };

float JsonGenerator::getValue(int channel) {
    switch(channel) {
        case 0:
            return tempDist_(rng_);
        case 1:
            return pressDist_(rng_);
        case 2:
            return proxDist_(rng_);
        default:
            return 0.0f;
    }
};

