#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define TIMEOUT 2 

bool timeoutOccurred = false;

void sendData(int packet) {
    printf("Sending packet %d\n", packet);
    sleep(1); // Simulate the time taken to send data
}

bool receiveAck() {
    // Simulate random ACK reception or loss
    if (rand() % 2 == 0) {
        printf("ACK received for packet\n");
        return true;
    } else {
        printf("ACK lost for packet\n");
        return false;
    }
}

void handleTimeout(int sig) {
    timeoutOccurred = true;
    printf("Timeout occurred. Resending packet\n");
}

void startTimer() {
    struct itimerval timer;
    timer.it_value.tv_sec = TIMEOUT;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
}

void stopTimer() {
    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // User input for the number of packets to transmit
    int numPackets;
    printf("Enter the number of packets to transmit: ");
    scanf("%d", &numPackets);

    signal(SIGALRM, handleTimeout); // Set up the signal handler for the timeout

    int base = 0; // Base of the window
    int nextSeqNum = 0; // Next sequence number

    while (base < numPackets) {
        if (nextSeqNum == base) {
            sendData(nextSeqNum);
            startTimer();
            nextSeqNum++;
        }

        if (receiveAck()) {
            base++;
            stopTimer();
        } else {
            timeoutOccurred = true;
        }

        if (timeoutOccurred) {
            timeoutOccurred = false;
            nextSeqNum = base;
        }
    }

    printf("All packets sent and acknowledged successfully.\n");

    return 0;
}
