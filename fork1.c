#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SUCCESS  0
#define FAILURE -1

int main(int argc, char* argv[])
{
    // If user has entered command line parameters they are doing it wrong
    if (argc > 1) {
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    // Else run program
    // Tell the user our process ID (pid)
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
    // Fork off another process
    int rc = fork();
    // If return code < 0 something bad has happened.
    if (rc < 0) {
        // Could not fork another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) { // Return code of 0 means its a child process
        fprintf(stderr, "Child can't talk to strangers. But doesn't listen anyhow.\n");  
        printf("Hello, I am child (pid:%d)\n", (int)getpid()); 
        sleep(1);
    } else if (rc > 0) { // Return code is > 0 meaning parent process
        // Is child finished having a temper tantrum?
        int wc = wait(NULL);
        // Fend off attackers, by giving them the childs social insurance number...
        printf("Please leave my child (pid:%d) alone, I am its guardian (pid:%d)\n", wc, getpid());
    }
    // I can has cheezburger?
    return SUCCESS;
}
