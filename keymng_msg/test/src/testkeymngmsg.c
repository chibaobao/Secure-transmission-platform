#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "keymng_msg.h"


int mywritefile3(unsigned char *buf, int len)
{
	FILE *fp = NULL;
	fp = fopen("./teacher_to_test.ber", "wb+");
	if (fp == NULL)
	{
		printf("fopen file error \n");
		return -1;
	}
	fwrite(buf, 1, len, fp);
	fclose(fp);
	return 0;
}
//测试Teacher的编解码
int main_Teacher()
{
	Teacher			t1;
	int				ret = 0; //给变量赋值 意思是说: 给变量所代表的内存空间赋值

	unsigned char	*myout = NULL;
	int				outlen = 0;
	Teacher			*outStruct = NULL;
	int				iTeacherType = 0;

	//结构体赋值 
	memset(&t1, 0, sizeof(Teacher));
	t1.age = 32;
	strcpy(t1.name, "myname");
	//strcpy(t1.p, "mynameaaaff");
	t1.p = (char *)malloc(100);
	strncpy(t1.p, "dsafdsafdsafdsafdsa", 9);
	t1.plen = 9;
	t1.p[t1.plen] = '\0';

	ret = MsgEncode(&t1, ID_MsgKey_Teacher, &myout, &outlen);
	if (ret != 0)
	{
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}

	mywritefile3(myout, outlen);

	ret = MsgDecode(myout, outlen, (void**)&outStruct, &iTeacherType);
	if (ret != 0)
	{
		printf("func MsgDecode() err:%d \n", ret);
		return ret;
	}

	//校验
	if (strcmp(t1.p, outStruct->p) == 0 &&
		t1.age == outStruct->age)
	{
		printf("编码 和 解码 结果一致  ok\n");
	}
	else
	{
		printf("编码 和 解码 结果不一致  err\n");
	}

	if (myout)  free(myout);
	//MsgMemFree((void **)&myout, 0);
	MsgMemFree((void **)&outStruct, iTeacherType);

	return 0;
}
//测试MsgKey_Req的编解码
int main()
{
	MsgKey_Req			t1;
	int				ret = 0; //给变量赋值 意思是说: 给变量所代表的内存空间赋值

	unsigned char	*myout = NULL;
	int				outlen = 0;
	MsgKey_Req			*outStruct = NULL;
	int				iTeacherType = 0;

	//结构体赋值 
	memset(&t1, 0, sizeof(MsgKey_Req));
	t1.cmdType = 32;


	strcpy(t1.clientId, "myname");
	strcpy(t1.AuthCode, "myname");
	strcpy(t1.serverId, "myname");
	strcpy(t1.r1, "myname");
	//strcpy(t1.p, "mynameaaaff");


	ret = MsgEncode(&t1, ID_MsgKey_Req, &myout, &outlen);
	if (ret != 0)
	{
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}

	mywritefile3(myout, outlen);

	ret = MsgDecode(myout, outlen, (void**)&outStruct, &iTeacherType);
	if (ret != 0)
	{
		printf("func MsgDecode() err:%d \n", ret);
		return ret;
	}

	//校验
	printf("cmd:%d\n",outStruct->cmdType);
	printf(" clientId :%s\n",outStruct->clientId);
	printf(" AuthCode :%s\n",outStruct->AuthCode);
	printf(" serverId :%s\n",outStruct->serverId);
	printf(" r1:%s\n",outStruct->r1);
	if (strcmp(t1.r1, outStruct->r1) == 0 &&
		t1.cmdType == outStruct->cmdType)
	{
		printf("编码 和 解码 结果一致  ok\n");
	}
	else
	{
		printf("编码 和 解码 结果不一致  err\n");
	}

	if (myout)  free(myout);
	//MsgMemFree((void **)&myout, 0);
	MsgMemFree((void **)&outStruct, iTeacherType);

	return 0;
}
//测试MsgKey_Res的编解码
int main2()
{

	MsgKey_Res			t1;
	int				ret = 0; //给变量赋值 意思是说: 给变量所代表的内存空间赋值

	unsigned char	*myout = NULL;
	int				outlen = 0;
	MsgKey_Res			*outStruct = NULL;
	int				iTeacherType = 0;

	//结构体赋值 
	memset(&t1, 0, sizeof(MsgKey_Res));
	t1.rv = 10;
	strcpy(t1.clientId, "myname1");
	strcpy(t1.serverId, "myname2");
	strcpy((char*)t1.r2, "myname3");
	t1.seckeyid=50;

	ret = MsgEncode(&t1, ID_MsgKey_Res, &myout, &outlen);
	if (ret != 0)
	{
		printf("func MsgEncode() err:%d \n", ret);
		return ret;
	}

	mywritefile3(myout, outlen);
	ret = MsgDecode(myout, outlen, (void**)&outStruct, &iTeacherType);
	if (ret != 0)
	{
		printf("func MsgDecode() err:%d \n", ret);
		return ret;
	}

	printf(" rv:%d\n",outStruct->rv);
	printf(" clientId :%s\n",outStruct->clientId);
	printf(" serverId :%s\n",outStruct->serverId);
	printf(" r2 :%s\n",outStruct->r2);
	printf(" seckeyid:%d\n",outStruct->seckeyid);
	if (strcmp(t1.clientId, outStruct->clientId) == 0 &&
		t1.seckeyid == outStruct->seckeyid)
	{
		printf("编码 和 解码 结果一致  ok\n");
	}
	else
	{
		printf("编码 和 解码 结果不一致  err\n");
	}

	if (myout)  free(myout);
	//MsgMemFree((void **)&myout, 0);
	MsgMemFree((void **)&outStruct, iTeacherType);

	return 0;
}
