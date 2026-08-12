#include <stdio.h>
#include <string.h>

int main() {
    char input[100];

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        printf("You entered: %s\n", input);
    }

    return 0;
}
