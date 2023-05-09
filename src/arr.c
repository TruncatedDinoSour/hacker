#define _XOPEN_SOURCE 500

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int main(const int argc, char **argv) {
    static int fd;
    static off_t sz;
    static char *buf, *old;

    if (argc < 2) {
        fputs("converts files into c arrays, no files supplied\n", stderr);
        return 0;
    }

    putchar('{');

    while (*++argv) {
        if ((fd = open(*argv, O_RDONLY)) == -1)
            continue;

        sz = lseek(fd, 0, SEEK_END) + 1;
        lseek(fd, 0, SEEK_SET);
        buf = mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);

        close(fd);

        old = buf;

        while (*buf)
            printf("%d,", *buf++);

        munmap(old, sz);
    }

    putchar('}');

    return 0;
}
