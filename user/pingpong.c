#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int fork1(void) {
    int pid;

    pid = fork();
    if(pid == -1) {
        fprintf(2, "fork error\n");
        exit(1);
    }
    return pid;
}

int main(int argc, char *argv[]) {
    int p[2];
    if (pipe(p) < 0) {
        fprintf(2, "create pipe buffer error\n");
        exit(1);
    }
    
    char buf[3];
    if (fork1() != 0) {
        write(p[1], " ", 1);
        wait(0);
        read(p[0], buf, sizeof(buf));
        fprintf(1, "%d: received pong\n", getpid());
    } else {
        read(p[0], buf, sizeof(buf));
        fprintf(1, "%d: received ping\n", getpid());
        write(p[1], " ", 1);
    }

    close(p[0]);
    close(p[1]);

    exit(0);
}