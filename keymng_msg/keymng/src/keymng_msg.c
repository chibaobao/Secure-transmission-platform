
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "itcast_asn1_der.h"
#include "itcastderlog.h"
#include "keymng_msg.h"




#if 0
 编解码Teacher函数，Teacher只是一个测试用的结构体
//编码Teacher //形参也是一种参数 
int TeacherEncode_(Teacher *pStruct /*in*/, ITCAST_ANYBUF **outNode)
{
	int			ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF		*pTmpBuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	unsigned char		*tmpout = NULL;
	int					tmpoutlen = 0;

	//C语言的buf 转成 ITCAST_ANYBUF类型
	//pStruct->name 

	pTmp = malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		return 1;
	}
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));
	pTmp->pData = (unsigned char *)malloc(strlen(pStruct->name));
	if (pTmp->pData == NULL)
	{
		return 2;
	}
	memcpy(pTmp->pData, pStruct->name, strlen(pStruct->name));
	pTmp->dataLen = strlen(pStruct->name); //


	//编码name 
	ret = DER_ItAsn1_WritePrintableString(pTmp, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		printf("func DER_ItAsn1_WritePrintableString() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);

	pTmp = pHeadBuf; //


	//编码age
	ret = DER_ItAsn1_WriteInteger(pStruct->age, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //pTmp指向新的结点

	//编码p
	ret = EncodeChar(pStruct->p, pStruct->plen, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func EncodeChar() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //pTmp指向新的结点

	//编码plen
	ret = DER_ItAsn1_WriteInteger(pStruct->plen, &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}


	//编码总的结构体
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pHeadBuf);

	//间接赋值
	*outNode = pOutData;
	return ret;
}

//解码 teacher
int TeacherDecode_(unsigned char *in, int inLen, Teacher **pStruct)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF		*pTmpDABuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	ITCAST_ANYBUF		*inAnyBuf = NULL;
	int					tmpNum = 0;
	Teacher				*pTmpStru = NULL;

	//把buf 转成成 ITCAST_ANYBUF
	pTmp = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = 4;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));
	pTmp->pData = (unsigned char *)malloc(inLen);
	if (pTmp->pData == NULL) //20161015 modified by bombing
	{
		printf("func malloc() err:%d \n", ret);
		return 5;
	}
	memcpy(pTmp->pData, in, inLen);
	pTmp->dataLen = inLen;

	//解码大结构
	ret = DER_ItAsn1_ReadSequence(pTmp, &pHead);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);
	pTmp = pHead;

	//先分配大的结构体
	pTmpStru = (Teacher *)malloc(sizeof(Teacher));
	if (pTmpStru == NULL)
	{
		ret = 6;
		DER_ITCAST_FreeQueue(pHead);
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru, 0, sizeof(Teacher));

	//解码 name
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->name, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);

	//解码age
	ret = DER_ItAsn1_ReadInteger(pTmp,(ITCAST_UINT32 *)&(pTmpStru->age));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //指针指向下一个结点

	//解码p
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	pTmpStru->p = (unsigned char *)malloc(pTmpDABuf->dataLen + 1);
	if (pTmpStru->p == NULL)
	{
		ret = 7;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->p, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmpStru->p[pTmpDABuf->dataLen] = '\0'; //变成C风格的字符串
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);

	//解码plen
	ret = DER_ItAsn1_ReadInteger(pTmp, (ITCAST_UINT32 *)&(pTmpStru->plen));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}

	*pStruct = pTmpStru;

	DER_ITCAST_FreeQueue(pHead);

	return ret;

}


//既要释放内存 同时也要避免野指针
int TeacherFree2_(Teacher **pStruct)
{
	Teacher *tmp = NULL;
	if (pStruct == NULL)
	{
		return 0;
	}
	tmp = *pStruct;

	if (tmp->p != NULL)  free(tmp->p);
	free(tmp);			//bug
	*pStruct = NULL;
	return 0;
}

#endif


