#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MINPID 0
#define MAXPID 128
#include <pthread.h> 
#include <time.h>
#include <unistd.h>

unsigned long int bitmap[4];
pthread_t thread[100];

int testBit(int k)
{
	int tmp;
	tmp = bitmap[(k/32)]&(1<<(k%32)); 
	
	return tmp;
}

int allocate_map(){
	int i;
	for(i=0; i<4; i++){
		bitmap[i] = 0;
	}
	
	if(i!=0)	return 1;
	else		return -1;
}

int allocate_pid(){
	int i;
	
	for(i=0; i<MAXPID; i++){
		if(!testBit(i)){	// if 0 -> not set		
			bitmap[(i/32)] = bitmap[(i/32)]|(1<<(i%32));
			return i;
		}
	}
	return -1;
}

void release_pid(int k){
	bitmap[(k/32)] = bitmap[(k/32)]&~(1<<(k%32)); 	
}

void show(){
	int i;
	for(i=0; i<4; i++){
		printf("bitmap[%d] = %lu\n",i,bitmap[i]);
	}
}


void *threadfunc(void *arg){
	unsigned long int pid;
	pid = allocate_pid();
	
	int a,i;
	
	
	a=(rand()%10)+1;
	
	
	printf("tid is %lu\n",pthread_self());
	printf("pid is %lu, will sleep %d seconds\n",pid,a);

	sleep(a);

	release_pid(pid);
	printf("Release pid %lu\n",pid);

	pthread_exit(NULL);
	
	
}

int main(){
	int map = 0, choose = 0, del = 0, pid = 0;;
	srand(time(NULL));
	while(map!=1){
		map = allocate_map();
	}
	
	printf("-------------Allocating bitmap-------------\n");
	show();
	
	while(choose != 3){
		printf("-------------------------------------------\n");
		printf("(1)create 100 processes (2)exit\n");
		scanf("%d",&choose);

		
		if(choose == 1){
			int i;
			
			for(i = 0; i<100; i++){
				pthread_create(&thread[i], NULL, threadfunc, NULL);
			}
			//sleep(1);
			show();
			for(i=0; i<100; i++){
				pthread_join(thread[i],NULL);
			}
			
				
		}	
		if (choose == 2){
			printf("Exit this Process !\n");
			break;
		}	
		show();
	}
	
	
	
	return 0;
} 
