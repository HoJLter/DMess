cmake_minimum_required(VERSION 3.20)

project(DMess)

add_subdirectory(external/portaudio)

add_executable(DMess voice/main.cpp)
target_link_libraries(DMess PRIVATE portaudio)

add_custom_command(TARGET DMess POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:portaudio> $<TARGET_FILE_DIR:DMess> )