int ReqEncode_(MsgKey_Req *pStruct /*in*/, ITCAST_ANYBUF **outNode)
{
	int			ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHeadBuf = NULL;
	ITCAST_ANYBUF		*pTmpBuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	unsigned char		*tmpout = NULL;
	int					tmpoutlen = 0;


	//cmdType
	ret = DER_ItAsn1_WriteInteger(pStruct->cmdType,&pHeadBuf);
	pTmp = pHeadBuf; //



	//编码clientId
	ret = EncodeChar(pStruct->clientId, strlen(pStruct->clientId), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //pTmp指向新的结点

	//编码AuthCode
	ret = EncodeChar(pStruct->AuthCode, sizeof(pStruct->AuthCode), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //pTmp指向新的结点

	//编码serverId
	ret = EncodeChar(pStruct->serverId, sizeof(pStruct->serverId), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //pTmp指向新的结点

	//编码
	ret = EncodeChar(pStruct->r1, sizeof(pStruct->r1), &(pTmp->next));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}

	//编码总的结构体
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}
	ret = DER_ITCAST_FreeQueue(pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}

	//间接赋值
	*outNode = pOutData;

	return ret;
}
int ReqDecode_(unsigned char *in, int inLen, MsgKey_Req **pStruct)
{
	int					ret = 0;
	ITCAST_ANYBUF		*pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF		*pTmpDABuf = NULL;
	ITCAST_ANYBUF		*pOutData = NULL;
	ITCAST_ANYBUF		*inAnyBuf = NULL;
	int					tmpNum = 0;
	MsgKey_Req			*pTmpStru = NULL;

	//把buf 转成成 ITCAST_ANYBUF
	pTmp = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = 4;
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));
	pTmp->pData = (unsigned char *)malloc(inLen);
	if (pTmp->pData == NULL) //20161015 modified by bombing
	{
		printf("func malloc() err:%d \n", ret);
		return 5;
	}
	memcpy(pTmp->pData, in, inLen);
	pTmp->dataLen = inLen;

	//解码大结构
	ret = DER_ItAsn1_ReadSequence(pTmp, &pHead);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);
	pTmp = pHead;

	//先分配大的结构体
	pTmpStru = (MsgKey_Req *)malloc(sizeof(MsgKey_Req));
	if (pTmpStru == NULL)
	{
		ret = 6;
		DER_ITCAST_FreeQueue(pHead);
		printf("func malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmpStru, 0, sizeof(MsgKey_Req));
	//解码cmd
	ret = DER_ItAsn1_ReadInteger(pTmp,(unsigned long *) &(pTmpStru->cmdType));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHead);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}
	pTmp = pTmp->next; //指针指向下一个结点

	//解码 clientId
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->clientId, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);

	//解码 AuthCode
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->AuthCode, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);

	//解码 serverId
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->serverId, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);


	//解码 r1
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_ReadPrintableString() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmpStru->r1, pTmpDABuf->pData, pTmpDABuf->dataLen);
	pTmp = pTmp->next;
	DER_ITCAST_FreeQueue(pTmpDABuf);

	

	*pStruct = pTmpStru;

	DER_ITCAST_FreeQueue(pHead);

	return ret;
}
int ReqFree2_(MsgKey_Req **pStruct)
{
	MsgKey_Req *tmp = NULL;
	if (pStruct == NULL)
	{
		return 0;
	}
	tmp = *pStruct;
	if(tmp!=NULL)
		free(tmp);			//bug
	*pStruct = NULL;
	return 0;
}

