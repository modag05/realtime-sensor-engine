#pragma once 
#include <string>
#include <random>
#include <sstream>
#include <iomanip>

class JsonGenerator {
    private:

     std::mt19937                          rng_;
    std::uniform_real_distribution<float> tempDist_;   // ← هو هنا
    std::uniform_real_distribution<float> pressDist_;  // ← هو هنا
    std::uniform_int_distribution<int>    proxDist_;   
      
    
public:
     JsonGenerator() 
     :rng_(std::random_device{}())
        , tempDist_(20.0f, 100.0f)
        , pressDist_(1.0f, 20.0f)
        , proxDist_(0, 4)
    {};
    std::string generateJson(int channelId) ;
    float getValue(int channel)    ;

};