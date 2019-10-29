#include "staff.h"

time_t tm_now;
struct tm *time_s;

void login(int sockfd);

int user_modify(int sockfd,MSG *msg)
{
	msg->msgtype = USER_MODIFY;
	char temp[N] = {0};
	char temp1[N] = {0};

	printf("新密码：");
	scanf("%s",temp);
	getchar();
	printf("确认新密码：");
	scanf("%s",temp1);
	getchar();

	if(strcmp(temp,temp1) == 0){
		strcpy(msg->passwd,temp1);
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
	}else{
		printf("输入密码不一致，请重新输入！\n");
	}
}

int user_query(int sockfd,MSG *msg)
{
	msg->msgtype = USER_QUERY;
	send(sockfd,msg,sizeof(MSG),0);
	recv(sockfd,msg,sizeof(MSG),0);
	printf("type\tid\tname\tpasswd\taddr\tphone\tsalary\n");
	printf("%s\n",msg->recvmsg);
}

int admin_modify(int sockfd,MSG *msg)
{
	int opt;
	msg->msgtype = ADMIN_MODIFY;
	//printf("info:%s  ** %s",msg->info.name,msg->name);
	printf("请输入需要修改信息的员工姓名：");
	scanf("%s",msg->info.name);
	getchar();

	printf("**********1.权限************\n");
	printf("***2.姓名***3.id***4.密码***\n");
	printf("***5.地址**6.电话**7.工资****\n");

	printf("请输入需要修改的选项:");
	scanf("%d",&opt);
	getchar();

	switch(opt){
	case 1:
		printf("权限修改为(1.管理员 2.普通员工)：");
		scanf("%d",&msg->info.type);
		getchar();

		tm_now = time(NULL);
		time_s = localtime(&tm_now);
		sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 将 %s 的权限修改为 %d (1.管理员 0.普通员工)",\
				msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
				msg->info.name,msg->info.type);

		msg->flag = 1;
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		break;
	case 2:
		printf("姓名修改为：");
		scanf("%s",msg->change_name);
		getchar();

		tm_now = time(NULL);
		time_s = localtime(&tm_now);
		sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 将 %s 的姓名修改为 %s",\
				msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
				msg->info.name,msg->change_name);

		msg->flag = 2;
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		break;
	case 3:
		printf("id修改为：");
		scanf("%u",&msg->info.id);
		getchar();

		tm_now = time(NULL);
		time_s = localtime(&tm_now);
		sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 将 %s 的id修改为 %u (id不可重复)",\
				msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
				msg->info.name,msg->info.id);

		msg->flag = 3;
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		break;
	case 4:
		printf("密码修改为：");
		scanf("%s",msg->info.passwd);
		getchar();

		tm_now = time(NULL);
		time_s = localtime(&tm_now);
		sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 将 %s 的密码修改为 %s",\
				msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
				msg->info.name,msg->info.passwd);

		msg->flag = 4;
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		break;
	case 5:
		printf("地址修改为：");
		scanf("%s",msg->info.addr);
		getchar();

		tm_now = time(NULL);
		time_s = localtime(&tm_now);
		sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 将 %s 的地址修改为 %s",\
				msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
				msg->info.name,msg->info.addr);

		msg->flag = 5;
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		break;
	case 6:
		printf("电话修改为：");
		scanf("%ld",&msg->info.phone);
		getchar();

		tm_now = time(NULL);
		time_s = localtime(&tm_now);
		sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 将 %s 的电话修改为 %ld",\
				msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
				msg->info.name,msg->info.phone);

		msg->flag = 6;
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		break;
	case 7:
		printf("工资修改为：");
		scanf("%f",&msg->info.salary);
		getchar();

		tm_now = time(NULL);
		time_s = localtime(&tm_now);
		sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 将 %s 的工资修改为 %f",\
				msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
				msg->info.name,msg->info.salary);

		msg->flag = 7;
		send(sockfd,msg,sizeof(MSG),0);
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		break;
	}

}

int admin_query(int sockfd,MSG *msg)
{
	msg->msgtype = ADMIN_QUERY;
	printf("请输入需要查询的员工姓名：");
	scanf("%s",msg->info.name);
	getchar();

	tm_now = time(NULL);
	time_s = localtime(&tm_now);
	sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 查询了 %s 的信息",\
			msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
			msg->info.name);

	send(sockfd,msg,sizeof(MSG),0);
	recv(sockfd,msg,sizeof(MSG),0);
	printf("%s\n",msg->recvmsg);
}

int admin_adduser(int sockfd,MSG *msg)
{
	printf("姓名：");
	scanf("%s",msg->info.name);
	getchar();
	printf("密码：");
	scanf("%s",msg->info.passwd);
	getchar();
	printf("id：");
	scanf("%d",&msg->info.id);
	getchar();
	printf("地址：");
	scanf("%s",msg->info.addr);
	getchar();
	printf("电话：");
	scanf("%ld",&msg->info.phone);
	getchar();
	printf("工资：");
	scanf("%f",&msg->info.salary);
	getchar();
	printf("是否设置为管理员（1.是  0.否）：");
	scanf("%d",&msg->info.type);
	getchar();

	tm_now = time(NULL);
	time_s = localtime(&tm_now);
	sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 添加了名为 %s 的员工",\
			msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
			msg->info.name);

	msg->msgtype = ADMIN_ADDUSER;
	send(sockfd,msg,sizeof(MSG),0);
	recv(sockfd,msg,sizeof(MSG),0);
	printf("%s\n",msg->recvmsg);
	return 0;
}

