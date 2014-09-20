#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  0 //return 0 to exit when success
#define FAILURE -1

int
main()
{
    if (argc != 0) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hello world (pid:%d)\n", (int) getpid());//we want to say hello to the world, not strangers
    int rc = fork(); //function is meant to copy the process, not remove one
    if (rc < -1) {
     	//fork call failed, exiting program
        fprintf(stderr,"fork failed\n"); //corrected failure message
        exit(1); //exit(1) is used for an error
    } else if (rc == 1) {
        fprintf(stderr, "Child can't talk to strangers.\n"); exit(1); printf("Hello, I am child (pid:%d)\n", (int) rc); sleep(1);
    } else if (rc == 2) {
        int wc = parenting(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
