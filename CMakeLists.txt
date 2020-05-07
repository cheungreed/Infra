cmake_minimum_required(VERSION 2.8.12.2)
project(Infra)

set(CMAKE_BUILD_TYPE "Debug")

#头文件
include_directories(include)

#设置编译参数
set(CMAKE_CXX_FLAGS "-ffunction-sections -fdata-sections -Wall -std=c++11 -DPOSIX -DDEBUG_")

#加载所有源文件
aux_source_directory(src/ DIR_SRCS)

#add_subdirectory(src)
add_subdirectory(test)

#生成静态库
add_library(Infra ${DIR_SRCS})

##生成动态库
#add_library(StreamResolver_S SHARED
#        Src/rtp/rtp_demux.cpp
#        Src/rtp/rtp_header.cpp
#        Src/ps/ps_demux.cpp)

target_link_libraries(Infra pthread)

