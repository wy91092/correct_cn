/*************************************************************************
  > File Name: workthread.h
  > Author: crooked
  > Mail:812665244@qq.com 
  > Created Time: Wed 23 Apr 2014 11:14:07 AM CST
 ************************************************************************/

#ifndef _WORKTHREAD_H_
#define _WORKTHREAD_H
#include<pthread.h>
#include"thread.h"
#include<stack>
#include<string>
#include<string.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
//#include"threadpool.h"
class ThreadPool;
struct Task;
class WorkThread: public Thread
{
	public:
		WorkThread()
		{
		 _client_fd=socket(AF_INET, SOCK_DGRAM, 0);
		}
		void run();
		void compute_task(struct Task &task);//实际的工作函数，由run来调用
		void register_thread_pool(ThreadPool *p_thread_pool);//注册线程池
	/*	std::string getPostfixExp(std::string &infix);
		bool isOperator(char ch);
		int priority(char a);
		int postfixCalculate(std::string &postfix);
		void getTwoNums(std::stack<int> &num_stack, int &first, int &second);*/
	private:
		ThreadPool *_p_thread_pool;//线程池的指针，用来指定线程去哪里获取任务
        int _client_fd;
        
};

#endif
