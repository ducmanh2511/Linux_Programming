#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("[Con] PID = %d, ket thuc ngay\n", getpid());
        exit(42);
    }
    printf("[Cha] PID = %d, con la %d. Khong goi wait(). Ngu 60 giay...\n", getpid(), pid);
    int status;

    if (waitpid(pid, &status, 0) == -1) {
    perror("waitpid");
    return 1;
    }

    if (WIFEXITED(status)) {
    printf("[Cha] Exit code cua con: %d\n", WEXITSTATUS(status));
     }


    sleep(60);
    return 0;
}
