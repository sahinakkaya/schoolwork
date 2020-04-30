/*
Author: Şahin Akkaya
Studend ID: 150170098
*/

#include <math.h>     // ceil, sqrt
#include <pthread.h>  // thread functions
#include <stdbool.h>
#include <stdio.h>   // printf, sscanf
#include <stdlib.h>  // general functions
#include <string.h>
#include <sys/shm.h>   // shared memory operations
#include <sys/wait.h>  // wait
#include <unistd.h>    // fork

#define MAX_NUM_OF_PRIMES 500000
#define and &&
#define or ||

// lock for mutex
pthread_mutex_t lock;


// shared memory keys
int KEYSHM;
int KEYSHM2;

// shared memory id's
int shmid_4_num_of_primes;
int shmid_4_primes;

// init function for shared memory keys
void initKeys(const char* argv[]) {
  char cwd[256];
  char* keyString;

  getcwd(cwd, 256);
  keyString = malloc(strlen(cwd) + strlen(argv[0]) + 2);
  strcpy(keyString, cwd);
  strcat(keyString, "/");
  strcat(keyString, argv[0]);
  KEYSHM = ftok(keyString, 3);
  KEYSHM2 = ftok(keyString, 2);
  free(keyString);
}

// struct that will hold necessary information for workers
typedef struct Worker {
  int lower_bound;
  int upper_bound;
  int process_order;
  int worker_order;
  int* primes;
  int* num_of_primes;
} Worker;



// worker function
void* search_for_primes(void* args) {
  Worker* worker = (Worker*)args;
  int lower_bound = worker->lower_bound;
  int upper_bound = worker->upper_bound;
  int process_order = worker->process_order;
  int worker_order = worker->worker_order;
  int* primes = worker->primes;
  int* num_of_primes = worker->num_of_primes;

  printf("Thread %d.%d: searching in %d-%d\n", process_order, worker_order,
         lower_bound, upper_bound);

  for (int i = lower_bound; i <= upper_bound; i++) {
    if (i == 1 || i == 0) continue;
    bool is_prime = true;
    int divisor = 2;
    double sq = sqrt(i);
    while (divisor <= sq) {
      if (i % divisor == 0) {
        is_prime = false;
        break;
      }
      divisor++;
    }
    if (is_prime) {
      // -- BEGIN CRITICAL SECTION
      pthread_mutex_lock(&lock);
      primes[(*num_of_primes)++] = i;
      pthread_mutex_unlock(&lock);
      // -- END CRITICAL SECTION
    }
  }

  printf("Thread %d.%d: Done.\n", process_order, worker_order);
  free(args);
  args = NULL;
  pthread_exit(NULL);
}

