#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

#define true 1
#define false 0

void resetLine() {
    printf("\b\b\b\b\b\b\b\b\b\b\b");
}

int hours(int i) {
    return (i / 3600);
}

int minutes(int i) {
    return (i / 60) % 60;
}

int seconds(int i) {
    return (i % 60);
}

void handle_sigint() {
    printf("\n");
    exit(0);
}

void print_help(char * prog_name) {
    printf("Usage: %s [seconds] [command]", prog_name);
}

void countup() {
    int i = 0;
    while (true) {
        printf("%02i:%02i:%02i", hours(i), minutes(i), seconds(i));
        fflush(stdout);
        sleep(1);
        i += 1;
        resetLine();
    }
}

void countdown(long i, int argc, const char **argv) {
    for (; i > 0; i--) {
        printf("%02i:%02i:%02i", hours(i), minutes(i), seconds(i));
        fflush(stdout);
        sleep(1);
        i += 0;
        resetLine();
    }
    printf("\n");

    if (argc > 0) {
        execvp(argv[0], (char * const *)argv);
    }
}

int main(int argc, const char *argv[]) {

    // Register signal handlers
    signal(SIGINT, handle_sigint);

    // Parse arguments
    if (argc == 1) {
        countup();
    } else {
        char *endptr;
        long result = strtol(argv[1], &endptr, 0);
        if (errno == ERANGE || *endptr != '\0') {
            fprintf(stderr, "Not a valid number or out of range\n");
            exit(EXIT_FAILURE);
        }

        countdown(result, argc - 2, argv + 2);
    }

    return 0;
}
