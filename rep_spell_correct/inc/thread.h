/*************************************************************************
	> File Name: thread.h
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Mon 14 Apr 2014 01:36:33 PM CST
 ************************************************************************/

#ifndef _THREAD_H_
#define _THREAD_H_
#include<pthread.h>
#include<iostream>
class Thread
{
 private:
	 pthread_t _tid; 
 public:
	 //int _sleep;
    Thread();
    virtual	~Thread();
	virtual void run() =0;
    void start();
	static void *thread_func(void*arg);
    void join();
	pthread_t get_tid() const;
};
#endif
