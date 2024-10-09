#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t alarmFlag = 0;
time_t startTime;

void handleAlarm(int signum) {
    printf("Hello World!\n");
    alarmFlag = 1;
}

void handleSigint(int signum) {
    time_t endTime;
    time(&endTime);
    printf("\nTotal system time: %ld seconds\n", endTime - startTime);
    exit(0);
}

int main(int argc, char *argv[]) {
    time(&startTime); // Record start time

    signal(SIGALRM, handleAlarm); // Register handler for SIGALRM
    signal(SIGINT, handleSigint); // Register handler for SIGINT

    while (1) {
        alarm(1); // Set an alarm for every 1 second
        alarmFlag = 0; // Reset flag

        // Busy wait until the alarm signal is received
        while (!alarmFlag);
    }

    return 0;
}