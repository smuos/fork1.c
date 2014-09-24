#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE -1

int
main(int argc, char *argv[])
{
    if (argc >= 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }
   
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //slice off another process
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(0);
    } else if (rc == 0) { // child (new process)
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
    } else if (rc == 2) {
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
