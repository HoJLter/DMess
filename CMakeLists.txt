cmake_minimum_required(VERSION 3.20)

project(DMess)

add_subdirectory(external/rtaudio)

add_executable(DMess voice/main.cpp)
target_link_libraries(DMess PRIVATE rtaudio)