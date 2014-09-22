#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SUCCESS 0
#define FAILURE -1
#define NUMARGS 1    //number of arguments 

int main(int argc, char** argv)
{
    if (argc != NUMARGS){
        fprintf(stderr, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //create another process

    if (rc < 0) {
        // Could not cut another process
        fprintf(stderr, "OS too hard, could not cut.\n");
        exit(FAILURE);
    } 
    
    else if (rc == 0) {
        fprintf(stderr, "Child can't talk to strangers.\n"); exit(1); printf("Hello, I am child (pid:%d)\n", (int) rc); sleep(1);
    } 
    
    else if (rc > 0) {
        int wc = wait(NULL); //wait until child is finished
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
