#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "poolsocket.h"


//指针2大知识领域
//1 指针做函数参数 
//2 函数指针做函数参数  回调函数 
//理解回调理解: 	
//1) 本来是上层man函数调用底层库 ,结果 底层库反过来 调用你写的api函数
//2) 在使用的时候,谁使用 函数指针做函数参数的api函数,谁提供函数的入口地址 
//3) 能实现 任务的编写者 和 任务的调用者  解耦合     
                          
void *mystart_routine(void *arg)
{
	int 		ret = 0;
	int 		timeout = 3;
	int 		connfd = (int)arg;
	
	unsigned char 	*out = NULL;
	int 			outlen = 0;
	
	while (1)
	{	
		//服务器端端接受报文
		ret =  sckServer_rev(connfd, timeout, &out, &outlen); //1
		if (ret == Sck_ErrPeerClosed)
		{
			//printf("aaaaa \n");
			printf("服务器端检测到客户端有一条连接已关闭 \n");
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			printf("服务器端send超时\n");
			continue;
		}
		else if (ret != 0)
		{
			printf("服务器端 sckServer_send() err\n");
			break;
		}
	
		printf("out:%s \n", out);
		
		//服务器端发送报文
		ret =  sckServer_send(connfd, timeout, out, outlen);
		if (ret == Sck_ErrPeerClosed)
		{
			sck_FreeMem((void **)&out);
			printf("服务器端检测到客户端有一条连接已关闭\n");
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			sck_FreeMem((void **)&out);
			printf("服务器端send超时\n");
			continue;
		}
		else if (ret != 0)
		{
			sck_FreeMem((void **)&out);
			printf("服务器端 sckServer_send() err\n");
			break;
		}
		sck_FreeMem((void **)&out);
	}
	
	sckServer_close(connfd);
	return NULL;
}


int main()
{
	int 		ret 		= 0;
	int		 	port 		= 8001;
	int 		listenfd 	= 0;
	int 		timeout		= 3;
	int 		connfd = 0;
	pthread_t 	pid;
	
	
	//函数声明
	//服务器端初始化
	ret = sckServer_init(port, &listenfd);
	if (ret != 0)
	{
		printf("func sckServer_init() err:%d \n", ret);
		return ret;
	}
	
	while (1)
	{
		ret = sckServer_accept(listenfd, timeout, &connfd);
		if (ret ==Sck_ErrTimeOut)
		{
			printf("func sckServer_accept() Sck_ErrTimeOut\n");
			continue;
		}
		else if (ret != 0)
		{
			ret = 2;
			printf("fun sckServer_accept() err :%d \n", ret);
			break;
		}
	
		pthread_create(&pid, NULL,  mystart_routine, (void *)(connfd));

	}


	//服务器端环境释放 
	int sckServer_destroy();
	printf("hello....\n");	
}