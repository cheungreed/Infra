/*
**	********************************************************************************
**
**	File		: thread_pool.cpp
**	Description	: 
**	Modify		: 2020/5/5		zhangqiang		Create the file
**	********************************************************************************
*/
#include <list>
#include <vector>
#include "thread_pool.h"
#include "thread.h"
#include "print_log.h"
#include "mutex.h"
#include "timer.h"

namespace Zilu {
namespace Infra {

class CSingleThread
{
public:
    CSingleThread(int index) : m_thread("ThreadPool_"+std::to_string(index))
    {
        thread_proc_t proc = std::bind(&CSingleThread::thread_proc, this, std::placeholders::_1);
        int r = m_thread.Start(proc);
        if (r != 0) {
            errorf("ThreadPool_%d start failed.", index);
        } else {
            debugf("ThreadPool_%d start success.", index);
        }
    }

    ~CSingleThread() {}

    int PushTask(const ThreadTask& task) {
        CGuard g(m_mtx);
        m_tasks.push_back(task);
        return 0;
    }

    int GetTaskSize() {
        CGuard g(m_mtx);
        return m_tasks.size();
    }

private:
    void thread_proc(void* param)
    {
        while (m_thread.Looping())
        {
            CGuard g(m_mtx);
            for (auto itr = m_tasks.begin(); itr != m_tasks.end();) {
                if ((*itr)() == -1) {
                    itr = m_tasks.erase(itr);
                } else {
                    ++itr;
                }
            }
            CTimer::sleep(40);
        }
    }

private:
    CMutex                      m_mtx;
    CThread                     m_thread;
    std::list<ThreadTask>       m_tasks;
};

////////////// CThreadPoolImpl /////////////////////////////////////
class CThreadPoolImpl
{
public:
    CThreadPoolImpl(int num);
    ~CThreadPoolImpl();

    int Start(int num);

    int PushTask(const ThreadTask& task);

private:
    CMutex                         m_mtx;
    std::vector<CSingleThread* >   m_pool;
};

CThreadPoolImpl::CThreadPoolImpl(int num)
{

}

CThreadPoolImpl::~CThreadPoolImpl()
{

}

int CThreadPoolImpl::Start(int num)
{
    for (auto i =0; i <num; ++i) {
        CSingleThread* thread = new CSingleThread(i);
        m_pool.push_back(thread);
    }
    debugf("Start ThreadPool num: %d", num);
    return 0;
}

int CThreadPoolImpl::PushTask(const ThreadTask &task)
{
    CGuard g(m_mtx);
    ///< 查找出任务数最少的线程
    int min = 0;
    for (auto i =1; i <m_pool.size(); ++i) {
        if (m_pool[min]->GetTaskSize() > m_pool[i]->GetTaskSize()) {
            min = i;
        }
    }
    m_pool[min]->PushTask(task);
    return 0;
}

/////////////////////////// CThreadPool //////////////////////////////////
CThreadPool::CThreadPool() {}

CThreadPool::~CThreadPool()
{
    if (m_impl != nullptr) {
        delete m_impl;
        m_impl = nullptr;
    }
}

CThreadPool *CThreadPool::instance()
{
    static CThreadPool _inst;
    return &_inst;
}

int CThreadPool::Start(int num)
{
    m_impl = new CThreadPoolImpl(num);

    m_impl->Start(num);
    return 0;
}

int CThreadPool::PushTask(const ThreadTask &task)
{
    m_impl->PushTask(task);
    return 0;
}

}
}
