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


int main()
{
	int 	ret = 0;
	char 	*ip = "127.0.0.1";
	int 	port = 8001;
	int 	mytime = 3;
	int 	connfd = 0;
	
	 unsigned char *data = "abcdefgafdsafdsafdsfdsafd";
	 int 			datalen = 8;
	 
	  unsigned char *myout  = NULL;
	 int 			myoutlen;
	
	//客户端 初始化
	ret = sckClient_init();
	if (ret != 0)
	{
		printf("func sckClient_init() err:%d \n",ret);
		return ret;
	}
	
	ret = sckClient_connect(ip, port, mytime, &connfd);
	if (ret != 0)
	{
		printf("func sckClient_connect() err:%d \n",ret);
		return ret;
	}

	//发送报文
	ret = sckClient_send(connfd, mytime, data, datalen);
	if (ret != 0)
	{
		printf("func sckClient_connect() err:%d \n",ret);
		return ret;
	}
	

	ret = sckClient_rev(connfd,  mytime, &myout, &myoutlen); //1
	if (ret != 0)
	{
		printf("func sckClient_rev() err:%d \n",ret);
		return ret;
	}
	
	printf("myout:%s \n", myout);
	
	ret = sck_FreeMem((void **)&myout);

	ret = sckClient_closeconn(connfd);
	
	ret = sckClient_destroy();

	printf("hello ...client\n");
	return 0;
}