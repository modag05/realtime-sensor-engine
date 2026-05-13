#include "Event.h"
#include <string>
#include "JsonParser.h"

Event JsonParser::parseJson(const std::string jsonString) {
    Event event;
    size_t channelIdPos = jsonString.find("\"channelId\":");
    size_t valuePos = jsonString.find(",\"temperature\":");
    
    if (channelIdPos != std::string::npos && valuePos != std::string::npos) {
        event.channelId = std::stoi(jsonString.substr(channelIdPos + 12, valuePos - (channelIdPos + 12)));
        event.value = std::stof(jsonString.substr(valuePos + 15));
    }
    
    return event;
}