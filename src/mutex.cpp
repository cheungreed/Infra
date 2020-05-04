/*
**	********************************************************************************
**
**	File		: mutex.cpp
**	Description	: 
**	Modify		: 2020/4/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include "mutex.h"

namespace Zilu {
namespace Infra {


CMutex::CMutex()
{
    pthread_mutex_init(&m_mtx, nullptr);
}

CMutex::~CMutex()
{
}

int CMutex::lock()
{
    pthread_mutex_lock(&m_mtx);
    return 0;
}

int CMutex::unlock()
{
    pthread_mutex_unlock(&m_mtx);
    return 0;
}

int CMutex::trylock()
{
    return pthread_mutex_trylock(&m_mtx);
}


CGuard::CGuard(CMutex &m) : m_mtx(m)
{
    m_mtx.lock();
}

CGuard::~CGuard()
{
    m_mtx.unlock();
}

}
}
