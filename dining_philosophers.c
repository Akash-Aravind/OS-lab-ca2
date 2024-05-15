#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
int chopstick[NUM_PHILOSOPHERS] = {1, 1, 1, 1, 1}; // 1 represents available, 0 represents taken

void wait(int *semaphore){
	while(*semaphore==0){
		usleep(1000);
	}
	*semaphore=0;
}
void signall(int *semaphore){
	*semaphore=1;
}


void philosopher(int *id){
	int local_id=*id;
	wait(&chopstick[local_id]);
	wait(&chopstick[(local_id + 1) % NUM_PHILOSOPHERS]);
	
	//philosopher does something
	printf("Now philosopher %d is using the chopsticks %d %d",local_id,local_id,local_id+1 );
	usleep(40000);
	
	signall(&chopstick[local_id]);
	signall(&chopstick[(local_id + 1) % NUM_PHILOSOPHERS]);	
}

void main(){
	pthread_t philosophers[NUM_PHILOSOPHERS];
	int ids[NUM_PHILOSOPHERS]={0,1,2,3,4};
	int i=0;
	
	for(i=0;i<NUM_PHILOSOPHERS;i++){
		pthread_create(&philosophers[i],NULL,philosopher,&ids[i]);
	}
}

