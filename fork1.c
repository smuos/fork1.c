#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE -1

int
main(int argc, const char** argv)
{
    if (argc != 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //slice off another process
    if (rc < -1) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) {
        fprintf(stderr, "Child can't talk to strangers.\n");
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
        exit(1);
    } else if (rc > 0) {
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
