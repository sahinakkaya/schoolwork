//
// Created by sahin on 24/04/2020.
//
#include <unistd.h>  // fork
#include "math.h"
#include "stdio.h"   // printf, sscanf
#include "stdlib.h"  // EXIT_FAILURE, EXIT_SUCCESS

#define and &&
#define or ||

int main(int argc, char** argv) {
  if (argc != 5) {
    printf("Please supply correct number of arguments.\n");
    return EXIT_FAILURE;
  }

  int lower_bound, upper_bound, np, nt;
  sscanf(argv[1], "%d", &lower_bound);
  sscanf(argv[2], "%d", &upper_bound);
  sscanf(argv[3], "%d", &np);
  sscanf(argv[4], "%d", &nt);

  int* processes = malloc(np * sizeof(int));
  for (int i = 0; i < np; i++) {
    int child = fork();
    if (child == 0) {
      int interval = ceil((upper_bound - lower_bound) / (float)np);
      int interval_s = lower_bound + interval * i;
      int interval_e = lower_bound + interval * (i + 1) - 1;
      if (i + 1 == np and interval_e + 1 == upper_bound)
        interval_e = upper_bound;
      printf("created child %d. responsible from %d to %d. pid: %d\n", i,
             interval_s, interval_e, getpid());
      break;
    } else {
      processes[i] = child;
      if (i + 1 == np) {
        for (int i = 0; i < np; i++) {
          printf("pid of child %d is %d\n", i, processes[i]);
        }
        free(processes);
      }
    }
  }

  return EXIT_SUCCESS;
}