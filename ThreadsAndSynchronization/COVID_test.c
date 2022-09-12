#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
//Used to include input streams

void* phonecall(void* vargp);

static sem_t connected_lock;								//initializing all needed semaphores.
static sem_t lock_operators;

static int num_operators = 4;								//initializing given and extra variables.
static int num_lines = 7;
static int num_connected = 0;
static int next_id = 0;
static int freeOps = 4;

int main(int argc, char **argv){
  if(argc <= 1){									//Test this case earlier to save memory.
    printf("Invalid entry please enter the number of calls to be greater than 1");
    exit(3);
  }
  int calls = atoi(argv[1]);
  pthread_t arrID[calls];
  for(int i=0; i<calls; ++i){								//Create Threads
    pthread_create(&arrID[i],NULL,phonecall,NULL);
  }
  for(int i=0 ;i<calls; ++i){								//Destroy the Threads
    pthread_join(arrID[i],NULL);
  }
  sem_destroy(&connected_lock);								//Destroy the Semaphores
  sem_destroy(&lock_operators);
  exit(1);
  return 0;
}

void* phonecall(void* vargp){
  sem_init(&connected_lock,0,1);							//Initialize the binary and counting semaphores
  sem_init(&lock_operators,0,num_operators);
  int currID = ++next_id;								//Use an integer variable to store the current caller number.
  printf("Currently attempting to connect Caller <%i>, please wait....\n",currID);

  sem_wait(&connected_lock);								//Using the binary semaphore to lock the integer with respect to the connections.
  
  if(num_connected == num_lines){							//A different case when there is not much traffic but all lines are currently full.
    printf("All lines are currently busy, please call in a while, Thank You\n");
    sem_post(&connected_lock);
    sleep(3);
    sem_wait(&connected_lock);
  }
  sem_post(&connected_lock);

  while(freeOps > 0){
    sem_wait(&connected_lock);
    if(num_connected < num_lines){
      num_connected++;
      sem_post(&connected_lock);
      printf("A connection to the line has been made for Caller <%i>!\nFinding an available operator....\n",currID);
      break;
      }
    sem_post(&connected_lock);
  }
  sem_wait(&lock_operators);

  if(freeOps == 0){									//Like for lines, a case where there are no free operators at the moment
    printf("Please wait till one of our operators can assist you, Thank You\n");
    sem_post(&lock_operators);
    sleep(3);
    sem_wait(&lock_operators);
  }
  --freeOps;
  printf("A successfull connection has been made to one of our operators for Caller <%i>!\n",currID);		//Code for when there has been a connection made with the operator
  sleep(3);
  sem_post(&lock_operators);
  printf("Thank You for booking an appointment Caller <%i>! The operator has left this call\n",currID);
  ++freeOps;
  sem_wait(&connected_lock);								//Finish the phone call and end the connection, the number of connected lines will decrement
  --num_connected;
  sem_post(&connected_lock);
  
  printf("Caller <%i> has hung up.\n",currID);
}
