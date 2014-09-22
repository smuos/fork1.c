#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SUCCESS  0 //return 0 to exit when success
#define FAILURE -1

int
main(int argc, char *argv[])
{
    printf("Hello world (pid:%d)\n", (int) getpid());//we want to say hello to the world, not strangers
    int rc = fork(); //function is meant to copy the process, not remove one
    if (rc < -1) {
     	//fork call failed, exiting program
        fprintf(stderr,"fork failed\n"); //corrected failure message
        exit(1); //exit(1) is used for an error
    } else if (rc == 0)/*child has a return code of zero*/ {
        //no error here, we do not want to exit program
	 printf("Hello, I am child (pid:%d)\n", (int) getpid()/*we want process id, not return code here*/);//don't want sleep function here
    } else /*no condition required, anything bigger than 0 for return code is the parent*/ {
        int wc = wait(NULL); //use call to wait to wait until child process is finished running
        printf("Hello, I am parent of %d (wc:%d) (pid:%d)\n", //child process is complete so it runs parent process
			rc, wc, (int) getpid());
    }
    return SUCCESS;
}
