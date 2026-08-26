#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buffer[100];

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid > 0)
    {
        // Parent - Producer
        close(fd[0]);

        char message[] = "Hello from Producer! This data is sent through the pipe.";

        clock_t start = clock();

        write(fd[1], message, strlen(message) + 1);

        clock_t end = clock();

        close(fd[1]);

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Parent (Producer): Data sent successfully.\n");
        printf("Communication time: %f seconds\n", time_taken);

        wait(NULL);
    }
    else
    {
        // Child - Consumer
        close(fd[1]);

        read(fd[0], buffer, sizeof(buffer));

        printf("Child (Consumer): Data received: %s\n", buffer);

        close(fd[0]);
    }

    return 0;
}
