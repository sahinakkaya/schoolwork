#include <stdio.h>
#include <sys/wait.h>  // wait
#include <unistd.h>    // fork

void print_info_about_process(int child_pids[], int num_of_childs, int level) {
  printf("<%d, ", getpid());
  if (num_of_childs) {
    printf("[");
    for (int i = 0; i < num_of_childs; i++) {
      if (i != 0) {
        printf(", ");
      }
      printf("%d", child_pids[i]);
    }
    printf("]");
  } else {
    printf("None");
  }
  printf(", %d>\n", level);
}

int main() {
  int level1_childs_pid[3] = {0};
  int child = fork();
  if (child == 0) {
    // 2
    int level2_childs_pid[2] = {0};
    child = fork();
    if (child == 0) {
      // 3
      child = fork();
      if (child == 0) {
        // 4
      } else {
        // 3
      }
      // 3,4
    } else {
      level2_childs_pid[0] = child;
      // 2
      child = fork();
      if (child == 0) {
        // 5
      } else {
        level2_childs_pid[1] = child;
        print_info_about_process(level2_childs_pid, 2, 2);
      }
      // 2, 5
    }
    // 2, 3, 4, 5
  } else {
    level1_childs_pid[0] = child;
    child = fork();
    if (child == 0) {
      // 6
      int level2_childs_pid[2] = {0};
      child = fork();
      if (child == 0) {
        // 7
        child = fork();
        if (child == 0) {
          // 8
        } else {
          // 7
        }
        // 7
      } else {
        // 6
        level2_childs_pid[0] = child;
        child = fork();
        if (child == 0) {
          // 9
        } else {
          // 6
          level2_childs_pid[1] = child;
          print_info_about_process(level2_childs_pid, 2, 2);
        }
        // 6
      }

    } else {
      // 1
      level1_childs_pid[1] = child;
      child = fork();
      if (child == 0) {
        // 10
        int level2_childs_pid[2] = {0};
        child = fork();
        if (child == 0) {
          // 11
          child = fork();
          if (child == 0) {
            // 12
          }
          // 11, 12
        } else {
          // 10
          level2_childs_pid[0] = child;
          child = fork();
          if (child == 0) {
            // 13
          } else {
            level2_childs_pid[1] = child;
            print_info_about_process(level2_childs_pid, 2, 2);
          }
          // 10 ,13
        }
        // 10, 11, 12, 13
      } else {
        level1_childs_pid[2] = child;
        print_info_about_process(level1_childs_pid, 3, 1);
      }
      // 1, 10, 11, 12, 13
    }
  }

  return 0;
}