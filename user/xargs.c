#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     fprintf(2, "xargs command needs 2 parameters at least");
    //     exit(0);
    // }
    char *xCmd = argv[1], *argPoniter;
    char buf[512];
    argPoniter = buf;
    char *xCmdArg[MAXARG];
    xCmdArg[0] = xCmd;
    int argInd = 1, argCharInd = 0;
    for (int i = 2; i < argc; ++i) {
        xCmdArg[argInd++] = argv[i];
    }
    int initArgInd = argInd;
    char c;
    while (read(0, &c, sizeof(c)) == sizeof(c)) {
        // fprintf(1, "%c", c);
        if (c == 0) {
            continue;
        }
        if (c == '\n' || c == ' ') {
            *(argPoniter + argCharInd) = '\0';
            // fprintf(1, "%s\n", argPoniter);
            xCmdArg[argInd] = argPoniter;
            char arg[512];
            argPoniter = arg;
            argCharInd = 0;
            ++argInd;

            if (c == '\n') {
                xCmdArg[argInd] = 0;
                argInd = initArgInd;
                if (fork() == 0) {
                    // fprintf(1, "%s\n", xCmd);
                    exec(xCmd, xCmdArg);
                } else {
                    wait(0);
                }
            }
        } else {
            *(argPoniter + argCharInd) = c;
            ++argCharInd;
        }
    }
    exit(0);
}