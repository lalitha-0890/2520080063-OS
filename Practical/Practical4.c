#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t child1, child2, child3;
    int status;

    // Create Child 1
    child1 = fork();

    if (child1 < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (child1 == 0)
    {
        printf("Child 1: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);
        printf("Child 1 completed.\n");
        exit(0);
    }

    // Create Child 2
    child2 = fork();

    if (child2 < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (child2 == 0)
    {
        printf("Child 2: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(4);
        printf("Child 2 completed.\n");
        exit(0);
    }

    // Create Child 3
    child3 = fork();

    if (child3 < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (child3 == 0)
    {
        printf("Child 3: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(6);
        printf("Child 3 completed.\n");
        exit(0);
    }

    // Parent process
    printf("\nParent PID = %d\n", getpid());
    printf("Created children: %d, %d, %d\n", child1, child2, child3);

    // Using wait()
    printf("\nParent using wait()...\n");

    pid_t finished = wait(&status);

    printf("wait(): Child with PID %d completed.\n", finished);

    // Using waitpid()
    printf("\nParent using waitpid() for Child 3...\n");

    waitpid(child3, &status, 0);

    printf("waitpid(): Child 3 with PID %d completed.\n", child3);

    // Wait for remaining children
    wait(NULL);

    printf("\nAll child processes completed.\n");

    return 0;
}
