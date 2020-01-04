//#include "apue.h"
#include "pthread.h"

pthread_t ntid;

void print_ids(const char *str)
{
	pid_t 		pid;
	pthread_t 	tid;
	
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n",str, (unsigned int)pid,
		(unsigned int)tid,(unsigned int)tid);
}

void *thr_fn(void *arg)
{
	print_ids("new thread:");
	return ((void *)0);
}

int main(void)
{
	int err;
	err = pthread_create(&ntid,NULL,thr_fn,NULL);
	//if(err != 0)
	//	err_quit("can't create thread : %s\n",strerror(err));
	print_ids("main thread:");
	sleep(1);
	exit(0);
}