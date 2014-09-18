#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  0
#define FAILURE  1

int
main(int argc, char *argv[])
{
  //if there are paraments when user run, give a warning
    if (argc != 0) {
      //Print out the warning
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
	//exit the program
        exit(FAILURE);
    }

    //If user run the program sucessfully, print out welcome message with pid
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    //use fork() to a new process named rc
    int rc = fork(); 
    //fork failed; exit
    if (rc < -1) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
	//exit the program
        exit(FAILURE);
	//	
    } else if (rc == 0) {
        fprintf(stderr, "Child can't talk to strangers.\n");
	exit(FAILURE);
	printf("Hello, I am child (pid:%d)\n", (int) rc);
	sleep(1);
    } else if (rc > 0) {
        int wc = wait(NULL); //wait for child process
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    //return 1 to show program runs sucessfully
    return SUCCESS;
}