int RecEncode_(MsgKey_Res *pStruct /*in*/, ITCAST_ANYBUF **outNode)
{
	ITCAST_ANYBUF *head=NULL,*tmp=NULL;
	int ret=0;
	//编码rv
	ret = DER_ItAsn1_WriteInteger(pStruct->rv,&head);
	if(ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("keymng_msg RecEncode_ write error:%d\n",ret);
		return ret;
	}
	tmp = head;
	//编码clientId
	ret = EncodeChar(pStruct->clientId, sizeof(pStruct->clientId), &(tmp->next));
	if(ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("keymng_msg RecEncode_ write error:%d\n",ret);
		return ret;
	}
	tmp=tmp->next;
	//编码serverId
	ret = EncodeChar(pStruct->serverId, sizeof(pStruct->serverId), &(tmp->next));
	if(ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("keymng_msg RecEncode_ write error:%d\n",ret);
		return ret;
	}
	tmp=tmp->next;
	//编码r2
	ret = EncodeUnsignedChar(pStruct->r2, sizeof(pStruct->r2), &(tmp->next));
	if(ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("keymng_msg RecEncode_ write error:%d\n",ret);
		return ret;
	}
	tmp=tmp->next;
	//编码seckeyid
	ret = DER_ItAsn1_WriteInteger(pStruct->seckeyid,&(tmp->next));
	if(ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("keymng_msg RecEncode_ write error:%d\n",ret);
		return ret;
	}
	tmp = NULL;

	//编码成大结构体
	ret = DER_ItAsn1_WriteSequence(head,&tmp);
	if(ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("keymng_msg DER_ItAsn1_WriteSequence error:%d\n",ret);
		return ret;
	}
	ret = DER_ITCAST_FreeQueue(head);
	if(ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("keymng_msg DER_ITCAST_FreeQueue error:%d\n",ret);
		return ret;
	}
	*outNode = tmp;
	//test(*outNode);
	return 0;
}
int RecDecode_(unsigned char *in, int inLen, MsgKey_Res **pStruct)
{
	int ret= 0;
	ITCAST_ANYBUF *tmp = NULL,*head = NULL,*pTmp=NULL;
	MsgKey_Res * pStructtmp = (MsgKey_Res*)malloc(sizeof(MsgKey_Res));
	//构造被解开的结构体
	ITCAST_ANYBUF *tmpbuf=(ITCAST_ANYBUF*)malloc(sizeof(ITCAST_ANYBUF));
	memset(tmpbuf, 0, sizeof(ITCAST_ANYBUF));
	tmpbuf->pData = (unsigned char *)malloc(inLen);
	memset(tmpbuf->pData, 0, sizeof(ITCAST_ANYBUF));
	tmpbuf->dataLen= inLen;
	memcpy((void*)tmpbuf->pData,in,inLen);
	//解码大机构体为链表
	ret = DER_ItAsn1_ReadSequence(tmpbuf,&head);
	if(ret!=0)
	{
		free(tmpbuf->pData);
		free(tmpbuf);
		printf("func RecDecode_: DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	free(tmpbuf->pData);
	free(tmpbuf);
	//解码rv
	ret = DER_ItAsn1_ReadInteger(head,(ITCAST_UINT32 *)&(pStructtmp->rv));
	if(ret!=0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("func RecDecode_: DER_***_Read*** err:%d \n", ret);
		return ret;
	}
	tmp =head->next;
	//解码clientId
	ret = DER_ItAsn1_ReadPrintableString(tmp,&tmpbuf);
	if(ret!=0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("func RecDecode_: DER_***_Read*** err:%d \n", ret);
		return ret;
	}
	memcpy(pStructtmp->clientId,tmpbuf->pData,tmpbuf->dataLen);
	DER_ITCAST_FreeQueue(tmpbuf);
	tmp = tmp->next;
	//解码serverId
	ret = DER_ItAsn1_ReadPrintableString(tmp,&tmpbuf);
	if(ret!=0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("func RecDecode_: DER_***_Read*** err:%d \n", ret);
		return ret;
	}
	memcpy(pStructtmp->serverId,tmpbuf->pData,tmpbuf->dataLen);
	DER_ITCAST_FreeQueue(tmpbuf);
	tmp = tmp->next;
	//解码r2
	ret = DER_ItAsn1_ReadPrintableString(tmp,&tmpbuf);
	if(ret!=0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("func RecDecode_: DER_***_Read*** err:%d \n", ret);
		return ret;
	}
	memcpy(pStructtmp->r2,tmpbuf->pData,tmpbuf->dataLen);
	DER_ITCAST_FreeQueue(tmpbuf);
	tmp = tmp->next;
	//解码seckeyid
	ret = DER_ItAsn1_ReadInteger(tmp,(ITCAST_UINT32 *)&(pStructtmp->seckeyid));
	if(ret!=0)
	{
		DER_ITCAST_FreeQueue(head);
		printf("func RecDecode_: DER_***_Read*** err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(head);
	*pStruct=pStructtmp;
	return 0; 
}
int RecFree2_(MsgKey_Req **pStruct)
{
	MsgKey_Res *tmp = NULL;
	if (pStruct == NULL)
	{
		return 0;
	}
	tmp = (MsgKey_Res *)*pStruct;
	if(tmp!=NULL)
		free(tmp);			//bug
	*pStruct = NULL;
	return 0;
}
int MsgEncode(
	void			*pStruct, /*in*/
	int				type,
	unsigned char	**outData, /*out*/
	int				*outLen)
{
	ITCAST_ANYBUF	*pHeadbuf = NULL, *pTemp = NULL;
	ITCAST_ANYBUF			*pOutData = NULL;
	int				ret = 0;
	if (pStruct == NULL || type < 0 || outData == NULL || outLen == NULL)
	{
		ret = KeyMng_ParamErr;
		printf("func MsgEncode() err:%d check pStruct == NULL || type < 0 || outData == NULL || outLen == NULL\n", ret);
		return ret;
	}

	ret = DER_ItAsn1_WriteInteger(type, &pHeadbuf);
	if (ret != 0)
	{
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
		return ret;
	}
	switch (type)
	{
	/*case ID_MsgKey_Teacher:
		//老师编码函数
		ret = TeacherEncode_((Teacher*)pStruct, &(pHeadbuf->next));
		break;*/
	case ID_MsgKey_Req:
		//请求报文编码函数
		ret = ReqEncode_(pStruct, &(pHeadbuf->next));
		break;
	case ID_MsgKey_Res:
		//应答报文编码函数
		ret = RecEncode_(pStruct, &(pHeadbuf->next));
		break;
	default:
		ret = KeyMng_TypeErr;
		printf("func DER_ItAsn1_WriteInteger() err:%d \n", ret);
	}
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("encode err:%d \n", ret);
		return ret;
	}
	//编大结构体
	ret = DER_ItAsn1_WriteSequence(pHeadbuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("func DER_ItAsn1_WriteSequence() err:%d \n", ret);
		return ret;
	}
	//间接赋值 结果传出 通过指针做函数参数
	*outData = (unsigned char *)malloc(pOutData->dataLen);
	if (*outData == NULL)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		ret = KeyMng_MallocErr;
		printf("check malloc err:%d \n", ret);
		return ret;
	}
	memcpy(*outData, pOutData->pData, pOutData->dataLen);
	
	*outLen = pOutData->dataLen;
	DER_ITCAST_FreeQueue(pHeadbuf);
	return ret;
}

int MsgDecode(
	unsigned char *inData,/*in*/
	int           inLen,
	void          **pStruct /*out*/,
	int           *type /*out*/)
{
	ITCAST_ANYBUF		*pHeadBuf = NULL, *pTmp = NULL;
	int					ret = 0;
	unsigned long		itype = 0;

	if (inData == NULL || inLen < 0 || pStruct == NULL || type == NULL)
	{
		ret = KeyMng_ParamErr;
		printf("check inData == NULL || inLen < 0 || pStruct == NULL || type == NULL:%d\n", ret);
		return ret;
	}
	//把C buf 转成成 ITCAST_ANYBUF
	pTmp = (ITCAST_ANYBUF *)malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = KeyMng_MallocErr;
		printf("malloc() err:%d \n", ret);
		return ret;
	}
	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));
	pTmp->pData = (unsigned char *)malloc(inLen);
	if (pTmp->pData == NULL)
	{
		ret = KeyMng_MallocErr;
		printf("malloc() err:%d \n", ret);
		return ret;
	}
	memcpy(pTmp->pData, inData, inLen);
	pTmp->dataLen = inLen;

	//解码大结构体
	ret = DER_ItAsn1_ReadSequence(pTmp, &pHeadBuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pTmp);
		printf("func DER_ItAsn1_ReadSequence() err:%d \n", ret);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);

	//解码 itype
	ret = DER_ItAsn1_ReadInteger(pHeadBuf, &itype);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("func DER_ItAsn1_ReadInteger() err:%d \n", ret);
		return ret;
	}

	switch (itype)
	{
	/*case ID_MsgKey_Teacher:
		//老师结构体 解码api
		ret = TeacherDecode_(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (Teacher **)pStruct) ;
		break;*/
	case ID_MsgKey_Req:
		//请求报文 解码api
		ret = ReqDecode_(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (MsgKey_Req **)pStruct) ;
		break;
	case ID_MsgKey_Res:
		//应答报文 解码api
		ret = RecDecode_(pHeadBuf->next->pData, pHeadBuf->next->dataLen, (MsgKey_Res **)pStruct) ;
		break;
	default:
		ret = KeyMng_TypeErr;
		printf("参数不支持:%d \n", ret);
		break;
	}
	if (ret != 0)
	{
		printf("解码 失败:%d\n", ret);
		DER_ITCAST_FreeQueue(pHeadBuf);
		return ret;
	}

	*type = itype;
	DER_ITCAST_FreeQueue(pHeadBuf);
	return ret;
}

int MsgMemFree(void **point, int type)
{
	if (point == NULL)
	{
		return 0;
	}

	if (type == 0)
	{
		free(*point);
		*point = NULL;
		return 0;
	}

	switch (type)
	{
/*	case ID_MsgKey_Teacher:
		//调用释放内存api
		TeacherFree2_((Teacher **)point);
		break;
*/
	case ID_MsgKey_Req:
		//调用释放内存api
		ReqFree2_((MsgKey_Req **)point);
		break;
	case ID_MsgKey_Res:
		//调用释放内存api
		RecFree2_((MsgKey_Req **)point);
		break;
	default:
		break;
	}
	return 0;
}
