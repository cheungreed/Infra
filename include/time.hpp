/*
**	********************************************************************************
**	File		: time.h
**	Description	: 
**	Modify		: 2019/12/4		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <ctime>
#include <string>
#include "time.hpp"

namespace Zilu {
namespace Infra {

class CTime
{
public:
    enum StrTimeType {
        STM_TYPE1,      /// "20191203192854"
        STM_TYPE2,      /// "2019-12-03T19:28:54"
        STM_TYPE3       /// "2019-12-03 19:28:54"
    };
    ///\brief 当前时间
    CTime();

    CTime(time_t tt);

    ///\brief 支持"2019-12-03T19:28:54", "2019-12-03 19:28:54","20191203192854" 三种格式
    CTime(std::string& strTime, StrTimeType type);

    CTime(struct tm& tm);

    bool operator <(CTime& rhs);
    int operator - (CTime& rhs);

    time_t ToSince1970();

    struct tm ToStm();

    std::string ToStringTime(StrTimeType type);

    bool SetTimeZone(int zone);

private:
    int m_nTimeZone;
    struct tm m_stm;
};

}
}
