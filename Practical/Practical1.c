#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char command[100];
    pid_t pid;

    printf("Enter a Linux command: ");
    scanf("%s", command);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child Process: PID = %d\n", getpid());

        execlp(command, command, (char *)NULL);

        // This executes only if execlp() fails
        printf("Command execution failed\n");
    }
    else
    {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());

        wait(NULL);

        printf("Child process completed\n");
    }

    return 0;
}
