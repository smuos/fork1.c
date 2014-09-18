#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SUCCESS  0 //this two declration is used for the exit command
#define FAILURE -1 //and exit(0) stands for normal exit, no error

int
main(int argc, char *argv[])
{
    if (argc != 0) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //slice off another process by fork
    
    if (rc < 0) {//less than 0,or equal -1
        // Could not cut another process

        //fprintf(stdout, "OS too hard, could not cut.\n");
	printf("OS too hard, could not cut.\n");//stdout is the screen and a 
						//simple printf can do the job

	//unable to fork output to error file
	fprintf(stderr, "fail to fork\n");
        exit(0);//or exit(SUCCESS) for consistance

    } else if (rc == 0) {//this is children
        fprintf(stderr, "Child can't talk to strangers.\n"); 
	exit(1); 
	printf("Hello, I am child (pid:%d)\n", (int) rc); 
	sleep(1);
    } else if (rc > 0) {
        int wc = wait(NULL); //is child finished?
				  //the correct command is wait not parenting
				  //although it makes more sense
        printf("Please leave my child alone, I am %d (wc:%d) and my child pid is%d\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;//should be return 0 instead of success(1)
}
