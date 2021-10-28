#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void runNewPrimeProc(int p[]) {
    int x, y;
    int newP[2];

    close(p[1]);
    if (read(p[0], &x, sizeof(int)) != 0) {
        fprintf(1, "prime %d\n", x);
        int prime = x;
        pipe(newP);
        int pid = fork();
        if (pid != 0) {
            close(newP[0]);
            while (read(p[0], &y, sizeof(int)) != 0) {
                if (y % prime != 0) {
                    write(newP[1], &y, sizeof(int));
                }
            }
            close(p[0]);
            close(newP[1]);
            wait(0);
        } else {
            runNewPrimeProc(newP);
        }
    }

    exit(0);
}

int main() {
    int p[2];
    pipe(p);

    int pid = fork();

    if (pid != 0) {
        close(p[0]);
        for (int i = 2; i <= 35; ++i) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    } else {
        runNewPrimeProc(p);
    }

    exit(0);
}