#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

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

int main(int argc, const char *argv[]) {

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

        countdown(result, argc, argv);
    }

    // Register signal handlers
    signal(SIGINT, handle_sigint);

    int i = 0;
    while (true) {
        printf("%02i:%02i:%02i", hours(i), minutes(i), seconds(i));
        fflush(stdout);
        sleep(1);
        i += 1;
        resetLine();
    }

    return 0;
}
