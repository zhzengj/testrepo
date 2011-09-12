#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

struct range
{
	int start;
	int end;
};

struct stCalcSum
{
	int threadCount;
	int start;
	int end;
	struct range * rg;
};

#define OPT_STR "s:e:t:"
long long g_sum = 0;
pthread_mutex_t mutex;

static void * z_tcallback_calcsum(void * data)
{
	struct range * ptr = (struct range *)data;
	long long sum = 0;
	int i;

	for (i = ptr->start; i <= ptr->end; ++i)
		sum +=i;
	pthread_mutex_lock(&mutex);
	g_sum += sum;
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

static void z_calcsum_parseArg(struct stCalcSum * p, int argc, char *argv[])
{
	int opt;
	while((opt = getopt(argc, argv, OPT_STR)) != -1) {
		switch(opt) {
		case 't' :
			p->threadCount = atoi(optarg);
			break;
		case 's':
			p->start = atoi(optarg);
			break;
		case 'e':
			p->end = atoi(optarg);
			break;
		case '?':
			printf("unknown option\n");
			break;
		}
	}
}

static bool z_calcsum_init(struct stCalcSum *p, int argc, char * argv[])
{
	memset(p, 0, sizeof(struct stCalcSum)); 
	z_calcsum_parseArg(p, argc, argv);
	if (p->start > p->end || p->threadCount < 0)
		return false;

	if (p->threadCount != 0) {
		int step = (p->end - p->start + 1) / p->threadCount;
		int i;
		p->rg = (struct range *)malloc(sizeof(struct range) * (p->threadCount));

		for (i = 0; i < p->threadCount; ++i) {
			p->rg[i].start = p->start + step * i;
			p->rg[i].end = p->rg[i].start + step - 1;
			if (i == (p->threadCount - 1))
				p->rg[i].end = p->end;
		}
	}
	return true;
}

static void z_calcsum_destroy(struct stCalcSum * p)
{
	if (p->rg)
		free(p->rg);
	free(p);
}

int main(int argc, char * argv[])
{
	struct stCalcSum * p = (struct stCalcSum*)malloc(sizeof(struct stCalcSum));
	int i;

	if (!z_calcsum_init(p, argc, argv)) {
		z_calcsum_destroy(p);
		return -1;
	}

	if (p->threadCount == 0) {
		for (i = p->start; i <= p->end; ++i)
			g_sum += i;
	}
	else {
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * p->threadCount);
		pthread_attr_t attr;
		int rc;
		void *status;

		pthread_mutex_init(&mutex, NULL);
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		for (i = 0; i < p->threadCount; ++i) {
			rc = pthread_create(&threads[i], &attr, z_tcallback_calcsum, (void*)&p->rg[i]);
			if (rc) 
				printf("error : return code is %d\n", rc);
		}
		pthread_attr_destroy(&attr);

		for(i = 0; i < p->threadCount; ++i) {
			//pthread_join block until thread term or already term.
			rc = pthread_join(threads[i], &status);
			if (rc) 
				printf("error pthread_join : return code is %d\n", rc);
		}

		pthread_mutex_destroy(&mutex);
	}

	printf("sum is %lld", g_sum);

	z_calcsum_destroy(p);

	pthread_exit(NULL);
}

