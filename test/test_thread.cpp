/*
**	********************************************************************************
**
**	File		: test_thread.cpp
**	Description	: 
**	Modify		: 2020/5/7		zhangqiang		Create the file
**	********************************************************************************
*/

#include <gtest/gtest.h>
#include "thread.h"
#include "timer.h"
using namespace Zilu::Infra;

class CTest
{
public:
    CTest(): m_thread("CTest_thread"){}
    ~CTest(){}

    int Start() {
        thread_proc_t proc = std::bind(&CTest::thread_proc, this, std::placeholders::_1);
        m_thread.Start(proc);
    }

    int Stop() {
        m_thread.Stop();
    }

    void thread_proc(void* param)
    {
        std::cout <<"Entry thread_proc.\n";
        while (m_thread.Looping())
        {
            std::cout <<"looping.\n";

            CTimer::sleep(1*1000);
        }
        std::cout <<"exit thread_proc\n";
    }

private:
    CThread     m_thread;
};

TEST(Thread_Case, thread)
{
    CTest test;
    test.Start();
    std::cout <<"222222222\n";
    CTimer::sleep(10* 1000);
    test.Stop();
    std::cout <<"call stop.\n";
    CTimer::sleep(555*1000);
}