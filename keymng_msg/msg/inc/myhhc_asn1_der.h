#ifndef _MYHHC_MESSAGE_DER_
#define _MYHHC_MESSAGE_DER_

#ifdef __cplusplus
extern "C" {
#endif

#define MYHHCDER_NoErr 0 

typedef int					MYHHC_INT ;
typedef unsigned char       MYHHC_UINT8;
typedef unsigned short      MYHHC_UINT16;
typedef unsigned long       MYHHC_UINT32;
typedef signed long         MYHHC_SINT32;
#define  TRUE  1
#define  FALSE 0


#define    ITDER_NoErr                    0	
#define    ITDER_MemoryErr                200
#define	   ITDER_LengthErr                201
#define	   ITDER_LengthNotEqualErr        202
#define	   ITDER_DataRangeErr             203
#define	   ITDER_InvalidTagErr            204



/* The ID's for universal tag numbers 0-31.  Tag number 0 is reserved for
   encoding the end-of-contents value when an indefinite-length encoding
   is used */
enum {
        
	    MYHHC_DER_ID_RESERVED,
		MYHHC_DER_ID_BOOLEAN, 
		MYHHC_DER_ID_INTEGER,
		MYHHC_DER_ID_BITSTRING,
		MYHHC_DER_ID_OCTETSTRING,
		MYHHC_DER_ID_NULL,
		MYHHC_DER_ID_OBJECT_IDENTIFIER,
		MYHHC_DER_ID_OBJECT_DESCRIPTOR,
		MYHHC_DER_ID_EXTERNAL,
		MYHHC_DER_ID_REAL,
		MYHHC_DER_ID_ENUMERATED, 
		MYHHC_DER_ID_EMBEDDED_PDV, 
		MYHHC_DER_ID_STRING_UTF8, 
		MYHHC_DER_ID_13,
		MYHHC_DER_ID_14, 
		MYHHC_DER_ID_15, 
		MYHHC_DER_ID_SEQUENCE, 
		MYHHC_DER_ID_SET,
		MYHHC_DER_ID_STRING_NUMERIC, 
		MYHHC_DER_ID_STRING_PRINTABLE, 
		MYHHC_DER_ID_STRING_T61,
		MYHHC_DER_ID_STRING_VIDEOTEX, 
		MYHHC_DER_ID_STRING_IA5, 
		MYHHC_DER_ID_TIME_UTC,
		MYHHC_DER_ID_TIME_GENERALIZED, 
		MYHHC_DER_ID_STRING_GRAPHIC, 
		MYHHC_DER_ID_STRING_ISO646,
		MYHHC_DER_ID_STRING_GENERAL, 
		MYHHC_DER_ID_STRING_UNIVERSAL, 
		MYHHC_DER_ID_29,
		MYHHC_DER_ID_STRING_BMP
		
		};


/* Whether the encoding is constructed or primitive */

#define MYHHC_DER_CONSTRUCTED			    0x20
#define MYHHC_DER_PRIMITIVE			    0x00

/* The encodings for the universal types */
#define MYHHC_DER_UNIVERSAL			    0x00
#define MYHHC_DER_APPLICATION		   	    0x40
#define MYHHC_DER_CONTEXT_SPECIFIC	        0x80
#define MYHHC_DER_PRIVATE				    0xC0

#define MYHHC_DER_RESERVED		      ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_RESERVED )
#define MYHHC_DER_BOOLEAN			  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_BOOLEAN )
#define MYHHC_DER_INTEGER			  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_INTEGER )
#define MYHHC_DER_BITSTRING		  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_BITSTRING )
#define MYHHC_DER_OCTETSTRING		  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_OCTETSTRING )
#define MYHHC_DER_NULL			      ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_NULL )
#define MYHHC_DER_OBJECT_IDENTIFIER  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_OBJECT_IDENTIFIER )
#define MYHHC_DER_OBJECT_DESCRIPTOR  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_OBJECT_DESCRIPTOR )
#define MYHHC_DER_EXTERNAL		      ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_EXTERNAL )
#define MYHHC_DER_REAL			      ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_REAL )
#define MYHHC_DER_ENUMERATED		  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_ENUMERATED )
#define MYHHC_DER_EMBEDDED_PDV	      ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_EMBEDDED_PDV )
#define MYHHC_DER_STRING_UTF8		  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_UTF8 )
#define MYHHC_DER_13				  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_13 )
#define MYHHC_DER_14				  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_14 )
#define MYHHC_DER_15				  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_15 )
#define MYHHC_DER_SEQUENCE		      ( MYHHC_DER_UNIVERSAL | MYHHC_DER_CONSTRUCTED | MYHHC_DER_ID_SEQUENCE )
#define MYHHC_DER_SET				  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_CONSTRUCTED | MYHHC_DER_ID_SET )
#define MYHHC_DER_STRING_NUMERIC	  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_NUMERIC )
#define MYHHC_DER_STRING_PRINTABLE   ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_PRINTABLE )
#define MYHHC_DER_STRING_T61		  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_T61 )
#define MYHHC_DER_STRING_VIDEOTEX	  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_VIDEOTEX )
#define MYHHC_DER_STRING_IA5		  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_IA5 )
#define MYHHC_DER_TIME_UTC		      ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_TIME_UTC )
#define MYHHC_DER_TIME_GENERALIZED   ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_TIME_GENERALIZED )
#define MYHHC_DER_STRING_GRAPHIC	  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_GRAPHIC )
#define MYHHC_DER_STRING_ISO646	  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_ISO646 )
#define MYHHC_DER_STRING_GENERAL	  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_GENERAL )
#define MYHHC_DER_STRING_UNIVERSAL   ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_UNIVERSAL )
#define MYHHC_DER_29				  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_BER29 )
#define MYHHC_DER_STRING_BMP		  ( MYHHC_DER_UNIVERSAL | MYHHC_DER_PRIMITIVE | MYHHC_DER_ID_STRING_BMP )


/* Masks to extract information from a tag number */

#define MYHHC_DER_CLASS_MASK			0xC0
#define MYHHC_DER_CONSTRUCTED_MASK	    0x20
#define MYHHC_DER_SHORT_ID_MASK		0x1F
#define MYHHC_DER_FIRST_NOT_ID_MASK    0x7F     //xia
#define MYHHC_DER_FIRST_YES_ID_MASK    0x80     //xia
#define MYHHC_DER_ALL_YES_ID_MASK      0xFF     //xia
/* The maximum size for the short tag number encoding, and the magic value
   which indicates that a long encoding of the number is being used */

#define ITASN1_MAX_SHORT_BER_ID	    30
#define ITASN1_LONG_BER_ID		    0x1F

   
#define		DER_MYHHC_Free(memblock) {if(memblock) {free(memblock); memblock=NULL;}}  

#define DER_ITASN1_LOW_IDENTIFIER(cTag)      (cTag & MYHHC_DER_SHORT_ID_MASK)

#define  DER_CREATE_LOW_MYHHC_ANYBUF(point) \
	     point = (MYHHC_ANYBUF *)malloc(sizeof(MYHHC_ANYBUF)); \
         if (point==NULL) return 7002; \
		 memset(point,0,sizeof(MYHHC_ANYBUF)); \
         point->dataLen = 0; \
         point->dataType = 0; \
	     point->memoryType = DER_ITASN1_MEMORY_MALLOC; \
	     point->pData = NULL; \
	     point->unusedBits = 0; \
	     point->next = NULL; \
         point->prev = NULL

#define DER_ITASN1_LOW_CREATEUINT8(point,size) \
	    point = malloc(size); \
		if (point==NULL) return 7002; \
        //memset(point,0,size)

#define DER_ITASN1_LOW_CREATEUINT32(point) \
	    point = malloc(sizeof(MYHHC_UINT32)); \
		if (point==NULL) return 7002; \
        memset(point,0,sizeof(MYHHC_UINT32))

#define DER_ITASN1_LOW_CHECKERR(iResult,iErrNumber) \
	    if (iResult == iErrNumber) \
            return iErrNumber
#define DER_DACERT_LOW_FREE_ANYBUF(point) \
	    DER_MYHHC_Free(point->pData); \
        DER_MYHHC_Free(point)
#define DER_ITASN1_MEMORY_STATIC     1
#define DER_ITASN1_MEMORY_MALLOC     2

typedef struct MYHHC_ANYBUF_{
    unsigned char *pData;
    MYHHC_UINT32     dataLen;
    MYHHC_UINT32     unusedBits;  /* for bit string */  
    MYHHC_UINT32     memoryType;
    MYHHC_UINT32     dataType;
    struct MYHHC_ANYBUF_ *next;    /* for sequence and set */
    struct MYHHC_ANYBUF_ *prev;
}MYHHC_ANYBUF;
 
typedef MYHHC_UINT8     ITASN1_BOOLEAN;
typedef MYHHC_ANYBUF    ITASN1_INTEGER;
typedef MYHHC_ANYBUF    ITASN1_OCTETSTRING;
typedef MYHHC_ANYBUF    ITASN1_BITSTRING;
typedef MYHHC_ANYBUF    ITASN1_PRINTABLESTRING;
/*begin of bmpstring*/
typedef MYHHC_ANYBUF	 ITASN1_BMPSTRING;
/*end of bmpstring*/
typedef MYHHC_ANYBUF    ITASN1_ENUMERATED;
typedef MYHHC_ANYBUF    ITASN1_IA5STRING;
typedef MYHHC_ANYBUF    ITASN1_SEQUENCE;
typedef MYHHC_ANYBUF    ITASN1_SET; 
//typedef time_t       ITASN1_GENERALIZEDTIME;
//typedef time_t       ITASN1_UTCTIME;
//*****************************************************************************常用
//编解码    int     型为ITASN1_INTEGER结构体
MYHHC_INT
DER_ItAsn1_WriteInteger(MYHHC_UINT32 integer,ITASN1_INTEGER **ppDerInteger);

MYHHC_INT
DER_ItAsn1_ReadInteger(ITASN1_INTEGER *pDerInteger,MYHHC_UINT32 *pInteger);

//编解码MYHHC_ANYBUF型    链表    为MYHHC_ANYBUF结构体（ITASN1_SEQUENCE与MYHHC_ANYBUF）
MYHHC_INT
DER_ItAsn1_WriteSequence(ITASN1_SEQUENCE *pSequence,MYHHC_ANYBUF **ppDerSequence);

MYHHC_INT
DER_ItAsn1_ReadSequence(MYHHC_ANYBUF *pDerSequence,ITASN1_SEQUENCE **ppSequence);

//编解码字符串，将字符串存到ITASN1_PRINTABLESTRING结构体中，
MYHHC_INT
DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING *pPrintString,ITASN1_PRINTABLESTRING **ppDerPrintString);

