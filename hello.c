#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SUCCESS  0 //changed from 1 to 0
#define FAILURE -1 //changed from 0 to -1

int
main(int argc, char *argv[])  //pass in two parameters
{
  if (argc == 0) { //when argc equals 0, exit program.
    fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
    exit(FAILURE);
  }

  printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
  int rc = fork(); //slice off another process
  if (rc == -1) { //fork() returns -1, exit with error message.
    // Could not cut another process
    fprintf(stdout, "OS too hard, could not cut.\n");
    exit(FAILURE);
  } else if (rc == 0) { //when fork() returns 0, exit with success message.
    fprintf(stderr, "Child can't talk to strangers.\n"); exit(1); printf("Hello, I am child (pid:%d)\n", (int) rc); sleep(1);
  } else { //when fork() returns others nums, create new child 
    int wc = wait(NULL); //is child finished?
    printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	   getpid(), wc, (int) rc);
  }
  return SUCCESS;
}
