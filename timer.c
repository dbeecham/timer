#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

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

int main(int argc, const char *argv[]) {
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
