#include "pthread.h"
#include "string.h"
pthread_t ntid1,ntid2;

void print_ids(const char *str)
{
	pid_t 		pid;
	pthread_t 	tid;
	
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n",str, (unsigned int)pid,
		(unsigned int)tid,(unsigned int)tid);
}

void *thr_fun1(void *str)
{
	print_ids(str);
	
	return ((void *)1);
}

void *thr_fun2(void *str)
{
	print_ids(str);
	pthread_exit((void *)2);
}

int main(void)
{
	int err;
	void *tret;
	
	
	err = pthread_create(&ntid1,NULL,thr_fun1,"fun_1");
	if(err != 0)
		printf("can't create thread : %s\n",strerror(err));
	err = pthread_create(&ntid2,NULL,thr_fun2,"fun_2");
	if(err != 0)
		printf("can't create thread : %s\n",strerror(err));
	err = pthread_join(ntid1,&tret);
	printf("thread 1 exit code is %d\n",(int)tret);
	
	err = pthread_join(ntid2,&tret);
	printf("thread 2 exit code is %d\n",(int)tret);
	sleep(1);
	exit(0);
}