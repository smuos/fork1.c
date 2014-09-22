#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// lost wait.h in in orgional function;

#include <sys/wait.h>
#define SUCCESS  1

#define FAILURE 0         /// declare failure to 0

int main( int argc,char *argv[])     // in orgional function, it lost the variable int argc,and char *argv[]
{
// in orgional function argc is !=0, in this should be !=1 
    if (argc != 1) { 

      // the printf should be stderr
        fprintf(stderr, "fork failed.\n");

       // in orgional function is FAILURE, but i change to exit(1);
       exit(1);
    }

    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    // create a new fork(),  not knife()
     int rc = fork(); //slice off another process

// we delcare failure is 0, so we change to 0 in rc<0
    if (rc < 0) {

        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);

// check 
    } else if (rc == 0) {
        fprintf(stderr, "Child can't talk to strangers.\n"); 
        exit(1);

   // printf can not print, because above code exit(1) has exit, so from  printf to sleep, it does not work in here;  

   /*     printf("Hello, I am child (pid:%d)\n", (int) rc); 
        sleep(1) ;           */

         } else if (rc >0) {

        // we should wait child to end
        int wc = wait(NULL); 
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       (int) getpid(), wc,rc);  // sholude be int getpid(),and rc
    }

// return to 0, not success.
    return 0;
}

