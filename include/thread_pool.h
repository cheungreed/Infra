/*
**	********************************************************************************
**
**	File		: thread_pool.h
**	Description	: 
**	Modify		: 2020/5/5		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once
#include <functional>

namespace Zilu {
namespace Infra {

typedef std::function<int(void)> ThreadTask ;

class CThreadPoolImpl;

class CThreadPool
{
public:
    CThreadPool();
    ~CThreadPool();

    static CThreadPool* instance();

    ///< 开启线程池
    ///<\param num 线程池数,默认4个
    int Start(int num = 4);

    ///< 向线程池塞入执行体
    ///<\param proc 执行体
    ///<\note proc不允许堵塞,返回-1,表示从线程池pop
    int PushTask(const ThreadTask &task);

private:
    CThreadPoolImpl* m_impl;
};

}
}
