#include <stdio.h>
#include <sys/wait.h>  //   wait
#include <unistd.h>    //fork

/*int main(int argc, char* argv[]) {
  int c = 0;
  int child = fork();
  c++;

  if (child == 0) {
    child = fork();
    c += 2;
    if (child) {
      c = c * 3;
      sleep(3);
      printf("pid: %d c: %d \n", getpid(), c);
    } else {
      sleep(2);
      printf("pid: %d c: %d \n", getpid(), c);

    }

  } else {
    c += 4;
    sleep(1);
    child = fork();
    if (child == 0) {
      sleep(4);
    }
    printf("pid: %d c: %d \n", getpid(), c);
  }
  sleep(5);
  return 0;
}*/


int main(){
    int child = fork();
    if (child == 0){
        // 2
        child = fork();
        if (child == 0){
            // 3
            child = fork();
            if (child == 0){
                //4
            }
            else{
                // 3
            }
            // 3,4
        } 
        else{
            // 2
            child = fork();
            if (child == 0){
                // 5
            }
            // 2, 5
        }
        // 2, 3, 4, 5
    }else{
        child = fork();
        if (child == 0){
            // 6
            child = fork();
            if (child == 0){
                // 7
                child = fork();
                if (child == 0){
                    // 8
                }
                else{
                    // 7
                }
                // 7
            }
            else{
                // 6
                child = fork();
                if (child == 0){
                    // 9
                }
                else{
                    // 6
                }
                // 6
            }


        } else{
            // 1
            child = fork();
            if (child == 0){
                // 10
                child = fork();
                if (child == 0){
                    // 11
                    child = fork();
                    if (child == 0){
                        // 12
                    }
                    // 11, 12
                }
                else {
                    // 10
                    child = fork();
                    if (child == 0){
                        // 13
                    }
                    // 10 ,13
                }
                // 10, 11, 12, 13
            }
            // 1, 10, 11, 12, 13
        }
        
    }

    return 0;

}