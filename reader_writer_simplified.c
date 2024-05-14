#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 3

int mutex = 1; // Semaphore for mutual exclusion
int reader_sem = 1; // Semaphore for controlling readers
int writer_sem = 1; // Semaphore for controlling writers
int readcnt=0;
void wait(int *semaphore) {
    while (*semaphore <= 0) {
        usleep(1000);
    }
    *semaphore -= 1;
}

void signall(int *semaphore) {
    *semaphore += 1;
}


void readd(){
	wait(&mutex);
	readcnt++;
	if(readcnt==1){
		wait(&writer_sem);
	}
	signall(&mutex);
	//reader does the reading stuff
	printf("reader does reading");
	wait(&mutex);
	readcnt--;
	if(readcnt==0){
		signall(&writer_sem);
	}
	signall(&mutex);
}


void writee(){
	wait(&writer_sem);
	//does the writing processing
	printf("writer does writing ");
	signall(&writer_sem);
}
int main() {
    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];
    int i;

    for (i = 0; i < NUM_READERS; i++) {
        pthread_create(&reader_threads[i], NULL, readd, NULL);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writer_threads[i], NULL, writee, NULL);
    }


    return 0;
}


