#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SUCCESS  1
#define FAILURE -1

int
main(int argc, char *argv[])
{
    // If the program takes any paraments, print out a message
    if (argc != 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);  // exit the program (failure)
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    
    int rc = fork();  // slice off another process
    
    // If fork failed, exit the program (failure)
    if (rc < 0) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) {  // when rc is child
        fprintf(stderr, "Child can't talk to strangers.\n");
        exit(1);  // exit (success)
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
        sleep(1);  // sleep for 1 second
    } else {  // when rc is parent
        int wc = wait(NULL);  //wait for child finished
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       (int) getpid(), wc, (int) rc);
    }
    
    return SUCCESS;  // run successfully
}
