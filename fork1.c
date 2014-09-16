#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE -1

int
main(int argc, char* argv[])
{
    if (argc > 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //fork off another process
    if (rc < 0) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) {
        fprintf(stderr, "Child can't talk to strangers. But doesn't listen anyhow.\n");  
        printf("Hello, I am child (pid:%d)\n", (int)getpid()); 
        sleep(1);
    } else if (rc > 0) {
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child (pid:%d) alone, I am its guardian (pid:%d)\n",
            wc, getpid());
    }
    return SUCCESS;
}
