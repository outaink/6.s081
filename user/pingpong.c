#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv) {
    int pipe_p2c[2], pipe_c2p[2];

    // 创建管道，在数组中写入管道读端和写端的文件描述符，[0]是读取端，[1]是写入端
    pipe(pipe_p2c);
    pipe(pipe_c2p);

    char ball = '.';


    if (fork() != 0) {
        write(pipe_p2c[1], &ball, 1);
        close(pipe_p2c[1]);

        char buf;
        read(pipe_c2p[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        wait(0);
    } else {
        char buf;
        read(pipe_p2c[0], &buf, 1);
        printf("%d: received ping\n", getpid());

        write(pipe_c2p[1], &buf, 1);
        close(pipe_c2p[1]);
    }

    close(pipe_c2p[0]);
    close(pipe_p2c[0]);

    exit(0);
}