#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "appcryptapi.h"
#include "poolsocket.h"
#include "cfg_op.h"
#define IP "127.0.0.1"
#define PORT 6001

int main(int argc, char const *argv[])
{
	int ret=0;

	int listenfd;
	int connfd;
	unsigned char *out;
	int timeout =3;
	int outlen;

	char *clientid = (char *)malloc(sizeof(char)*10);
	char *serverid = (char *)malloc(sizeof(char)*10);
	int value_len;
	GetCfgItem("./a.bat", "clientid", clientid, &value_len);
	GetCfgItem("./a.bat", "serverid", serverid, &value_len);


	unsigned char *outdata = (unsigned char*)malloc(100*sizeof(unsigned char));
	int outdatalen;
	int cfg_shm_keyid = 0x0001;
	int cfg_shm_maxnodenum =20;

	ret = sckServer_init(PORT, &listenfd);
	if (ret != 0)
	{
		printf("error sckServer_init\n");
		goto End;
	}
	while(1)
	{
		ret = sckServer_accept(listenfd, timeout, &connfd);
		if(ret == Sck_ErrTimeOut)
		{
			printf("no client\n");
			continue;
		}
		else
		{
			break;
		}
	}

	//服务器端端接受报文
	printf("have client\n");
	while(1)
	{
		printf("wait\n");
		ret =  sckServer_rev(connfd, timeout, &out, &outlen); //1
		if (ret == Sck_ErrPeerClosed)
		{
			printf("func sckServer_rev() Sck_ErrPeerClosed:%d \n", ret);
			break;
		}
		else if (ret == Sck_ErrTimeOut)
		{
			printf("func sckServer_rev() Sck_ErrTimeOut:%d \n", ret);
			continue;  //特别小心  服务器端 不能主动的把连接给关闭 break;
		}
		else if (ret != 0)
		{
			printf("func sckServer_rev() err:%d \n", ret);
			break;
		}
		else
		{
			printf("get client data len:%d:\n",outlen);
			break;
		}
	}
	
	ret =  AppCryptApi(1 , clientid, serverid, out, outlen, 
						outdata, &outdatalen, cfg_shm_keyid, cfg_shm_maxnodenum);
	printf("%s\n", outdata );
	if(ret !=0)
	{
		printf("error 1\n");
		return 0;
	}
	ret =  sckServer_close(connfd);
	if (ret != 0)
	{
		printf("error sckServer_close\n");
		goto End;
	}
	//服务器端环境释放 
	ret =  sckServer_destroy();
	if (ret != 0)
	{
		printf("error sckServer_destroy\n");
		goto End;
	}
End:
	return 0;
}