#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "please give sleep time as input\n");
        exit(1);
    }

    int sleepTime = atoi(argv[1]);
    if (sleepTime == 0) {
        fprintf(2, "please enter legal number as input\n");
        exit(1);
    }
    
    sleep(sleepTime);

    exit(0);
}
