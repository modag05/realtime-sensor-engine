cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_CXX_STANDARD 17)

add_executable(app
    App.cpp
    Engine/Engine.cpp
    Engine/Engine.h
    JsonGenerator/JsonGenerator.cpp
    JsonGenerator/JsonGenerator.h
    JsonParsa/JsonParser.cpp
    JsonParsa/JsonParser.h
    JsonParsa/Event.h
    Events/EventQueue.h
    Controller/Controller.h
)
