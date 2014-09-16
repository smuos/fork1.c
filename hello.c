#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SUCCESS  1
#define FAILURE -1

int
main(int argc, char *argv[])
{
    //check commandline arguments    
    if (argc != 1) {
        fprintf(stderr, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //slice off another process

    //error case
    if (rc < 0) {
        // Could not cut another process
        fprintf(stderr, "OS too hard, could not cut.\n");
        exit(0);

    //child process
    } else if (rc == 0) {
        //fprintf(stderr, "Child can't talk to strangers.\n");
        //exit(1);
        printf("Hello, I am child (pid:%d)\n", (int) rc);
        sleep(1);
    
    //parent process
    } else if (rc > 0) {
        int wc = wait(NULL); //is child finished?
        //printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       //getpid(), wc, (int) rc);
        printf("Hello, I am parent (wc:%d) (pid:%d)\n",
	       wc, (int) rc);
    }
    return SUCCESS;
}
