#include <stdio.h>
#include <unistd.h>

int counter = 0;

void worker() {
    while (1) {
        counter++;
        sleep(1);
    }
}

int main() {
    printf("PID: %d\n", getpid());
    worker();
    return 0;
}
