#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int
main(int argc, char *argv[])
{
    if (argc != 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(1);//exit if the argument not equal to 1,
    }
    
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //slice off another process
    if (rc <0) {//if rc<0 exit the program
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(1);
    } else if (rc ==0) {//child(new procoess from fork())
        fprintf(stderr, "Child can't talk to strangers.\n"); printf("Hello, I am child (pid:%d)\n", (int)getpid()); sleep(1);
    } else {
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
               rc,wc, (int) getpid());
    }
    return 0;
}

