#ifndef __STAFF_H__
#define __STAFF_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <linux/in.h>  //sockaddr_in
#include <stdlib.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>

#define N 32
#define MSG_NUM 128

#define USER_LOGIN     1 	//登录
#define USER_MODIFY    2 	//普通用户修改信息
#define USER_QUERY     3 	//普通用户查询信息

#define ADMIN_MODIFY   4 	//管理员修改信息
#define ADMIN_QUERY    5 	//管理员查询信息
#define ADMIN_ADDUSER  6 	//管理员添加用户
#define ADMIN_DELUSER  7 	//管理员删除用户
#define ADMIN_HISTORY  8 	//历史记录查询
#define ADMIN_ALL_QUERY    9 	//管理员查看所有员工信息

#define QUIT           0 	//退出

#define USER  0
#define ADMIN 1


typedef struct{
	int  type; 				//权限标志位
	unsigned int id;  		//编号
	char  name[N];  		//姓名
	char  passwd[N]; 		//密码
	char  addr[N]; 			//地址
	unsigned long   phone; 	//电话
	float salary; 			//工资
}info_t;

typedef struct{
	int msgtype; 			//消息类型
	int type; 				//用户权限
	char name[N]; 			//姓名
	char passwd[N]; 		//密码
	char recvmsg[MSG_NUM]; 	//通信的消息
	info_t info; 	  		//员工信息
	int flag; 				//修改员工信息标志位
	char change_name[N]; 	//修改后的员工姓名
}MSG;




#endif
