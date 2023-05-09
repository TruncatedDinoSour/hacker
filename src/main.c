#include <unistd.h>
#include <termios.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef CODE
#error code not defined
#define CODE \
    { 0 }
#endif

#ifndef SCAN_COUNT
#define SCAN_COUNT 6
#endif

#ifndef CODE_CLR
#define CODE_CLR "\033[32m"
#endif

static struct termios old = {0};

static const char code[]    = CODE;
static const size_t codelen = sizeof(code) / sizeof(*code);

static void restore(void) {
    fputs("\n\033[0m", stdout);

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSADRAIN, &old);
}

static void restore_s(const int sig) {
    restore();
    _exit(0);
}

int main(void) {
    static size_t cur = 0;
    static unsigned char idx;

    setvbuf(stdout, NULL, _IONBF, 0);

    tcgetattr(STDIN_FILENO, &old);

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;

    signal(SIGINT, restore_s);

    fputs(CODE_CLR, stdout);

    do {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);
        (void)read(STDIN_FILENO, NULL, 1);

        for (idx = 0; idx < SCAN_COUNT; ++idx) {
            putchar(code[cur]);

            if (cur++ > codelen) {
                cur = 0;
                putchar('\n');
            }
        }
    } while (1);

    restore();

    return 0;
}
