#include <stdio.h>
#include <pthread.h>

void *hello (void * arg) { 
	printf("Hello Thread\n"); 
}

void main() {
  pthread_t tid;

  pthread_create(&tid, NULL, hello, NULL);

  getchar();
}