int admin_deluser(int sockfd,MSG *msg)
{
	msg->msgtype = ADMIN_DELUSER;
	printf("输入要删除的用户姓名：");
	scanf("%s",msg->info.name);
	
	tm_now = time(NULL);
	time_s = localtime(&tm_now);
	sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 删除了名为 %s 的员工",\
			msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec,\
			msg->info.name);

	send(sockfd,msg,sizeof(MSG),0);
	recv(sockfd,msg,sizeof(MSG),0);
	printf("%s\n",msg->recvmsg);
	return 0;
}

int admin_history(int sockfd,MSG *msg)
{
	int i;
	msg->msgtype = ADMIN_HISTORY;
	
	tm_now = time(NULL);
	time_s = localtime(&tm_now);
	sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 查询了历史记录",\
			msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec);

	printf("&&&&&&&&&&&&&&&&&&&&&&历史记录&&&&&&&&&&&&&&&&&&&&\n");
	send(sockfd,msg,sizeof(MSG),0);
	msg->flag = 0;

	for(i=0; i<=msg->flag; i++){
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		msg->flag;
	}
}

int admin_all_query(int sockfd,MSG *msg)
{
	int i;
	msg->msgtype = ADMIN_ALL_QUERY;
	
	tm_now = time(NULL);
	time_s = localtime(&tm_now);
	sprintf(msg->recvmsg,"管理员 %s 在 %d/%d/%d %d:%d:%d 查看了所有员工信息",\
			msg->name,time_s->tm_year+1900,time_s->tm_mon+1,time_s->tm_mday,time_s->tm_hour,time_s->tm_min,time_s->tm_sec);

	send(sockfd,msg,sizeof(MSG),0);
	msg->flag = 0;
	for(i=0; i<=msg->flag; i++){
		recv(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",msg->recvmsg);
		msg->flag;
	}
}


#if 1
//普通员工登录
void user_login(int sockfd,MSG *msg)
{
	printf("\n");
	printf("亲爱的用户您好，欢迎登录员工管理系统！\n");

	int opt;

	while(1){
		printf("\n");
		printf("************************************\n");
		printf("*******1.查询信息**2.修改密码*******\n");
		printf("***********3.返回**4.退出***********\n");
		printf("************************************\n");
		printf("\n");

		printf("请选择>>");
		scanf("%d",&opt);
		getchar();

		switch (opt) {
		case 1:
			user_query(sockfd,msg);
			break;
		case 2:
			user_modify(sockfd,msg);
			break;
		case 3:
			login(sockfd);
		case 4:
			exit(0);
		default:
			printf("输入有误！\n");
		}
	}
}

//管理员登录
void admin_login(int sockfd,MSG *msg)
{
	printf("\n");
	printf("************亲爱的管理员，欢迎登录员工管理系统**************\n");
	while(1){
		printf("\n");
		printf("# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # \n");
		printf("# **1.添加员工**2.删除员工**3.修改员工信息**4.查询员工信息** #\n");
		printf("# ***5.查看所有员工信息***6.查看历史记录**7.返回***8.退出*** #\n");
		printf("# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # \n");

		int opt;
		printf("请选择>>");
		scanf("%d",&opt);
		getchar();

		switch (opt) {
		case 1:
			admin_adduser(sockfd,msg);
			break;
		case 2:
			admin_deluser(sockfd,msg);
			break;
		case 3:
			admin_modify(sockfd,msg);
			break;
		case 4:
			admin_query(sockfd,msg);
			break;
		case 5:
			admin_all_query(sockfd,msg);
			break;
		case 6:
			admin_history(sockfd,msg);
			break;
		case 7:
			login(sockfd);
		case 8:
			exit(0);
			break;
		default:
			printf("输入有误，请重新输入！\n");
		}
	}
}
#endif

void login(int sockfd)
{
	int opt;
	MSG msg;

	while(1){
		printf("\n");
		printf("**********************************\n");
		printf("*********员工信息管理系统*********\n");
		printf("*******1.登录********2.退出*******\n");
		printf("**********************************\n");

		printf("请输入你的选择>>");
		scanf("%d",&opt);
		getchar();

		if(opt > 2 || opt < 1){
			printf("input error,please input again!\n");
			//continue;
		}
		else if(opt == 1){
			msg.msgtype = USER_LOGIN;

			printf("name >> ");
			scanf("%s",msg.name);
			getchar();

			printf("passwd >> ");
			scanf("%s",msg.passwd);
			getchar();

			send(sockfd,&msg,sizeof(msg),0);
			recv(sockfd,&msg,sizeof(MSG),0);
			printf("%s",msg.recvmsg);

			if(msg.type == USER){
				user_login(sockfd,&msg);
			}else if(msg.type == ADMIN){
				admin_login(sockfd,&msg);
			}
		}else{
			close(sockfd);
			exit(0);
		}
	}
}

int main(int argc, const char *argv[])
{
	if(argc < 3){
		printf("Usage:%s IP port\n",argv[0]);
		exit(-1);
	}

	int sockfd;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		perror("socket failed:");
		exit(-1);
	}

	struct sockaddr_in serveraddr;
	socklen_t addrlen = sizeof(serveraddr);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sockfd,(struct sockaddr *)&serveraddr,addrlen) < 0){
		perror("connect failed");
		exit(-1);
	}

	login(sockfd);

	close(sockfd);

	return 0;
}

