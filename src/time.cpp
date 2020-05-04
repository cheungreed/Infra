/*
**	********************************************************************************
**	File		: Time.cpp
**	Description	: 
**	Modify		: 2019/12/4		zhangqiang		Create the file
**	********************************************************************************
*/
#include "time.hpp"

namespace Zilu {
namespace Infra {

CTime::CTime() : m_nTimeZone(0)
{
    time_t timeSecond;
    time(&timeSecond);

    struct tm* curTime = localtime(&timeSecond);
    m_stm = *curTime;
}

CTime::CTime(time_t tt) : m_nTimeZone(0)
{
    struct tm* stm = localtime(&tt);
    m_stm = *stm;
}

CTime::CTime(std::string &strTime, CTime::StrTimeType type) : m_nTimeZone(0)
{
    std::string format;
    if (type == CTime::STM_TYPE1)
        format = "%04d%02d%02d%02d%02d%02d";
    else if (type == CTime::STM_TYPE2)
        format = "%04d-%02d-%02dT%02d:%02d:%02d";
    else if (type == CTime::STM_TYPE3)
        format = "%04d-%02d-%02d %02d:%02d:%02d";

    sscanf(strTime.c_str(), format.c_str(), &m_stm.tm_year, &m_stm.tm_mon, &m_stm.tm_mday,
           &m_stm.tm_hour, &m_stm.tm_min, &m_stm.tm_sec);

    m_stm.tm_year -= 1900;
    m_stm.tm_mon -= 1;
}

CTime::CTime(struct tm &tm) : m_nTimeZone(0)
{
    m_stm = tm;
}

bool CTime::operator<(CTime &rhs)
{
    return this->ToSince1970() - rhs.ToSince1970() < 0;
}

int CTime::operator-(CTime &rhs)
{
    return this->ToSince1970() - rhs.ToSince1970();
}

time_t CTime::ToSince1970()
{
    return mktime(&m_stm);
}

struct tm CTime::ToStm()
{
    return m_stm;
}

std::string CTime::ToStringTime(CTime::StrTimeType type)
{
    std::string format;
    if (type == CTime::STM_TYPE1)
        format = "%04d%02d%02d%02d%02d%02d";
    else if (type == CTime::STM_TYPE2)
        format = "%04d-%02d-%02dT%02d:%02d:%02d";
    else if (type == CTime::STM_TYPE3)
        format = "%04d-%02d-%02d %02d:%02d:%02d";

    char buf[32] = {0};
    snprintf(buf, sizeof(buf), format.c_str(), m_stm.tm_year+1900, m_stm.tm_mon+1, m_stm.tm_mday,
             m_stm.tm_hour, m_stm.tm_min, m_stm.tm_sec);
    return std::string(buf);
}

bool CTime::SetTimeZone(int zone)
{
    m_nTimeZone = zone; // TODO 时区转换
    return true;
}

}
}
