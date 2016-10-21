#include <sys/shm.h> 
#include <sys/ipc.h>   
#include <stdio.h>

int main()
{
	int hand;
	int key=0x1111;
	int size=128;
	hand= shmget(key,size,0666|IPC_CREAT);
}
