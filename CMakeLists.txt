cmake_minimum_required(VERSION 3.1)
project(ploink VERSION 1.0
            DESCRIPTION "\"Ball game\""
            LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES src/main.cpp src/window.cpp src/bezier.cpp
    src/game.cpp src/line.cpp src/circle.cpp src/vec.cpp)

add_executable(ploink_exe ${SOURCES})
set_property(TARGET ploink_exe PROPERTY CXX_STANDARD 17)

target_include_directories(ploink_exe PRIVATE include)

target_link_libraries(ploink_exe PRIVATE Threads::Threads)
target_link_libraries(ploink_exe PRIVATE ${SDL2_LIBRARIES})
