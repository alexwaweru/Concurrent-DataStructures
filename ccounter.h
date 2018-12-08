#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
 typedef struct _counter_t{
	int value;
}counter_t;
 void init(counter_t *c) {
	//Pthread_mutex_lock(&c->lock);
	c->value = 0;
	//Pthread_mutex_unlock(&c->lock);
}
 void increment(counter_t *c){
	c->value++;
}
 void decrement(counter_t *c){
	c->value--;
}
 int get(counter_t *c){
	return c->value;
}
 counter_t mycounter;
void *myThread(void *vargp){
	printf("%s\n", "thread is created");
	increment(&mycounter);
	return NULL;
}



