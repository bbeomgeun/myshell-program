#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define ITER 1000

void *thread_increment(void *arg);
void *thread_decrement(void *arg);
int x;
sem_t s, n, e;

int main() {
	pthread_t tid1, tid2;
	sem_init(&s, 0, 1);
	sem_init(&n, 0, 0); // data = 0;
	sem_init(&e, 0, 30); // bufferSize = 30;
	pthread_create(&tid1, NULL, thread_increment,NULL);
	pthread_create(&tid2, NULL, thread_decrement, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if(x != 0)
		printf("BOOM! counter = %d\n", x);
	else
		printf("OK counter = %d\n", x);
	sem_destroy(&s);
	sem_destroy(&n);
	sem_destroy(&e);
}

void *thread_increment(void *arg){ // 생산자
	int i, val;
	for (i = 0 ; i < ITER ; i++){
		sem_wait(&e); // 비워지기를 기다림
		sem_wait(&s); // 상호 배제
		val = x;
		printf("%u : %d\n", (unsigned int) pthread_self(), val);
		x = val + 1;
		sem_post(&s); // 상호 배제
		sem_post(&n); // 생산 후 시그널
	}
	return NULL;
}

void *thread_decrement(void *arg){ // 소비자
	int i, val;
	for (i = 0 ; i < ITER ; i++){
		sem_wait(&n); // 데이터를 기다림
		sem_wait(&s); // 상호 배제
		val = x;
		printf("%u : %d\n", (unsigned int) pthread_self(), val);
		x = val - 1;
		sem_post(&s); // 상호 배제
		sem_post(&e); // 소비 후 시그널
	}
	return NULL;
}
