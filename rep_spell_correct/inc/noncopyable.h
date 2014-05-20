/*************************************************************************
	> File Name: noncopyable.h
	> Author: crooked
	> Mail:812665244@qq.com 
	> Created Time: Tue 22 Apr 2014 04:56:55 PM CST
 ************************************************************************/

#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_
/*
 *把拷贝构造函数和赋值运算符设为私有，是为了防止对象的复制
 *把构造函数和析构函数设为protected,是为了防止生存本类的对象
 */ 
class noncopyable
{
   protected:
	   noncopyable(){}
	   ~noncopyable(){}
   private:
	   noncopyable(const noncopyable&);
       noncopyable &operator=(const noncopyable &);
};
#endif
