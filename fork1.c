#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  0
#define FAILURE -1

intmain()
{
    if (argc != 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //fork off another process
    if (rc == -1) {
        // Could not fork another process
        fprintf(stdout, "OS too salty, could not fork.\n");
        exit(FAILURE);
    } else if (rc == 1) {
        fprintf(stderr, "Child can't talk to strangers.\n");
	exit(FAILURE);
	printf("Hello, I am child (pid:%d)\n", (int) rc);
	sleep(1);
    } else if (rc == 2) {
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
