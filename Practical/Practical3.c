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
        printf("\n--- Child Process ---\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());
        printf("Child is sleeping for 60 seconds...\n");

        sleep(60);

        printf("Child process terminating...\n");
    }
    else
    {
        // Parent process
        printf("\n--- Parent Process ---\n");
        printf("PID  : %d\n", getpid());
        printf("PPID : %d\n", getppid());
        printf("Parent is waiting for child...\n");

        wait(NULL);

        printf("Child process completed.\n");
        printf("Parent process terminating...\n");
    }

    return 0;
}
