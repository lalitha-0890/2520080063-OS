#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        printf("Child is terminating...\n");
        exit(0);
    }
    else
    {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        wait(NULL);

        printf("Parent collected the child using wait().\n");
    }

    return 0;
}
