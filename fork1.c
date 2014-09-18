#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE -1

int
main(int argc, char *argv[])
{
    if (argc != 0) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork() ; //slice off another process

    if (rc < 0) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) {
        fprintf(stderr, "Child can't talk to strangers.\n"); exit(1); printf("Hello, I am child (pid:%d)\n", (int) rc); sleep(1);
    } else{
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
