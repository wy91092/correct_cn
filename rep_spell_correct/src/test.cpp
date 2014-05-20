/*************************************************************************
  > File Name: test.cpp
  > Author: crooked
  > Mail:812665244@qq.com 
  > Created Time: Wed 23 Apr 2014 12:17:05 PM CST
 ************************************************************************/

#include"../inc/threadpool.h"
#include"../inc/socket.h"
#include"../inc/manageword.h"
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<fstream>
#include<string.h>
#include<stdio.h>
using namespace std;

int main(int argc, char **argv)
{
    if(argc<3)
    {
     std::cout<<"arguments too few"<<std::endl;;
    }
	std::ifstream fin(argv[1]);
	std::string ip,port;
	fin>>ip>>port;
//  ip="192.168.21.136";
//	port="6688";
	std::cout<<ip<<" "<<port<<std::endl;
	const socklen_t len=1024;
	char buf[len];
	MySocket a_socket(ip, port);
    std::string filename=argv[2];
    ManageWord manage(filename);
	pid_t pid;
    pid=fork();
    if(pid==-1)
    {
    std::cout<<"fork failed"<<std::endl;
    }
    else if(pid==0)
   {
	ThreadPool pool(10,manage);
	pool.start_thread_pool();
    while(true)
	{
		memset(buf, 0, len);
		int ret=a_socket.recv_message(buf, len); 
		cout<<ret<<endl;
		Task tmp;
		tmp._addr=a_socket.get_client();
		tmp._expression=buf;
		pool.add_task_queue(tmp);
		sleep(1);
	}
    pool.stop_thread_pool();
   }
    else
   {
    exit(0);
   }
	return 0;

}
