cmake_minimum_required(VERSION 3.20)

project(DMess)

#EXTERNAL LIBS COMPILATION
add_subdirectory(external/portaudio)
add_subdirectory(external/opus)

#MAIN FILE COMPILE
add_executable(DMess client/main.cpp "include/NetworkClient.h" "include/Encoder.h"  "client/RecordManager.cpp" "client/Encoder.cpp")

#LIBS LINKING
target_link_libraries(DMess PRIVATE portaudio opus)


#INCLUDE DIRECTORIES
target_include_directories(DMess PRIVATE 
							external/opus/include 
							external/portaudio/include
							include
						   )

						 
#OTHER COMMANDS
add_custom_command(TARGET DMess POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:portaudio> $<TARGET_FILE_DIR:DMess> )

