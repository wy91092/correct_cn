/*************************************************************************
	> File Name: lock.cpp
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Fri 11 Apr 2014 01:56:43 PM CST
 ************************************************************************/

#include"../inc/lock.h"
#include"../inc/cond.h"
 Lock::Lock()
{
	pthread_mutex_init(&_mutex,NULL);
}
void Lock::lock()
{
	pthread_mutex_lock(&_mutex);
}
void Lock::unlock()
{
	pthread_mutex_unlock(&_mutex);
}
Lock::~Lock()
{
	pthread_mutex_destroy(&_mutex);
}
