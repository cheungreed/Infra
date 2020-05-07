cmake_minimum_required(VERSION 3.6.2)
project(infra_unix_test)

#头文件
include_directories(include)

#设置编译参数
set(CMAKE_CXX_FLAGS "-ffunction-sections -fdata-sections -Wall -std=c++11 -DPOSIX -DDEBUG_")

aux_source_directory(. DIR_TEST_SRCS)

#源文件
add_executable(infra_unix_test ${DIR_TEST_SRCS})

#设置链接库
target_link_libraries(infra_unix_test Infra gtest pthread)
