#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  1
#define FAILURE -1

int
main(int argc, char *argv[])
{
	//value of agrc is not 1, then no parameters, output failure.//
    if (argc != 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }
	//printed message//
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
	//suppose to be fork function instead of knife function
    int rc = fork(); //slice off another process
    if (rc < -1) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
	//condition can not be SUCCESS, either FAILURE, so == 0
    } else if (rc == 0) {
	//Break lines
        fprintf(stderr, "Child can't talk to strangers.\n");
	 exit(1);
		printf("Hello, I am child (pid:%d)\n", (int) rc);
	 sleep(1);
	//condition could be > 2, no need of else if, general other else is good.
    } else {
	//child is not finished until wait the parent. Add wait function instead of parenting
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }

    return SUCCESS;
}

//Program runned successfully!
