/*************************************************************************
  > File Name: threadpool.h
  > Author: crooked
  > Mail:812665244@qq.com 
  > Created Time: Wed 23 Apr 2014 11:15:25 AM CST
 ************************************************************************/
#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_
#include<queue>
#include<vector>
#include<stdio.h>
#include<sys/types.h>
#include"workthread.h"
#include"lock.h"
#include"cond.h"
#include"manageword.h"
#include"noncopyable.h"
#include<netinet/in.h>
#include<arpa/inet.h>
class ManageWord;
struct Task
{
	struct sockaddr_in  _addr;
    std::string _expression;
};

class ThreadPool: public noncopyable
{
	public:
		ThreadPool(std::vector<WorkThread>::size_type max_thread,ManageWord &manage);
		~ThreadPool();

		void start_thread_pool();
		void stop_thread_pool();
		bool add_task_queue(Task task);
		bool get_task_queue(Task &task);

		bool is_task_queue_empty() const;
		std::queue<Task>::size_type get_task_queue_size() const;
       // std::vector<std::string> &get_vec();
        ManageWord _manage;   //管理词库的对象
	private:
		std::queue<Task> _task_queue;   //任务队列
		std::vector<WorkThread>::size_type _max_thread;//线程的数目
		std::vector<WorkThread> _thread_vector;  //用来存储线程
        //std::vector<std::string> _manage_word;
		bool _is_started;     //标记线程池是否开启
		mutable Lock _lock;   //用来保持对队列的互斥操作
		mutable Cond _cond;   //实现对队列任务的同步操作
};
#endif
