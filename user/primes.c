#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int pleft[2]) {
    // 从左邻居读取整数
    int p;
    read(pleft[0], &p, sizeof(p));
    if (p == -1) {
        exit(0);
    }
    printf("prime %d\n", p);  // 此时收到的肯定是质数

    // 创建一个新的管道
    int pright[2];
    pipe(pright);

    if (fork() == 0) {
        close(pright[1]);
        close(pleft[0]);
        sieve(pright); 
    } else {
        close(pright[0]);

        // 从左邻居接收数字
        int buf;
        while(read(pleft[0], &buf, sizeof(buf)) && buf != -1) {
            if (buf % p != 0) {
                write(pright[1], &buf, sizeof(buf));
            }
        }

        // 如果左邻居给来 -1 也要告诉右邻居 -1
        buf = -1;
        write(pright[1], &buf, sizeof(buf));
        wait(0);
        exit(0);
    }
}

int main(int argc, char **argv) {
    // 创建初始管道
    int input_pipe[2];
    pipe(input_pipe);

    if (fork() == 0) { // 右邻居
        close(input_pipe[1]);  // 右邻居不需要写端，关掉
        sieve(input_pipe);  // 调用筛选函数
        exit(0);
    } else {            // 父进程
        close(input_pipe[0]); // 父进程只需要用到写端，关掉自己的读端
        int i;
        for (i = 2; i <= 35; i++) {
            write(input_pipe[1], &i, sizeof(i)); // 向管道中写入2～35的整数
        }
        // 写入结束标志
        i = -1;
        write(input_pipe[1], &i, sizeof(i));
    }

    wait(0);
    // 这里等待子进程的子进程结束，只能等待直接子进程，无法等待间接子进程
    exit(0);
}