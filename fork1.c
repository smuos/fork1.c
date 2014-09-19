#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  0
#define FAILURE  1

int
main(int argc, char *argv[])
{
  //If there are paraments when user run, give a warning
    if (argc != 1) {
      //Print out the warning
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
	//Exit the program(FAILURE)
        exit(FAILURE);
    }

    //If user run the program sucessfully, print out welcome message with pid
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    //Use fork() to a new process named rc
    int rc = fork(); 
    //Fork failed; exit(FAILURE)
    if (rc < 0) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
	//Exit the program(FAILURE)
        exit(FAILURE);
    //If rc is child process
    } else if (rc == 0) {
        //Print out corresponding output if rc is child process
        fprintf(stderr, "Child can't talk to strangers.\n");
	//Print out corresponding output if rc is child process
	printf("Hello, I am child (pid:%d)\n", (int) rc);
    //If rc is parent process
    } else if (rc > 0) {
        //Wait for child process
        int wc = wait(NULL); 
	//Print out corresponding output if rc is parent process
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    //return 1 to show program runs sucessfully
    return SUCCESS;
}
