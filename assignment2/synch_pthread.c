#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define ITER 1000

void *thread_increment(void *arg);
void *thread_decrement(void *arg);
int x;
int MAX = 30;
pthread_mutex_t m;
pthread_cond_t fill, empty;

int main() {
	pthread_t tid1, tid2;
	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&fill, NULL);
	pthread_cond_init(&empty, NULL);

	pthread_create(&tid1, NULL, thread_increment,NULL);
	pthread_create(&tid2, NULL, thread_decrement, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if(x != 0)
		printf("BOOM! counter = %d\n", x);
	else
		printf("OK counter = %d\n", x);

	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&fill);
	pthread_cond_destroy(&empty);
}

void *thread_increment(void *arg){ // 생산자
	int i, val;
	
	for (i = 0 ; i < ITER ; i++){
		pthread_mutex_lock(&m);

		while(x == MAX)
			pthread_cond_wait(&empty, &m); // 자원이 최대면 empty되기를 기다린다.
		
		val = x;
		printf("%u : %d\n", (unsigned int) pthread_self(), val);
		x = val + 1;

		pthread_cond_signal(&fill); // 생산 후 fill에게 signal을 보낸다
		pthread_mutex_unlock(&m);
	}

	return NULL;
}

void *thread_decrement(void *arg){ // 소비자
	int i, val;
	
	for (i = 0 ; i < ITER ; i++){
		pthread_mutex_lock(&m);

		while(x == 0)
			pthread_cond_wait(&fill, &m); // 자원이 0이면 fill되기를 기다린다.

		val = x;
		printf("%u : %d\n", (unsigned int) pthread_self(), val);
		x = val - 1;

		pthread_cond_signal(&empty); // 소비 후 empty에게 signal을 보낸다.
		pthread_mutex_unlock(&m);
	}
	
	return NULL;
}
