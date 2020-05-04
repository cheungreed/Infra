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

namespace Zilu {
namespace Infra {

int debugf(const char* format, ...);

int infof(const char* format, ...);

int warnf(const char* format, ...);

int errorf(const char* format, ...);

int fatalf(const char* format, ...);

}
}
