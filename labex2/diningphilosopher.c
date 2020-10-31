#include <stdio.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>

#define key (20180201)

pid_t processes[1000];
int N;
void sigHandler(int sig);

int main (int argc, char *argv[]){
  processes[0] = getpid();  
  signal(SIGINT,sigHandler);
  N = atoi(argv[1]);
  if (argc == 1){
  	printf("Please give CLA\n");
  	exit(0);}

  int id;
  
 // sem_t *chopsticks;
  int semsetid;
  
  semget(key, N, IPC_CREAT);

  
  for(int i = 0; i < N; i++){
    semctl(semsetid, i, SETVAL, 1);	  
  //  chopsticks = mmap(NULL, N * sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS,-1,-0);
  }



  struct sembuf sops;
 // for(int i = 0; i < N; i++){
   // sem_init(&chopsticks[i], 1, 0);
  //}

  
  
 
  for (int i = 0; i < N; i++){
    if (fork() == 0){
      processes[i+1] = getpid();
      for(;;){
	//sem_wait(&chopsticks[i]);
	sops.sem_num = i;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	
	semop(semsetid, &sops, 1);
	
	//sem_wait(&chopsticks[(i+1)%N]);
	sops.sem_num = (i+1)%N;
	
	semop(semsetid, &sops, 1);


	
	printf("PID %d : Philosopher %d is eating now\n",getpid(), i);

	

	
	//sem_post(&chopsticks[(i+1)%N]);
	sops.sem_op = 1;
	semop(semsetid, &sops, 1);

	//sem_post(&chopsticks[i]);
	sops.sem_num = i;
	semop(semsetid, &sops, 1);

	
      }          
      break;
    }
    
  }

}


void sigHandler(int sig){
 	
 		for(int i = 0; i <= N; i++){
 			kill(processes[i], SIGKILL);
 			}
 			
  
  exit(SIGINT);
}
