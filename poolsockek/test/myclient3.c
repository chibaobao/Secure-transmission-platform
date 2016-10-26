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

typedef struct _ThreadInfo
{
	int 				iThreadIndex;
	int 				iLoop;
	void 				*handle;
}ThreadInfo;


void *myclient_start_routine(void *arg)
{
	
	ThreadInfo		*tmpThread = NULL;
	int 			i = 0, ret = 0;
	int 			connfd = 0;
	void 			*handle = NULL;
	
	unsigned char 	*out = NULL;
	int 			outlen = 0;
	
	
	tmpThread = (ThreadInfo *)arg;
	handle = tmpThread->handle;
	//printf("11111111111111 \n");
	
	//客户端 socket池 获取一条连接 
	ret = sckCltPool_getConnet(handle, &connfd);
	if (ret != 0)
	{
		printf("func sckCltPool_getConnet() err:%d \n", ret);
		return NULL;
	}
	
	//printf("22222222222222 \n");
	for (i=0; i<tmpThread->iLoop; i++)
	{
		char mybuf[64] = {0};
		
		sprintf(mybuf, "第%d个线程 第%d圈", tmpThread->iThreadIndex+1, i);
		
		//客户端 socket池 发送数据 
		ret = sckCltPool_send(handle, connfd, (unsigned char *)mybuf, strlen(mybuf));
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
		
		//printf("3333333333333333333 \n");
	
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
		//printf("444444444444444444 \n");

	}

//printf("555555555555555 \n");
	if (ret == 0)
	{
		//客户端 socket池 把连接放回 socket池中 
		sckCltPool_putConnet(handle, connfd, 0); //0正常 1
	}
	else
	{
		sckCltPool_putConnet(handle, connfd, 1); //0正常 1
	}
	

//printf("66666666666666666666 \n");
	return NULL;	
}



int main()
{
	int 					ret = 0, i = 0;
	SCKClitPoolParam  		sckClitPoolParam;
	void 					*handle = NULL;
	pthread_t				pidArray[1024];  
	
	int 					iThreadNum = 0;
	int 					iLoop = 0;
	ThreadInfo				*threadInfo;
	
	memset(&sckClitPoolParam, 0 ,sizeof(SCKClitPoolParam));
	
	printf("\n请输入启动的线程个数:");
	scanf("%d", &iThreadNum);
	
	printf("\n请输入每个线程运行的圈数:");
	scanf("%d", &iLoop);
	
	strcpy(sckClitPoolParam.serverip, "127.0.0.1");
	sckClitPoolParam.serverport = 8001;
	sckClitPoolParam.bounds = 20;
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
	
	threadInfo = (ThreadInfo*)malloc(sizeof(ThreadInfo)*iThreadNum);	 		
	for (i=0; i<iThreadNum; i++)
	{
		threadInfo[i].iLoop = iLoop;
		threadInfo[i].iThreadIndex = i;
		threadInfo[i].handle = handle;
		//开业务线程
		pthread_create(&pidArray[i], NULL, myclient_start_routine,  (void *) &threadInfo[i]);
	}
	//等待所有的线程 都结束了 才能向下运行
	for (i=0; i<iThreadNum; i++)
	{
		//开业务线程
		 pthread_join(pidArray[i], NULL);
	}
	free(threadInfo);
	threadInfo =NULL;
     	
	//客户端 socket池 销毁连接
	sckCltPool_destroy(handle);

	

	printf("hello ...client\n");
	return 0;
}
