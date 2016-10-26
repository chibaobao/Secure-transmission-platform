#include <unistd.h>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "poolsocket.h"


void *myclient_start_routine(void *arg)
{
	
	int 			i = 0, ret = 0;
	int 			connfd = 0;
	void 			*handle  = (void *)arg;
	
	unsigned char 	*out = NULL;
	int 			outlen = 0;

	
	//客户端 socket池 获取一条连接 
	ret = sckCltPool_getConnet(handle, &connfd);
	if (ret != 0)
	{
		printf("func sckCltPool_getConnet() err:%d \n", ret);
		return NULL;
	}
	
	for (i=0; i<20; i++)
	{
		unsigned char *out = NULL;
		int outlen = 0;
	
		//客户端 socket池 发送数据 
		ret = sckCltPool_send(handle, connfd,  "aaaaaaaffffffffffffffdddddd", 6);
		if (ret == Sck_ErrPeerClosed)
		{
			break;
		}
		else if (ret ==Sck_ErrTimeOut)
		{
			break;
		}
		else if (ret == 0)
		{
			;	
		}
		else
		{
			;
		}
		
	
		//客户端 socket池 接受数据
		ret = sckCltPool_rev(handle, connfd, &out, &outlen); //1
		if (ret == Sck_ErrPeerClosed)
		{
			break;
		}
		else if (ret ==Sck_ErrTimeOut)
		{
			break;
		}
		else if (ret == 0)
		{
			;	
		}
		else
		{
			;
		}
		
		printf("out:%s \n", out);
		
		//释放内存
		sck_FreeMem((void **) &out);

	}

	if (ret == 0)
	{
		//客户端 socket池 把连接放回 socket池中 
		sckCltPool_putConnet(handle, connfd, 0); //0正常 1
	}
	else
	{
		sckCltPool_putConnet(handle, connfd, 1); //0正常 1
	}
	

	return NULL;	
}

int main()
{
	int 					ret = 0, i = 0;
	SCKClitPoolParam  		sckClitPoolParam;
	void 					*handle = NULL;
	pthread_t				pidArray[1024];  
		
	memset(&sckClitPoolParam, 0 ,sizeof(SCKClitPoolParam));
	
	strcpy(sckClitPoolParam.serverip, "127.0.0.1");
	sckClitPoolParam.serverport = 8001;
	sckClitPoolParam.bounds = 10;
	sckClitPoolParam.connecttime = 3;
	sckClitPoolParam.sendtime = 3;
	sckClitPoolParam.revtime = 3;
	
	
	//客户端 socket池初始化
	ret = sckCltPool_init(&handle, &sckClitPoolParam);
	if (ret != 0)
	{
		printf("func sckCltPool_init() err:%d \n", ret);
		return ret;
	}
	
	for (i=0; i<10; i++)
	{
		//开业务线程
		pthread_create(&pidArray[i], NULL, myclient_start_routine,  (void *)handle);
	}
	
	//等待所有的线程 都结束了 才能向下运行
	for (i=0; i<10; i++)
	{
		//开业务线程
		 pthread_join(pidArray[i], NULL);
	}
     	
	//客户端 socket池 销毁连接
	sckCltPool_destroy(handle);

	

	printf("hello ...client\n");
	return 0;
}
