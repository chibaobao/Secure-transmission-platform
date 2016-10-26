#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "poolsocket.h"

#define IP "127.0.0.1"
#define PORT 6001

int main(int argc, char const *argv[])
{
	int 				ret =0;
	int 				mytime = 3;
	
	unsigned char		*sendData = "hello world\n";
	int					sendLen = strlen(sendData); 
	
	int 				connfd = 0;


	char *clientid = (char *)malloc(sizeof(char)*10);
	char *serverid = (char *)malloc(sizeof(char)*10);
	int value_len;
	GetCfgItem("./a.bat", "clientid", clientid, &value_len);
	GetCfgItem("./a.bat", "serverid", serverid, &value_len);
	unsigned char *outdata = (unsigned char*)malloc(100*sizeof(unsigned char));
	int outdatalen;

	int cfg_shm_keyid = 0x1111;

	int cfg_shm_maxnodenum =1;
	printf("send:%s\n", sendData);
	//加密
	ret =  AppCryptApi(0 , clientid, serverid, sendData, sendLen, 
						outdata, &outdatalen, cfg_shm_keyid, cfg_shm_maxnodenum);
	if(ret !=0)
	{
		printf("error 1\n");
		return 0;
	}
	//3 发送请求报文
	//客户端 初始化
	ret = sckClient_init();
	if (ret != 0)
	{
		printf("error sckClient_init\n");
		goto End;
	}

	//客户端 连接服务器 char	
	ret = sckClient_connect(IP, PORT, mytime, &connfd);
	if (ret != 0)
	{
		printf("error sckClient_connect\n");
		goto End;
	}
	
	//客户端 发送报文
	printf("加密后：%s\n",outdata);
	ret = sckClient_send(connfd, mytime, outdata, outdatalen);
	if (ret != 0)
	{
		printf("error sckClient_send\n");
		goto End;
	}
	


End:	
	
	//客户端 关闭和服务端的连接
	sckClient_closeconn(connfd);
	
	//客户端 释放
	sckClient_destroy();
	printf("send  end\n");
	return ret;	
}

