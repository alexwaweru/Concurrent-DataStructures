

#include "ccounter.h"


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

