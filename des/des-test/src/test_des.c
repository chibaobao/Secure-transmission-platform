#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "appcryptapi.h"
int main()
{
	int ret=0; 

	char *clientid = "1111";
	char *serverid = "0001";
	unsigned char *indata = "hello world";
	int indatalen = strlen((char*)indata);
	unsigned char *outdata = (unsigned char*)malloc(100*sizeof(unsigned char));
	unsigned char *outdata2 = (unsigned char*)malloc(100*sizeof(unsigned char));
	int outdatalen;
	int outdatalen2;

	int cfg_shm_keyid = 0x0001;
	int cfg_shm_keyid2 = 0x1111;

	int cfg_shm_maxnodenum =20;
	int cfg_shm_maxnodenum2 =1;
	printf("%s\n", indata);
	ret =  AppCryptApi(0 , clientid, serverid, indata, indatalen, 
						outdata, &outdatalen, cfg_shm_keyid, cfg_shm_maxnodenum);
	if(ret !=0)
	{
		printf("error 1\n");
		return 0;
	}
	ret =  AppCryptApi(1 , clientid, serverid, outdata, outdatalen, 
						outdata2, &outdatalen2, cfg_shm_keyid2, cfg_shm_maxnodenum2);
	if(ret !=0)
	{
		printf("error 1\n");
		return 0;
	}
	printf("%s\n", outdata2);
	return 0;
}
