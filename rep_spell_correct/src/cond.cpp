/*************************************************************************
	> File Name: cond.cpp
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Fri 11 Apr 2014 05:05:37 PM CST
 ************************************************************************/

#include"../inc/cond.h"
Cond::Cond(Lock *p_lock):_p_lock(p_lock)
{
   pthread_cond_init(&_cond, NULL);
}
Cond::~Cond()
{
   pthread_cond_destroy(&_cond);
}
void Cond::wait()
{ 
  pthread_cond_wait(&_cond, &(_p_lock->_mutex));
}
void Cond::signal()
{
  pthread_cond_signal(&_cond);
}
void Cond::broadcast()
{
  pthread_cond_broadcast(&_cond);
}

