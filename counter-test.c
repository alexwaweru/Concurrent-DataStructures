

#include "ccounter.h"

/*************************************
void counter1(int argc, char const *argv[])
{
    printf("Thread 1\n");
    struct _counter_t c;

    init(counter_t *c)
    int t = 11;;
    int r = 10;
    int s = t+r;
    if(s >0){
	 increment(&c);
    }
    return;
}
void counter2(int argc, char const *argv[])
{
    printf("Thread 1\n");
    struct _counter_t c;

    init(counter_t *c)
    int t = 10;;
    int r = 10;
    int s = t-r;
    if(s < 1 ){
	 increment(&c);
    }
    return;
}

int main(int argc, char *argv[])
{
    pthread_t p1, p2;
    int rc;
    printf("main: begin\n");
    pthread_create(&p1, NULL, counter1, "A");
    pthread_create(&p2, NULL, counter2, "B");

    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("%s%d\n", "the counter is at ", get(&c));
    return 0;

}

*********************************************************/


int main(int argc, char const *argv[])
{
	int threads = 2;
	if (argc > 1)
	{
		threads = atoi(argv[1]);
		printf("%s%d\n", "threads to be created is: ", threads );
	}
	struct timeval tv1;
	struct timeval tv2;
	pthread_t thread_id;
	
	printf("%s\n", "creating thread");
	int start_time = gettimeofday(&tv1, NULL);
	for (int i = 0; i < threads; ++i)
	{
		pthread_create(&thread_id, NULL, myThread, (void *)&thread_id);
	}
	int end_time = gettimeofday(&tv2, NULL);
	printf("%s\n", "after creating thread" );
 	long int difference = tv2.tv_usec - tv1.tv_usec;
 	printf("%s%ld\n", "time taken to increment is: ", difference);
	printf("%s%d\n", "the counter is at ", get(&mycounter) );
	
 	
	return 0;
} 

