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

 void *mystart_routine (void *arg)
 {
 	int 			ret = 0;
 	int 			timeout = 3;
 	int 			connfd = 0;
 
 	unsigned char 	*out = NULL;
 	int 			outlen = 0;
 	
 	connfd = (int)arg;
 	
 	while (1)
 	{
 		out = NULL;
 		outlen = 0;
	 	//服务器端端接受报文
		ret = sckServer_rev(connfd, timeout, &out, &outlen); //1
		if (ret == Sck_ErrPeerClosed)
		{
			printf("func sckServer_rev() Sck_ErrPeerClosed:%d \n", ret);
			break;
		}
		else if (ret == 0)
		{
			;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			printf("func sckServer_rev() Sck_ErrTimeOut:%d \n", ret);
			break;
		}
		else
		{
			printf("func sckServer_rev() err:%d \n", ret);
			break;
		}
		
		//
		printf("out:%s\n", out);
		
		//服务器端发送报文
		sckServer_send(connfd, timeout, out, outlen);
		if (ret == Sck_ErrPeerClosed)
		{
			sck_FreeMem((void **)&out);
			printf("func sckServer_send() Sck_ErrPeerClosed:%d \n", ret);
			break;
		}
		else if (ret == 0)
		{
			;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			sck_FreeMem((void **)&out);
			printf("func sckServer_send() Sck_ErrTimeOut:%d \n", ret);
			break;
		}
		else
		{
			sck_FreeMem((void **)&out);
			printf("func sckServer_send() err:%d \n", ret);
			break;
		}	
		
		sck_FreeMem((void **)&out);
 	}

	sckServer_close(connfd);
	
 	return NULL;
 }

//怎么样理解回调函数
//角度1 : 谁调用这样的api函数(函数指针做函数参数) 谁提供函数入口地址
//角度2 : 任务的调用者  和  任务的编写者 进行解耦合
//角度3: 

int main()
{
	int 			port = 8001, ret = 0;
	int 			listenfd = 0;
	int 			timeout = 3;
	int 			connfd = 0;
	
	pthread_t		pid;  
			
	//服务器端初始化
	ret =  sckServer_init(port, &listenfd);
	if (ret != 0)
	{
		printf("func sckServer_init() err:%d \n ", ret);
		return ret;
	}
	
	while (1)
	{
		ret = sckServer_accept(listenfd, timeout, &connfd);
		if (ret==Sck_ErrTimeOut)
		{
			printf("linux内核中没有已完成的连接\n");
			continue;
		}
		
		//开业务线程
		pthread_create(&pid, NULL, mystart_routine,  (void *)connfd);
		
	}

	//服务器端环境释放 
	sckServer_destroy();

	return 0;
}