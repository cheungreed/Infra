cmake_minimum_required(VERSION 2.8.12.2)
project(Infra)

include_directories(include)

set(CMAKE_CXX_FLAGS "-ffunction-sections -fdata-sections -Wall -std=c++11 -DPOSIX -DDEBUG")

file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.c" ".hpp")

add_executable(Infra ${SOURCE_FILES}
        src/mutex.cpp
        src/thread.cpp
        src/print_log.cpp
        )

target_link_libraries(Infra pthread)
