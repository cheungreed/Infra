cmake_minimum_required(VERSION 2.8.12.2)
project(MyInfra)

include_directories(Include)

set(CMAKE_CXX_FLAGS "-ffunction-sections -fdata-sections -Wall -std=c++11 -DPOSIX -DDEBUG")

file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.c" ".hpp")

add_executable(MyInfra ${SOURCE_FILES})
