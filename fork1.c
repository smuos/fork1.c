#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//
#define SUCCESS  1
#define FAILURE -1

/**
Start of program

@param argc argument count
@param argv argument vector
@return an integer indicating success or failure.
*/
int main(int argc, const char** argv)
{
    // Check if program number of arguements is zero (0).
    // Note: the first argument in argv and included in argc count
    // is the executed command which called this program.
    // Therefore user arguments are all after the first argument.
    if (argc != 1) {
        // Not only the first argument, which is the executable command.
        fprintf(stdout, "Program %s takes no parameters.\n", argv[0]);
        exit(FAILURE);
    }

    // Main program prints message to console
    printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());

    // Fork and create a child process
    int rc = fork(); //slice off another process

    // Run different code based on if there was an error,
    // it is the parent, or is the child.
    if (rc < -1) {
        // Error: Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) {
        // Is child
        fprintf(stderr, "Child can't talk to strangers.\n");
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
        exit(1);
    } else if (rc > 0) {
        // Is Parent
        int wc = wait(NULL); //is child finished?
        printf("Please leave my child alone, I am %d (wc:%d) (pid:%d)\n",
	       getpid(), wc, (int) rc);
    }
    return SUCCESS;
}
