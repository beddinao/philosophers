#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


void	*fun(void *arg)
{
	printf("num: %i\n",     *(int *)arg);
	*(int*)arg = *(int *)arg + 1;
}


int main(void)
{
	pthread_t	thread;
	pthread_t	thread_2;
	int		num = 0;


	pthread_create(&thread, NULL, fun, &num);
	pthread_create(&thread_2, NULL, fun, &num);

	pthread_join(thread, NULL);
	pthread_join(thread_2, NULL);

	printf("threads ended: %i\n", num);
}
