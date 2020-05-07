/*
**	********************************************************************************
**
**	File		: print_log.hpp
**	Description	: 
**	Modify		: 2020/4/29		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once
#include <stdio.h>
#include <cstdint>
#include <string>

namespace Zilu {
namespace Infra {

int debugf(const char* format, ...);

int infof(const char* format, ...);

int warnf(const char* format, ...);

int errorf(const char* format, ...);

int fatalf(const char* format, ...);

int setLogLevel(uint32_t level);
int setLogPath(const std::string& path, const std::string& name);

}
}
