#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char command[100];

    printf("Enter a command: ");
    scanf("%s", command);

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Child PID: %d\n", getpid());
        execlp(command, command, NULL);
        perror("Execution failed");
    }
    else
    {
        printf("Parent PID: %d\n", getpid());
        wait(NULL);
    }

    return 0;
}
