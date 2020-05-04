/*
**	********************************************************************************
**
**	File		: mutex.h
**	Description	: 
**	Modify		: 2020/4/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once
#include <pthread.h>

namespace Zilu {
namespace Infra {

class CMutex
{
public:
    CMutex();
    ~CMutex();

    int lock();

    int unlock();

    ///< 尝试加锁
    ///<\return 0: mutex未加锁直接返回 EBUSY: mutex已加锁
    int trylock();

private:
    pthread_mutex_t     m_mtx;
};

class CGuard
{
public:
    CGuard(CMutex& m);
    ~CGuard();

private:
    CMutex& m_mtx;
};

}
}
