#include "staff.h"

#define BL 10
#define CONNECT_NUM 20
#define SQL_CMD 256

sqlite3 *db;

int user_login(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg;
	char **result;
	int nrow,ncolumn;

	sprintf(sql,"select * from info where name=\"%s\" and passwd='%s';",msg->name,msg->passwd);

	sqlite3_get_table(db,sql,&result,&nrow,&ncolumn,&errmsg);
	if(nrow == 0){
		printf("no find\n");
		strcpy(msg->recvmsg,"用户名或密码错误！请重新输入!\n");
		msg->type = -1;
		send(acceptfd,msg,sizeof(MSG),0);
	}else{
		printf("%s\n",result[7]);
		msg->type = atoi(result[7]);
		strcpy(msg->recvmsg,"登录成功!\n");
		send(acceptfd,msg,sizeof(MSG),0);
	}
		return 0;
}

int user_modify(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg;
	sprintf(sql,"update info set passwd='%s' where name='%s';",msg->passwd,msg->name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
	{
		fprintf(stderr,"create failed %s\n",errmsg);
		return -1;
	}
	strcpy(msg->recvmsg,"密码修改成功！\n");
	send(acceptfd,msg,sizeof(MSG),0);
}

int user_query(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg;
	char **result;
	int nrow,ncolumn;

	strcpy(msg->info.name,msg->name);
	strcpy(msg->info.passwd,msg->passwd);

	sprintf(sql,"select * from info where name='%s' and passwd='%s';",msg->info.name,msg->info.passwd);
	if(sqlite3_get_table(db,sql,&result,&nrow,&ncolumn,&errmsg) != 0){
		printf("%s\n",errmsg);
	}
	else{
		sprintf(msg->recvmsg,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t",result[7],result[8],result[9],result[10],result[11],result[12],result[13]);
		printf("%s",msg->recvmsg);
		send(acceptfd,msg,sizeof(MSG),0);
	}

	return 0;
}

int admin_modify(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg;

	switch(msg->flag){
	case 1:
		sprintf(sql,"update info set type=%d where name='%s';",msg->info.type,msg->name);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
		{
			fprintf(stderr,"update failed %s\n",errmsg);
			return -1;
		}
		strcpy(msg->recvmsg,"修改成功！\n");
		send(acceptfd,msg,sizeof(MSG),0);

		break;
	case 2:
		sprintf(sql,"update info set name='%s' where name='%s';",msg->info.name,msg->name);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
		{
			fprintf(stderr,"update failed %s\n",errmsg);
			return -1;
		}
		strcpy(msg->recvmsg,"修改成功！\n");
		send(acceptfd,msg,sizeof(MSG),0);

		break;
	case 3:
		sprintf(sql,"update info set id=%u where name='%s';",msg->info.id,msg->name);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
		{
			fprintf(stderr,"update failed %s\n",errmsg);
			return -1;
		}
		strcpy(msg->recvmsg,"修改成功！\n");
		send(acceptfd,msg,sizeof(MSG),0);

		break;
	case 4:
		sprintf(sql,"update info set passwd='%s' where name='%s';",msg->info.passwd,msg->name);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
		{
			fprintf(stderr,"update failed %s\n",errmsg);
			return -1;
		}
		strcpy(msg->recvmsg,"修改成功！\n");
		send(acceptfd,msg,sizeof(MSG),0);

		break;
	case 5:
		sprintf(sql,"update info set addr='%s' where name='%s';",msg->info.addr,msg->name);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
		{
			fprintf(stderr,"update failed %s\n",errmsg);
			return -1;
		}
		strcpy(msg->recvmsg,"修改成功！\n");
		send(acceptfd,msg,sizeof(MSG),0);

		break;
	case 6:
		sprintf(sql,"update info set phone=%ld where name='%s';",msg->info.phone,msg->name);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
		{
			fprintf(stderr,"update failed %s\n",errmsg);
			return -1;
		}
		strcpy(msg->recvmsg,"修改成功！\n");
		send(acceptfd,msg,sizeof(MSG),0);

		break;
	case 7:
		sprintf(sql,"update info set salary=%f where name='%s';",msg->info.salary,msg->name);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
		{
			fprintf(stderr,"update failed %s\n",errmsg);
			return -1;
		}
		strcpy(msg->recvmsg,"修改成功！\n");
		send(acceptfd,msg,sizeof(MSG),0);

		break;
	}
}

int admin_query(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg;
	char **result;
	int nrow,ncolumn;

	sprintf(sql,"select * from info where name='%s';",msg->name);
	if(sqlite3_get_table(db,sql,&result,&nrow,&ncolumn,&errmsg) != 0){
		printf("%s\n",errmsg);
	}
	else{
		sprintf(msg->recvmsg,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t",result[7],result[8],result[9],result[10],result[11],result[12],result[13]);
		printf("%s",msg->recvmsg);
		send(acceptfd,msg,sizeof(MSG),0);
	}

	return 0;

}

int admin_adduser(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg = NULL;
	
	printf("ok\n");
	sprintf(sql,"insert into info values(%d,%u,'%s','%s','%s',%ld,%f);",\
			msg->info.type,msg->info.id,msg->info.name,msg->info.passwd,msg->info.addr,\
			msg->info.phone,msg->info.salary);
	printf("%s\n",sql);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
	{
		fprintf(stderr,"add user failed %s\n",errmsg);
		exit(-1);
	}
	printf("add user ok\n");

}

int admin_deluser(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg = NULL;
	sprintf(sql,"delete from info where name='%s';",msg->name);
	printf("%s",sql);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != 0)
	{
		fprintf(stderr,"delete user failed %s\n",errmsg);
		exit(-1);
	}
	printf("delete user ok\n");

}

int admin_history(int acceptfd,MSG *msg,sqlite3 *db)
{

}

int admin_all_query(int acceptfd,MSG *msg,sqlite3 *db)
{
	char sql[SQL_CMD] = {0};
	char *errmsg;
	char **result;
	int nrow,ncolumn,i,j,num=0;

	sprintf(sql,"select * from info");
	if(sqlite3_get_table(db,sql,&result,&nrow,&ncolumn,&errmsg) != 0){
		printf("%s\n",errmsg);
	}
	else{
		for(i=0; i<=nrow; i++){
			sprintf(msg->recvmsg,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t",result[i*ncolumn],result[i*ncolumn+1],result[i*ncolumn+2],result[i*ncolumn+3],result[i*ncolumn+4],result[i*ncolumn+5],result[i*ncolumn+6]);
			msg->flag = nrow;
			send(acceptfd,msg,sizeof(MSG),0);
		}
	}
	return 0;
}

int main(int argc, const char *argv[])
{
	//判断命令行输入是否合适
	if(argc < 3){
		printf("Usage:%s IP port\n",argv[0]);
		exit(-1);
	}

	//数据库操作
	sqlite3 *db;
	if(sqlite3_open("staff.db",&db) != 0){
		fprintf(stderr,"sqlite3 open failed %s\n",sqlite3_errmsg(db));
		exit(-1);
	}
	printf("sqlite3 open ok\n");

	char *errmsg = NULL;
#if 0
	if(sqlite3_exec(db,"create table info(type int,id unsigned int primary key,name char,passwd char,addr char,phone unsigned long,salary float);",\
				NULL,NULL,&errmsg) != 0)
	{
		fprintf(stderr,"create table failed %s\n",errmsg);
		exit(-1);
	}
	printf("table create ok\n");

	if(sqlite3_exec(db,"insert into info(type,id,name,passwd) values(1,10001,\"admin\",123456);",\
				NULL,NULL,&errmsg) != 0)
	{
		fprintf(stderr,"insert failed %s\n",errmsg);
		exit(-1);
	}
	printf("insert ok\n");
#endif

	//连接客户端
	int sockfd,acceptfd;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		perror("socket failed:");
		exit(-1);
	}

	int b_reuse = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&b_reuse,sizeof(int));

	struct sockaddr_in serveraddr,clientaddr;

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t addrlen = sizeof(serveraddr);
	socklen_t clientlen = sizeof(clientaddr);

	if(bind(sockfd,(struct sockaddr *)&serveraddr,addrlen) < 0){
		perror("bind failed");
		exit(-1);
	}

	if(listen(sockfd,BL) < 0){
		perror("listen failed");
		exit(-1);
	}

	int epfd, epct, i;
	struct epoll_event event;
	struct epoll_event events[CONNECT_NUM];
	epfd = epoll_create(1);

	event.data.fd = sockfd;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);

	while(1)
	{
		epct = epoll_wait(epfd,events,CONNECT_NUM,-1);
		for(i = 0;i < epct;i++){
			if(events[i].data.fd == sockfd){
				acceptfd = accept(events[i].data.fd,(struct sockaddr *)&clientaddr,&clientlen);
				if(acceptfd < 0){
					perror("accept failed");
					exit(-1);
				}
				printf("accept ok\n");

				event.data.fd = acceptfd;
				event.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd,EPOLL_CTL_ADD,acceptfd,&event);
			}
			else{

				int recvbytes;
				MSG msg;

				memset(&msg,0,sizeof(MSG));
				printf("wait recv\n");
				recvbytes = recv(events[i].data.fd,&msg,sizeof(MSG),0);
				if(recvbytes < 0){
					perror("revc failed");
					exit(-1);
				}
				else if(recvbytes == 0){
					printf("connect disconnected\n");
					close(events[i].data.fd);
					epoll_ctl(epfd,EPOLL_CTL_DEL,events[i].data.fd,&event);
					continue;
				}
				printf("recv ok\n");
				//以下为接收成功情况
				switch(msg.msgtype){
				case USER_LOGIN:
					printf("login\n");
					user_login(events[i].data.fd,&msg,db);
					break;
				case USER_MODIFY:
					user_modify(events[i].data.fd,&msg,db);
					break;
				case USER_QUERY:
					user_query(events[i].data.fd,&msg,db);
					break;
				case ADMIN_MODIFY:
					admin_modify(events[i].data.fd,&msg,db);
					break;
				case ADMIN_QUERY:
					admin_query(events[i].data.fd,&msg,db);
					break;
				case ADMIN_ADDUSER:
					admin_adduser(events[i].data.fd,&msg,db);
					break;
				case ADMIN_DELUSER:
					admin_deluser(events[i].data.fd,&msg,db);
					break;
				case ADMIN_HISTORY:
					admin_history(events[i].data.fd,&msg,db);
					break;
				case ADMIN_ALL_QUERY:
					admin_all_query(events[i].data.fd,&msg,db);
					break;
					//default:

				}
			}
		}
	}

	close(sockfd);
	close(acceptfd);

	return 0;
}
