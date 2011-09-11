#include <pthread.h>
#include <stdio.h>

#define CORE_NUM 2
#define NUM 100000

struct range
{
	int start;
	int end;
};

void * calcSum(void * data)
{
	struct range * ptr = (struct range *)data;
	int sum = 0;
	int i;

	for (i = ptr->start; i <= ptr->end; ++i)
		sum +=i;
	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
	struct range rg[CORE_NUM];
	int i;
	int avg = NUM/CORE_NUM;
	pthread_t threads[CORE_NUM];
	int rc;

	for (i = 0; i < CORE_NUM; ++i)
	{
		rg[i].start = i * avg + 1;
		rg[i].end = (i + 1) * avg;
		if ( i == CORE_NUM - 1)
			rg[i].end = NUM;

		rc = pthread_create(&threads[i], NULL, calcSum, (void*)rg[i]);
		if (rc) {
			printf("error : returen code is %d\n", rc);
		}
	}

	pthread_exit(NULL);
}


