#include "queue.h"
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

void test_queue1(int argc, char const *argv[])
{
    printf("Thread 1\n");
    struct __queue_t q;

    Queue_Init(&q);
    printf("Queue successfully initialized\n");
    Queue_Enqueue(&q, 1);
    printf("Value successfully added\n");
    Queue_Dequeue(&q);
    printf("Queue successfully dequeued\n");
    return;
}

void test_queue2(int argc, char const *argv[])
{
    printf("Thread 2\n");
    struct __queue_t q;

    Queue_Init(&q);
    printf("Queue successfully initialized\n");
    Queue_Enqueue(&q, 2);
    printf("Value successfully added\n");
    Queue_Dequeue(&q);
    printf("Queue successfully dequeued\n");
    return;
}

int main(int argc, char *argv[])
{
    pthread_t p1, p2;
    int rc;
    printf("main: begin\n");
    pthread_create(&p1, NULL, test_queue1, "A");
    pthread_create(&p2, NULL, test_queue2, "B");

    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main: end\n");
    return 0;
}
