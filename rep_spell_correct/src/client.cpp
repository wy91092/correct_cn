/*************************************************************************
	> File Name: client.cpp
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Mon 28 Apr 2014 09:40:02 AM CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<fstream>
#include<string>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdexcept>
#include<locale.h>
using namespace std;
std::wstring StringToWstring(const std::string str){
     unsigned len =str.size()*2;     //预留字节数
     setlocale(LC_CTYPE, "");        //必须调用此函数
     wchar_t *p=new wchar_t[len];    //申请一段内存存放转换后的字符串
     mbstowcs(p, str.c_str(), len);  //转换
     std::wstring str1(p);
     delete[] p;                     //释放申请的内存
     return str1;
}

std::string WstringToString(const std::wstring str){
    unsigned len=str.size() *4;
    setlocale(LC_CTYPE, "");
    char *p=new char[len];
    wcstombs(p, str.c_str(), len);
    std::string str1(p);
    delete[] p;
    return str1;
}

int main(int argc, char *argv[])
{
    std::ifstream fin(argv[1]);
	std::string ip, port;
	fin >> ip >> port;
  //  std::wcout<<ip<<L" "<<L" port "<<port <<std::endl;
    int server_fd=socket(AF_INET, SOCK_DGRAM, 0);
	if(server_fd==-1)
	{
	  throw std::runtime_error("socket");
	}
    struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(port.c_str()));
	server_addr.sin_addr.s_addr=inet_addr(ip.c_str());
    char buf[128]="";
    std::string word;
	while(std::cin>>word)
	{
	  int iret=sendto(server_fd, word.c_str(),word.size(),0,(struct sockaddr*)&server_addr, 16);
	  recvfrom(server_fd, buf, 128, 0, NULL, NULL);
      string _buf(buf);
      std::wstring wbuf=StringToWstring(_buf);
      std::wcout<<wbuf<<std::endl;
      std::wcout.flush();
      memset(buf, 0, 128);
	}
	return 0;
}
