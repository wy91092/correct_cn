/*************************************************************************
  > File Name: workthread.cpp
  > Author: crooked
  > Mail:812665244@qq.com 
  > Created Time: Wed 23 Apr 2014 11:32:02 AM CST
 ************************************************************************/
#include"../inc/threadpool.h"
#include<iostream>
#include<stack>
#include<string.h>
#include<string>
#include<locale.h>
#include<stdlib.h>
#include<fstream>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/types.h>
#include"json/json.h"
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;

static std::string WstringToString(const std::wstring str);
static std::wstring StringToWstring(const std::string str);
static std::string json_string(string &str);
void WorkThread::run()
{
	while(true)
	{
		Task task;
		/*
		 *如果获取任务时，返回值为false,那么说明线程池已经关闭，
		 *所以此时线程需要退出死循环
		 */
		bool ret=_p_thread_pool->get_task_queue(task);
		if(ret==false)
		{
			return;
		}
		compute_task(task);
	}
}

/*static int min(int a, int b, int c){
   int t= a<b?a:b;
   return t<c?t:c;
}

static int ED(const string &a, const string &b){
  int len1=a.size();
  int len2=b.size();
  int d[len1+1][len2+1];
  int i,j;
  for(i=0;i<=len1;i++)
     d[i][0]=i;
  for(j=0;j<=len2;j++)
     d[0][j]=j;
  for(i=1;i<=len1;i++){
     for(j=1;j<=len2;j++){
     int cost=(a[i-1]==b[j-1])?0:1;
     int del=d[i-1][j]+1;
     int ins=d[i][j-1]+1;
     int sub=d[i-1][j-1]+cost;
     d[i][j]=min(del, ins, sub);
     }
   }
   return d[len1][len2];
}*/

void WorkThread::compute_task(struct Task &task)
{
    /*vector<string> word_vec=_p_thread_pool->get_vec();
    vector<string>::size_type ix=0;
    int min=ED(task._expression, word_vec[ix]);
    int result;    //记录相关词的下标
    string correct_word;
    for(ix=1;ix!=word_vec.size();++ix){
     int num= ED(task._expression, word_vec[ix]);
     if(min>num) {
        min=num;
        result=ix;
       }
    }*/
    wstring query=StringToWstring(task._expression);
    //wstring result=_p_thread_pool->_manage.findMostSimilarWord(query);
   wstring top=_p_thread_pool->_manage.findTopKSimilarWords(query, 5);
    //string buf=WstringToString(result);
    string buf_top=WstringToString(top);
  //	sendto(_client_fd,buf.c_str(),buf.size(),0,(struct sockaddr*)&task._addr,sizeof(task._addr) );
  	string jsonstr=json_string(buf_top);
    sendto(_client_fd,jsonstr.c_str(),jsonstr.size(),0,(struct sockaddr*)&task._addr,sizeof(task._addr) );
}

static std::string WstringToString(const std::wstring str){
   unsigned len=str.size() *4;
   setlocale(LC_CTYPE, "");
   char *p=new char[len];
   wcstombs(p, str.c_str(), len);
   std::string str1(p);
   delete[] p;
   return str1;
}
static std::wstring StringToWstring(const std::string str){
   unsigned len=str.size()*2;
   setlocale(LC_CTYPE, "");
   wchar_t *p=new wchar_t[len];
   mbstowcs(p, str.c_str(), len);
   std::wstring str1(p);
   delete[] p;
   return str1;
}
static std::string json_string(string &str){
   Json::Value root;
   Json::Value arr;
   Json::Value elem;
   string title="the top 5";
   string summary=str;
   elem["title"]=title;
   elem["summary"]=summary;
   arr.append(elem);
   root["files"]=arr;
   Json::FastWriter writer;
   Json::StyledWriter stlwriter;
   return stlwriter.write(root);
}

void WorkThread::register_thread_pool(ThreadPool *p_thread_pool)
{
  _p_thread_pool=p_thread_pool;
}

