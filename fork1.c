#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE 0

int
main(int argc, char *argv[])
{
    // check the parameters and prints error message if
    // improper parameters are received
    if (argc == 0) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(1);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    //rc forks and creates a child process
    int rc = fork(); //slice off another process
    //can't create child process
    if (rc < 0) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(1);
    //check if it is child
    } else if (rc == 0) {
        fprintf(stderr, "Child can't talk to strangers.\n");
	exit(1);
	printf("Hello, I am child (pid:%d)\n", (int) getpid());
	sleep(1);
    // It is parent
    } else {
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
