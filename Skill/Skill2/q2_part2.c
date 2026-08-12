#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main() {
    char buffer[100];
    int position;
    char ch;

    struct termios oldt, newt;

    /* Get current terminal settings */
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    /* Enable character-by-character input */
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (1) {
        position = 0;

        printf("> ");
        fflush(stdout);

        while (1) {
            ch = getchar();

            /* Enter key */
            if (ch == '\n') {
                buffer[position] = '\0';
                break;
            }

            /* Backspace key */
            else if (ch == 127 || ch == 8) {
                if (position > 0) {
                    position--;
                    printf("\b \b");
                    fflush(stdout);
                }
            }

            /* Normal character */
            else {
                if (position < 99) {
                    buffer[position] = ch;
                    position++;

                    printf("%c", ch);
                    fflush(stdout);
                }
            }
        }

        printf("\n");

        /* Exit command */
        if (strcmp(buffer, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        /* Display entered command */
        printf("You entered: %s\n", buffer);
    }

    /* Restore normal terminal settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
