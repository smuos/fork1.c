//Kashif, A00369617

//include files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE -1

int main(int argc, char* argv [])
{
    if (argc != 1) { //if there is no command line parameter set
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //system call to create a copy of itself
    if (rc < 0) {
        // Could not cut another process. Creation of child was unsuccessful
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) { //fork returns zero to the newly created child process
        fprintf(stderr, "Child can't talk to strangers.\n");
        printf("Hello, I am child (pid:%d)\n", (int) getpid()); 
        sleep(1);
    } else if (rc > 0) { //fork returns a positive value
        int wc = wait(NULL); //wait until the child of the process terminates
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
