// keymnglog.h

#ifndef _KEYMNG_LOG_H_
#define _KEYMNG_LOG_H_
//定义要写入的文件名，文件将写入$(HOME)/log/目录下
#define MYLOG_DEBUG_FILE_  "keymngclient.log"
/*
#define IC_NO_LOG_LEVEL			0
#define IC_DEBUG_LEVEL			1
#define IC_INFO_LEVEL			2
#define IC_WARNING_LEVEL		3
#define IC_ERROR_LEVEL			4; 
*/

/************************************************************************/
/* 
const char *file：文件名称
int line：文件行号
int level：错误级别
		0 -- 没有日志
		1 -- debug级别
		2 -- info级别
		3 -- warning级别
		4 -- err级别
int status：错误码
const char *fmt：可变参数
*/
/************************************************************************/
//实际使用的Level
extern int  KeyMngLevel[5];
void KeyMng_Log(const char *file, int line, int level, int status, const char *fmt, ...);
//eg:KeyMng_Log(__FILE__, __LINE__,KeyMngLevel[4], 1,"func err"); //__FILE__是文件名的宏 __LINE__是文件行号的宏
#endif
