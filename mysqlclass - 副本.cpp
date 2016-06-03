/*====================================================================================================
      功能:实现MYSQL数据库类的封装
      时间:2016-5-4
      author:熊永乐
====================================================================================================*/
#include "mysqlclass.h"

/*=======================================================================================
函数功能:构造函数初始化
函数原型:mysql_init(mysql);
=======================================================================================*/
mysqlser::mysqlser():errorNum(0),errorInfo("ok") 
{
  mysql_user =  mysql_init(NULL);//初始化
}

/*=======================================================================================
函数功能:关闭服务器(自动调用)
=======================================================================================*/
mysqlser::~mysqlser()
{
    
}

/*======================================================================================
函数功能:输出错误信息
函数原型:mysql_errno(mysql_user);
返回值类型:void
======================================================================================*/
void mysqlser::outerrors()
{
  errorNum = mysql_errno(mysql_user);
  errorInfo =  mysql_error(mysql_user);
}

/*========================================================================================
函数功能:连接服务器
函数原型:mysql_real_connect(mysql_user,host,username,password,databasename,portname,NULL,0)
返回值类型:bool
=========================================================================================*/
bool mysqlser::connect(char* host,char* username,char* password,char* databasename,int portname)
{
  if(mysql_real_connect(mysql_user,host,username,password,databasename,portname,NULL,0)==NULL)
    {
      outerrors();
      return false;
    }
    else
    {
      return true;
    }
       
}

/*========================================================================================
函数功能:选择数据库
函数原型:mysql_select_db(mysql,const char *db)
函数返回值类型:bool
========================================================================================*/
bool mysqlser::select_db( char* databasename)
{
   int ret=mysql_select_db(mysql_user,databasename);
   if(ret!=0)
   {
     outerrors();
     return false;
   }
   else
   {
     return true; 
   }
}

/*========================================================================================
函数功能:关闭连接
函数原型:mysql_close(MYSQL *mysql)
函数返回值类型:void
========================================================================================*/
void mysqlser::freerecord()
{
  mysql_close(mysql_user);
}

/*========================================================================================
函数功能:实现非查询语句功能
1.插入数据
2.删除数据
3.修改数据
函数原型:mysql_query(mysql,sql);
函数返回值类型:void
========================================================================================*/
bool mysqlser::unquery(string sql)
{
    if (mysql_query(mysql_user,sql.c_str()) != 0 )
    {
      outerrors();
      return false;
    }
    else
    {
      return true;
    }

}

/*========================================================================================
函数功能:创建数据库
函数原型:mysql_query(mysql,sql);
函数返回值类型:bool
========================================================================================*/
bool mysqlser::create_db(string sql)
{
   if(mysql_query(mysql_user,sql.c_str())==0)
   {
      return true;
   }
   else
   {
      outerrors();
      return false;
   }
}

/*========================================================================================
函数功能:创建表
函数原型:mysql_query(mysql,sql);
函数返回值类型:bool
注意:c_str():这是为了与c语言兼容,在c语言中没有string类型,
故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式.
========================================================================================*/
bool mysqlser::create_table(const std::string& sql)  //std::域限制
{
    if(mysql_query(mysql_user, sql.c_str())==0)   
    {
      return true;
    }
    else
    {
      outerrors();
      return false;
    }
}

/*==============================================================================================
函数功能:切换用户
函数原型:mysql_change_user(MYSQL *mysql, const char *user, const char *password, const char *db)
函数返回值:bool
==============================================================================================*/
// bool mysql::change_user(const char *user,const char *password,const char *db)
// {
//   if(mysql_change_user(mysql_user,const char *user,const char *password,const char *db)==0)
//   {
//     return true;
//   }
//   else
//   {
//     outerrors();
//     return false;
//   }
// }

/*=============================================================================================================
函数功能:输出查询语句结果
函数原型:mysql_query(mysql_user,sql),mysql_store_result(mysql_user),mysql_num_fields(ret)
mysql_fetch_fields,mysql_fetch_row(ret),push_back,mysql_fetch_row
函数返回值类型:int
=============================================================================================================*/
int mysqlser::query(char* sql,mylist<string>& list)
{
   if (mysql_query(mysql_user,sql) != 0 )
   {
      outerrors();
      return -1;
   }
   ret = mysql_store_result(mysql_user);
   int col = mysql_num_fields(ret);
   MYSQL_FIELD* field;
   field = mysql_fetch_fields(ret);
   int i;
   for (i = 0; i < col; i++)
   {
     list.push_back(field[i].name);
   }
   MYSQL_ROW row_data;
   row_data = mysql_fetch_row(ret);
   while (row_data != NULL)
   {
      for (i = 0; i < col; i++)
      {
         list.push_back(row_data[i]);
      }
       row_data = mysql_fetch_row(ret);
   }
   return col;
}

/*======================================================================================
函数功能:输出结果
函数原型:output(int col,mylist<string> list)
函数返回值类型:void 
======================================================================================*/
void mysqlser::output(int col,mylist<string> list)
{
  int i = 0;
  mylist<string>::iterator it;
  for (it = list.begin();it != list.end();it++)
  {
    cout<<*it;
    i++;
    if (i == col)
    {
       i = 0;
       cout<<endl;
    }
  }
}








