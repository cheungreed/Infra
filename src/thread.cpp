/*
**	********************************************************************************
**
**	File		: thread.cpp
**	Description	: 
**	Modify		: 2020/4/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include "thread.h"
#include <errno.h>
#include <print_log.h>
#include <cstring>
#include <sys/prctl.h>

namespace Zilu {
namespace Infra {

class CThreadImpl
{
public:
    CThreadImpl(const std::string &name, uint32_t stacksize);

    ~CThreadImpl();

    int Start(const thread_proc_t &proc, const void *user_data);

    int Stop();

    int Detach();

    bool Looping();

    void ThreadProc();

    int GetThreadId();

private:
    bool            m_detach;
    bool            m_looping;                ///< 线程运行标志

    uint32_t        m_stacksize;

    void *          m_userdata;               ///<用户数据
    std::string     m_threadName;               ///<线程名称
    pthread_t       m_tid;
    thread_proc_t   m_proc;                 ///< 用户注册的执行体
};

static void *thread_proc(void *arg)
{
    debugf("Entry thread proc, this: %p\n", arg);
    CThreadImpl *impl = (CThreadImpl *) arg;
    if (impl != nullptr)
    {
        impl->ThreadProc();
    }

    return nullptr;
}

CThreadImpl::CThreadImpl(const std::string &name, uint32_t stacksize)
    : m_looping(false),m_stacksize(stacksize), m_threadName(name)
{
    debugf("create thread, this: %p\n", this);
}

CThreadImpl::~CThreadImpl()
{
    debugf("destroy thread, this: %p\n", this);
}

int CThreadImpl::Start(const thread_proc_t &proc, const void *user_data)
{
    if (m_looping) {
        debugf("thread this: %p already created.", this);
        return -1;
    }

    m_proc = proc;
    m_userdata = const_cast<void*>(user_data);

    m_detach = false;

    ///< 先赋值,防止pthread_create函数未返回,先执行线程体
    m_looping = true;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, m_stacksize);

    int r = pthread_create(&m_tid, &attr, thread_proc, this);
    if ( r != 0) {
        debugf("create thread failed, errno: %s", strerror(errno));
        return -1;
    }

    pthread_attr_destroy(&attr);

    return 0;
}

int CThreadImpl::Stop()
{
    debugf("stop thread start, this: %p", this);
    m_looping = false;

    if (!m_detach) {
        pthread_join(m_tid, nullptr);
    }

    debugf("stop thread end, this: %p", this);
    return 0;
}

int CThreadImpl::Detach()
{
    m_detach = true;
    int err = pthread_detach(m_tid);
    if ( err != 0) {
        debugf("detach thread failed, err: %s", strerror(err));
        return -1;
    }
    return 0;
}

bool CThreadImpl::Looping()
{
    return m_looping;
}

int CThreadImpl::GetThreadId()
{
    return m_tid;
}

void CThreadImpl::ThreadProc()
{
    m_tid = pthread_self();

    ::prctl(PR_SET_NAME, m_threadName.c_str());

    m_proc(m_userdata);
}

/////////////////////////Thread Warp/////////////////////////////

CThread::CThread(const std::string &name, uint32_t stacksize)
{
    m_impl = new CThreadImpl(name, stacksize);
}

CThread::~CThread()
{
    if (m_impl != nullptr) {
        delete m_impl;
        m_impl = nullptr;
    }
}

int CThread::Start(const thread_proc_t &proc, const void *user_data)
{
    return m_impl->Start(proc, user_data);
}

int CThread::Stop()
{
    return m_impl->Stop();
}

int CThread::Detach()
{
    return m_impl->Detach();
}

bool CThread::Looping()
{
    return m_impl->Looping();
}

int CThread::GetThreadId()
{
    return m_impl->GetThreadId();
}

}
}
