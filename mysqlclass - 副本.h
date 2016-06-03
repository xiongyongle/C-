/*====================================================================================================
      功能:实现MYSQL数据库类的封装
      时间:2016-5-4
      author:熊永乐
====================================================================================================*/
#ifndef _MYSQL_CLASS_H
#define _MYSQL_CLASS_H      
#include "mylist.h"
#include <mysql.h>
#include <iostream>
#include <string.h>
using namespace std;
class mysqlser
{
public:
	mysqlser();//初始化
	virtual ~mysqlser();//关闭服务器
	bool connect(char* host,char* username,char* password,char* databasename,int portname);//连接服务器
	bool select_db(char* databasename);//选择数据库
  bool create_table(const std::string& sql);//创建表
  bool create_db(string sql);//创建数据库
  bool change_user(const char* user, const char* password, const char* db);//切换用户
  void outerrors();//输出错误信息
  int query(char* sql,mylist<string>& list);//查询
  bool unquery(string sql);//非查询
  void freerecord();//关闭连接
  void output(int col,mylist<string> list);//输出
public:
  int errorNum;//错误编号
  const char* errorInfo;//错误信息
private:
	MYSQL* mysql_user;//句柄
	MYSQL_RES* ret;//结果集
};

#endif


