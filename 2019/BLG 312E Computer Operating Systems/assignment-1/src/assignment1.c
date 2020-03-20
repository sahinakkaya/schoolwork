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
  for (int i = 0; i < 3; i++) {
    int child = fork();
    int level2_childs_pid[2] = {0};
    if (child == 0) {
      // 2
      child = fork();
      if (child == 0) {
        // 3
        child = fork();
        if (child == 0) {
          // 4
          print_info_about_process(NULL, 0, 4);
        } else {
          int level3_childs_pid[1] = {child};
          print_info_about_process(level3_childs_pid, 1, 3);
        }
        // 3,4
      } else {
        level2_childs_pid[0] = child;
        // 2
        child = fork();
        if (child == 0) {
          // 5
          print_info_about_process(NULL, 0, 3);
        } else {
          level2_childs_pid[1] = child;
          print_info_about_process(level2_childs_pid, 2, 2);
        }
        // 2, 5
      }
      // 2, 3, 4, 5
      break;
    } else {
      level1_childs_pid[i] = child;
      if (i == 2) print_info_about_process(level1_childs_pid, 3, 1);
    }
  }

  return 0;
}