// comparison function that is used by qsort
int comp(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int main(int argc, char const* argv[]) {
  if (argc != 5) {
    printf("Please supply correct number of arguments.\n");
    return EXIT_FAILURE;
  }

  int* num_of_primes;
  int* primes;

  int lower_bound, upper_bound, np, nt;
  sscanf(argv[1], "%d", &lower_bound);
  sscanf(argv[2], "%d", &upper_bound);
  sscanf(argv[3], "%d", &np);
  sscanf(argv[4], "%d", &nt);

  if (pthread_mutex_init(&lock, NULL) != 0) {
    printf("\n mutex init has failed\n");
    return EXIT_FAILURE;
  }

  initKeys(argv);
  int process_index, worker_index;

  // create shared memories
  shmid_4_primes = shmget(KEYSHM, sizeof(int) * MAX_NUM_OF_PRIMES, 0700 | IPC_CREAT);
  shmid_4_num_of_primes = shmget(KEYSHM2, sizeof(int), 0700 | IPC_CREAT);

  // init shared memories
  num_of_primes = (int*)shmat(shmid_4_num_of_primes, 0, 0);
  *num_of_primes = 0;
  shmdt(num_of_primes);

  int pid;
  int status = 0;
  pid_t wpid;

  printf("Master: Started!\n");

  // create slaves
  for (process_index = 0; process_index < np; process_index++) {
    pid = fork();
    if (pid == -1) {
      printf("ERROR: cannot fork!\n");
      shmctl(shmid_4_primes, IPC_RMID, 0);
      shmctl(shmid_4_num_of_primes, IPC_RMID, 0);
      return EXIT_FAILURE;
    }
    if (pid == 0) {
      break;
    }
  }

  // parent process
  if (pid != 0) {
    bool reached_max_num_of_primes = false;
    // wait children and check status codes
    while ((wpid = wait(&status)) > 0)
      if (status == 256) reached_max_num_of_primes = true;

    if (reached_max_num_of_primes) {
      printf("ERROR: reached MAX_NUM_OF_PRIMES limit: %d\n", MAX_NUM_OF_PRIMES);
      shmctl(shmid_4_primes, IPC_RMID, 0);
      shmctl(shmid_4_num_of_primes, IPC_RMID, 0);
      return EXIT_FAILURE;
    }


    num_of_primes = (int*)shmat(shmid_4_num_of_primes, 0, 0);
    primes = (int*)shmat(shmid_4_primes, 0, 0);

    printf("%d prime numbers found!\n", *num_of_primes);
    printf("Master: Done. Prime numbers are: ");

    qsort(primes, *num_of_primes, sizeof(int), comp);

    for (int i = 0; i < *num_of_primes; i++) {
      printf("%d, ", primes[i]);
    }
    printf("\n");

    shmdt(num_of_primes);
    shmdt(primes);

    shmctl(shmid_4_primes, IPC_RMID, 0);
    shmctl(shmid_4_num_of_primes, IPC_RMID, 0);
    return EXIT_SUCCESS;
  } else {
    int process_order = process_index + 1;
    int worker_order;

    // calculate searching interval for process
    int p_interval = ceil((upper_bound - lower_bound) / (float)np);
    int p_lower = lower_bound + p_interval * process_index;
    int p_upper = lower_bound + p_interval * (process_index + 1) - 1;

    if (process_index + 1 == np and
        (p_upper + 1 == upper_bound or p_upper > upper_bound))
      p_upper = upper_bound;

    printf("Slave %d: Started. Interval %d-%d\n", process_index + 1, p_lower,
           p_upper);
    int* process_primes = (int*)malloc(sizeof(int) * (p_upper - p_lower));
    int process_num_of_primes = 0;

    // create workers
    pthread_t workers[nt];
    for (worker_index = 0; worker_index < nt; worker_index++) {
      worker_order = worker_index + 1;

      // calculate searching interval for worker
      int w_interval = ceil((p_upper - p_lower) / (float)nt);
      int w_lower = p_lower + w_interval * worker_index;
      int w_upper = p_lower + w_interval * (worker_index + 1) - 1;

      if (worker_index + 1 == nt and
          (w_upper + 1 == p_upper or w_upper > p_upper))
        w_upper = p_upper;

      // initialize arguments of the worker
      Worker* worker = (Worker*)malloc(sizeof(Worker));
      worker->lower_bound = w_lower;
      worker->upper_bound = w_upper;
      worker->process_order = process_order;
      worker->worker_order = worker_order;
      worker->primes = process_primes;
      worker->num_of_primes = &process_num_of_primes;

      if (pthread_create(&workers[worker_index], NULL, search_for_primes,
                         (void*)worker)) {
        printf("ERROR: cannot create thread %d.%d!\n", process_order, worker_order);
        printf("Maybe your system does not allow this number of threads? ");
        printf("You can try again with lower number of threads\n");
        free(process_primes);
        return EXIT_FAILURE;
      }
    }
    // wait until all workers done
    for (int i = 0; i < nt; i++) pthread_join(workers[i], NULL);

    int* primes = (int*)shmat(shmid_4_primes, 0, 0);
    int* num_of_primes = (int*)shmat(shmid_4_num_of_primes, 0, 0);
    
    // check if we reached MAX_NUM_OF_PRIMES
    if (*num_of_primes + process_num_of_primes >= MAX_NUM_OF_PRIMES){
      shmdt(primes);
      shmdt(num_of_primes);
      free(process_primes);
      process_primes = NULL;
      return EXIT_FAILURE;
    }

    // Copy prime numbers that is calculated in workers to shared memory 
    for (int i = 0; i < process_num_of_primes; i++)
      primes[(*num_of_primes)++] = process_primes[i];


    //  detach the shared memory segment from the address
    // space of the calling process(child)
    shmdt(primes);
    shmdt(num_of_primes);

    // give resources back to system
    free(process_primes);
    process_primes = NULL;

    printf("Slave %d: Done.\n", process_order);
    return EXIT_SUCCESS;
  }
  return EXIT_SUCCESS;
}
