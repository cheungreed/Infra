/*
**	********************************************************************************
**
**	File		: timer.h
**	Description	: 
**	Modify		: 2020/5/5		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once
#include <cstdint>

namespace Zilu {
namespace Infra {

class CTimer
{
public:
    CTimer();
    ~CTimer();

    static void sleep(uint32_t msec);
};

}
}
