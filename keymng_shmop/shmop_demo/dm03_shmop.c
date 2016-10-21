#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

 #include <sys/ipc.h>
       #include <sys/shm.h>
 int shmget(key_t key, size_t size, int shmflg);


int main31()
{
	//打开共享内存 	//打开文件  
	//若文件存在 使用旧的文件
	//若文件不存在 报错
	int			ret = 0;
	
	//输入一个key 得到一个句柄
	ret = shmget(0x2222, 128, 0666);  
	if (ret <0 )
	{
		printf("func shmget() err:%d\n", ret);
		return ret;
	}
	else
	{
		printf("func shmget() ok:%d\n", ret);
	}
	
	printf("hello shm...\n");
	return 0;
}

int main32()
{
	//打开共享内存 	//打开文件  
	//若文件存在 使用旧的
	//若文件不存在 在创建
	int			ret = 0;
	
	//输入一个key 得到一个句柄
	ret = shmget(0x2222, 128, 0666 |IPC_CREAT);  
	if (ret <0 )
	{
		printf("func shmget() err:%d\n", ret);
		return ret;
	}
	else
	{
		printf("func shmget() ok:%d\n", ret);
	}
	
	printf("hello shm...\n");
	return 0;
}


int main33()
{
	//打开共享内存 	//打开文件  
	//若文件存在 报错
	//若文件不存在 在创建
	int			ret = 0;
	
	//输入一个key 得到一个句柄
	ret = shmget(0x2222, 128, 0666 |IPC_CREAT |IPC_EXCL);  
	if (ret <0 )
	{
		printf("func shmget() err:%d 共享内存已经存在 报错\n", ret);
		return ret;
	}
	else
	{
		printf("func shmget() ok:%d\n", ret);
	}
	
	printf("hello shm...\n");
	return 0;
}

//////////////--------------------------------------------------------///

int main()
{
	//打开共享内存 	//打开文件  
	//若文件存在 使用旧的
	//若文件不存在 在创建
	int 			shmid = 0;
	
	//输入一个key 得到一个句柄
	shmid = shmget(0x2222, 128, 0666 |IPC_CREAT);  
	if (shmid <0 )
	{
		printf("func shmget() err:%d\n", shmid);
		return shmid;
	}
	else
	{
		printf("func shmget() ok:%d\n", shmid);
	}
	
	//       void *shmat(int shmid, const void *shmaddr, int shmflg);
	
	//进程 连接 共享内存 得到一个内存首地址
    void *p = shmat(shmid,  NULL, 0);
    if (p == NULL)
    {
    	printf("func shmat() err \n");
    }
    
    printf("连接上共享内存了 任意键继续...\n");
    getchar();
    
    
    strcpy(p, "1fewqrwqrewqrewq");
    
    printf("p:%s\n", (char *)p);
    
    
    //反链接共享内存
    shmdt(p);
    
    //删除共享内存
     shmctl(shmid, IPC_RMID, NULL);
 
   
	
	printf("hello shm...\n");
	return 0;
}
