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

int main31()
{
	int shmid = 0;
	//创建共享内存
	//相当于打开共享内存( 打开文件)
	//若文件存在  则使用旧的 
	//若文件不存在 则报错

	shmid = shmget(0x1111, 100, 0666 );
	if (shmid < 0)
	{
		printf("func shmget() err\n");
		return 0;
	}
	printf("创建共享内存 ok\n");
	return 0;
}



int main32()
{
	int shmid = 0;
	//创建共享内存
	//相当于打开共享内存( 打开文件)
	//若文件存在  则使用旧的 
	//若文件不存在 则创建
	shmid = shmget(0x1111, 100, 0666 |IPC_CREAT );
	if (shmid < 0)
	{
		printf("func shmget() err\n");
		return 0;
	}
	printf("创建共享内存 ok\n");
	return 0;
}

/*
------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x00001111 196613     it01       666        100        0    
*/


int main33()
{
	int shmid = 0;
	//创建共享内存
	//相当于打开共享内存( 打开文件)
	//若文件存在  则报错  //避免旧的共享内存被覆盖
	//若文件不存在 则创建
	shmid = shmget(0x1111, 100, 0666 |IPC_CREAT |IPC_EXCL );
	if (shmid < 0)
	{
		printf("func shmget() err\n");
		return 0;
	}
	printf("创建共享内存 ok\n");
	return 0;
}



int main()
{
	int shmid = 0;
	//创建共享内存
	//相当于打开共享内存( 打开文件)
	//若文件存在  则使用旧的 
	//若文件不存在 则创建
	shmid = shmget(0x1111, 100, 0666 |IPC_CREAT );
	if (shmid < 0)
	{
		printf("func shmget() err\n");
		return 0;
	}
	printf("创建共享内存 ok\n");
	
	
	//连接共享内存
	//	void *shmat(int shmid, const void *shmaddr, int shmflg);
	
    void *p = shmat(shmid, NULL, 0);
    printf("%d\n",p);
    
    strcpy((char *)p, "111122234344");
    
    printf("p:%s \n", p);
    
    
    printf("任意键删除连共享内存\n");
    getchar();
    
    
    //取消连接共享内存
   // shmdt(p);

 
    //删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    
	return 0;
}
