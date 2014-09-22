#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE -1

int main(int argc, char* argv[])
{
    if (argc != 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }
	
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //create another process
    if (rc == -1) {
        // Could not successfully create another process
        fprintf(stdout, "error creating new process.\n");
        exit(0);
    } else if (rc == 0) { 
	printf("Hello, I am child (pid:%d)\n", (int) rc);
	sleep(1);
    } else if (rc > 0) {
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
