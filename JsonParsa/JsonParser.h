#include "Event.h"
#include <string>

class JsonParser
{
public:
    Event parseJson(const std::string jsonString);
};
