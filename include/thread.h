/*
**	********************************************************************************
**
**	File		: thread.h
**	Description	: 
**	Modify		: 2020/4/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once
#include <pthread.h>
#include <functional>

namespace Zilu {
namespace Infra {

typedef std::function<void(void*)> thread_proc_t;

class CThreadImpl;

class CThread
{
public:
    CThread(const std::string &name, uint32_t stacksize=2*1024*1024);
    ~CThread();

    ///< 开启线程
    ///<\param proc线程执行体
    ///<\param user_data用户数据
    ///<\return 0:成功 <0失败
    int Start(const thread_proc_t &proc, const void *user_data = nullptr);

    ///<停止线程
    ///<\return 0成功 <0失败
    int Stop();

    ///< 分离线程
    int Detach();

    ///< 获取线程是否运行
    bool Looping();

    int GetThreadId();

private:
    CThreadImpl*    m_impl;
};

}
}
