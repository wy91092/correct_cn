/*************************************************************************
	> File Name: socket.h
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Fri 25 Apr 2014 04:40:11 PM CST
 ************************************************************************/
#ifndef _SOCKET_H_
#define _SOCKET_H_
#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdexcept>
class MySocket
{
    private:
		int _server_fd;//_len;
		socklen_t _len;
		struct sockaddr_in _server_addr,_client_addr;
		MySocket(const MySocket &);
		MySocket& operator=(const MySocket &);
	public:
		MySocket(const std::string &ip, const std::string &port)
	//	MySocket()
		{
		 if((_server_fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		 {
		   throw std::runtime_error("socket");
		 }
		 _server_addr.sin_family=AF_INET;
		 _server_addr.sin_port=htons(atoi(port.c_str()));
		 //_server_addr.sin_port=htons(atoi("6688"));
		 _server_addr.sin_addr.s_addr=inet_addr(ip.c_str());
		// _server_addr.sin_addr.s_addr=inet_addr("192.168.21.136");
		 if(-1==(bind(_server_fd,(struct sockaddr*)&_server_addr,sizeof(_server_addr) )))
		 {
		   throw std::runtime_error("bind");
		 }
		 _len=sizeof(_client_addr);
		 std::cout<<__LINE__<<" "<<ip<<" "<<port<<std::endl;
		}
		const struct sockaddr_in get_client() const
		{
		  return _client_addr;
		}
		int send_message(char *buf, int len)
		{
		 return sendto(_server_fd,buf,len,0,(struct sockaddr*)&_client_addr,sizeof(_client_addr));
		}
		int recv_message(char *buf, int len)
		{
		  std::cout<<"recv..."<<std::endl;
		  return recvfrom(_server_fd,buf, len,0,(struct sockaddr*)&_client_addr,&_len);
		}
		~MySocket()
		{
		close(_server_fd);
		}
};
#endif

