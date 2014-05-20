/*************************************************************************
	> File Name: cond.h
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Fri 11 Apr 2014 05:02:04 PM CST
 ************************************************************************/

#ifndef _COND_H_
#define _COND_H_
#include<pthread.h>
#include"lock.h"
#include"noncopyable.h"
class Cond:public noncopyable
{
 private:
	 pthread_cond_t _cond;
	 Lock *_p_lock;  //这里要用指针
 public:
     Cond(Lock *p_lock);
	  ~Cond();
	 void wait();
     void signal();
     void broadcast();//谨慎使用
};
#endif
