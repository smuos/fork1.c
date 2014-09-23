#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SUCCESS  0 //this two declration is used for the exit command
#define FAILURE  1 //and exit(0) stands for normal exit, no error VICE VERSA

int main(int argc, char *argv[])
{
    if (argc != 1) {// there must be one argument for the output file to run
	//if there is more than one argument that means any argument other than the first
	//one is parameter(s)
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);//exit(1) indicates error occurs
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    int rc = fork(); //slice off another process by fork
    if (rc < 0) {//less than 0,or equal -1
        // Could not cut another process

        fprintf(stderr, "OS too hard, could not cut.\n");//the error is printing to the err log  not the screen
	printf("OS too hard, could not cut.\n");//stdout is the screen and a simple printf can do the job

        exit(FAILURE);//exit(1) indicates error occurs

    } else if (rc == 0) {//this is children

       /* fprintf(stderr, "Child can't talk to strangers.\n");
	exit(1);//the following two line will not be run, because the program is exited
	if the purpose of the above two line is to modify the process to do some other tasks, a exec() should be call
	instead of exit()
*/
	printf("Hello, I am child (pid:%d)\n", (int) rc);
	sleep(1);//wait for one second

    } else if (rc > 0) {
        int wc = wait(NULL); //check if child finished?
				 //the correct command is wait instead of parenting
				 //although it makes more sense
        printf("Please leave my child alone, I am %d (wc:%d) and my child pid is%d\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;// return 0 normal exit
}
