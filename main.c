#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "collatz.h"

#define REDC "\e[31m"
#define OFFC "\e[0m"

static void
usage(const char * progName) {
    assert(progName != NULL);
    fprintf(stderr, "Usage: %s <n>\n\nWhere n is an unsigned integer value.\n", progName);
}

typedef unsigned long ulong_t;

int main(int argc, char *argv[]) {
    char *ep=NULL;
    ulong_t n;
    ulong_t steps;

    puts("Collatz Conjecture tester");

    // There should only be one argument
    if (argc != 2) {
        usage(argv[0]);
        fputs( REDC "There should only be one argument\n" OFFC, stderr);
        return EXIT_FAILURE;
    }

    // Make sure arg is not negative
    for (char *c = argv[1]; *c; c++) {
        if (*c == '-') {
            usage(argv[0]);
            fprintf(stderr, REDC "error: n cannot be negative number\n" OFFC);
            return EXIT_FAILURE;
        }
        else if (*c >= 48 && *c <= 57)
            break;
    }

    n = strtoul(argv[1], &ep, 10);

    fprintf(stderr, "\x1b[1;30mn = %lu\x1b[0m\n", n );

    if (!n || errno || *ep) {
        usage(argv[0]);
        if (errno)
            fprintf(stderr, REDC "%s: %s\n" OFFC, argv[1], strerror(errno));
        else if (ep && *ep)
            fprintf(stderr, REDC "%s (I don't understand the part starting with \"%s...\")\n" OFFC, argv[1], ep);
        else if (!n)
            fprintf(stderr, REDC "%s (must be non-zero)\n" OFFC, argv[1]);
        else
            fputs(REDC "Unknown error: please open an issue at\n\nhttps://github.com/mojotx/collatz-c/issues\n" OFFC, stderr);

        return EXIT_FAILURE;
    }


    for (steps=0; n != 1; steps++) {
        printf("%lu ", n);
        n = collatz(n);
    }
    puts("1");
    printf("steps: %lu\n", steps);
}
