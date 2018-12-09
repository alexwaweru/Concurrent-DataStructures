#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
 typedef struct _counter_t{
	int value;
	pthread_mutex_t lock;
}counter_t;
 void init(counter_t *c) {
	
	c->value = 0;
	pthread_mutex_init(&c->lock, NULL);
	
}
 void increment(counter_t *c){
	pthread_mutex_lock(&c->lock);
	c->value++;
	pthread_mutex_unlock(&c->lock);
}
 void decrement(counter_t *c){
	pthread_mutex_lock(&c->lock);
	c->value--;
	pthread_mutex_unlock(&c->lock);
}
 int get(counter_t *c){
	pthread_mutex_lock(&c->lock);
	int rc = c->value;
	pthread_mutex_lock(&c->lock);
	return rc;
}
 
counter_t mycounter;
void *myThread(void *vargp){
	printf("%s\n", "thread is created");
	increment(&mycounter);
	return NULL;
}



