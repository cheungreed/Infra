/*
**	********************************************************************************
**
**	File		: timer.cpp
**	Description	: 
**	Modify		: 2020/5/5		zhangqiang		Create the file
**	********************************************************************************
*/
#include "timer.h"
#include <time.h>

namespace Zilu {
namespace Infra {


CTimer::CTimer()
{

}

CTimer::~CTimer()
{

}

void CTimer::sleep(uint32_t msec)
{
    struct timespec req;
    req.tv_sec = msec / 1000;
    req.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&req, nullptr);
}

}
}
