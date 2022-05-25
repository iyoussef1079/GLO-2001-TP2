#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


typedef struct
{
	int ThreadNum;

} Parametres;

void change_scheduler(int scheduler)
{
	struct sched_param Param;
	int maxPriority = sched_get_priority_max(scheduler);
	int minPriority = sched_get_priority_min(scheduler);
	int meanPriority = (maxPriority + minPriority) / 2;
	Param.sched_priority = meanPriority;

	sched_setscheduler(0, scheduler, &Param);
	int ThreadID = syscall(SYS_gettid);
	printf("Code retour de errno pour changement d'ordonnanceur pour processus %d : %s. \n", ThreadID, strerror(errno));
}

void *work( void *data) {
	Parametres *pParam = (Parametres *)data;
	printf("Je suis le thread %d et je demarre !!! \n", pParam->ThreadNum);
	change_scheduler(SCHED_FIFO);
	printf("Code retour de errno pour processus %d : %s. \n", pParam->ThreadNum, strerror(errno));
	while(1);
}


int main(int argc, char **argv) {
	pthread_t threads[5];
	Parametres myParam[5];
	int status, i; 
	for(i = 0; i < 5; i++) {
		printf("Main(): en train de creer thread %d\n",i);
		myParam[i].ThreadNum = i;
		pthread_create(&threads[i], NULL, work, (void *)&myParam[i]);
	}
	for (i = 0; i < 5; i++)
	{
		pthread_join(threads[i], NULL);
	}
		
	return 1;	
}



