#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i;
    pid_t pid;

    for (i = 0; i < 3; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            printf("Child %d PID: %d\n", i + 1, getpid());
            return 0;
        }
    }

    // Parent waits for all children
    for (i = 0; i < 3; i++)
    {
        wait(NULL);
    }

    printf("All children completed\n");

    return 0;
}