MYHHC_INT
DER_ItAsn1_ReadPrintableString(ITASN1_PRINTABLESTRING *pDerPrintString,ITASN1_PRINTABLESTRING **ppPrintString);
//释放MYHHC_ANYBUF型链表
MYHHC_INT 
DER_MYHHC_FreeQueue(MYHHC_ANYBUF *pAnyBuf);

//编码字符串
int EncodeChar(char *pData, int dataLen, MYHHC_ANYBUF **outBuf);
//编码无符号型字符串
int EncodeUnsignedChar(unsigned char *pData, int dataLen, MYHHC_ANYBUF **outBuf);
//解码字符串
int DecodeChar(MYHHC_ANYBUF *inBuf, char **Data, int *pDataLen);
//*****************************************************************************常用




MYHHC_INT
DER_ItAsn1_WriteBitString(ITASN1_BITSTRING *pBitString,ITASN1_BITSTRING **ppDerBitString);

MYHHC_INT
DER_ItAsn1_ReadBitString(ITASN1_BITSTRING *pDerBitString,ITASN1_BITSTRING **ppBitString);
//
MYHHC_INT
DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING *pPrintString,ITASN1_PRINTABLESTRING **ppDerPrintString);

MYHHC_INT
DER_ItAsn1_ReadPrintableString(ITASN1_PRINTABLESTRING *pDerPrintString,ITASN1_PRINTABLESTRING **ppPrintString);



MYHHC_INT
DER_ItAsn1_WriteNull(MYHHC_ANYBUF ** ppDerNull);

MYHHC_INT
DER_ItAsn1_ReadNull(MYHHC_ANYBUF * ppDerNull, MYHHC_UINT8 * pInt);

MYHHC_INT
DER_MYHHC_String_To_AnyBuf(MYHHC_ANYBUF **pOriginBuf,	unsigned char * strOrigin,	int  strOriginLen);

int WriteNullSequence(MYHHC_ANYBUF **pOutData);


#ifdef __cplusplus
}
#endif

#endif
