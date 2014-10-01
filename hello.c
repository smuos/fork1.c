#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  0
#define FAILURE -1

int main(int argc, char *argv[])
{
    // Check that the program hasn't received arguments
    if (argc != 1) {
        printf("Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }
    printf("Hi stranger! I'm (pid:%d)\n", getpid());
    int rc = fork(); //slice off another process
    
    if (rc < 0) {
        // Could not cut another process
        printf("OS too hard, could not cut.\n");
        exit(FAILURE);
    } else if (rc == 0) {
        // Child process
        fprintf(stderr, "Child can't talk to strangers.\n"); 
        printf("Hello, I am child (pid:%d)\n", getpid());
        sleep(1);
        exit(SUCCESS); 
    } else {
        // Parent process
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (My Child is:%d)\n",
	       getpid(), rc);
    }
    return SUCCESS;
}
