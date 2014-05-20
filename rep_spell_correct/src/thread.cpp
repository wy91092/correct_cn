/*************************************************************************
	> File Name: thread.cpp
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Mon 14 Apr 2014 01:37:42 PM CST
 ************************************************************************/

#include"../inc/thread.h"
#include<iostream>
using namespace std;
Thread::Thread():_tid(0)//,_sleep(2)
{}
Thread::~Thread()
{}
void * Thread::thread_func(void *arg)
{
	//arg实际上是线程对象的指针，类型为实际线程的类型
 Thread *p_thread=static_cast<Thread*>(arg);
 //这里利用了动态绑定
 p_thread->run();
 return NULL;
}
void Thread::join()
{
  pthread_join(_tid, NULL);
}
void Thread::start()
{//采用静态函数的指针作为回调函数
	//this作为线程的参数
   pthread_create(&_tid, NULL, thread_func, this);
}
pthread_t Thread::get_tid() const
{
  return _tid;
}
