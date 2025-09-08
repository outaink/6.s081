#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define END_MARKER -1
#define MAX_NUMBER 35

void sieve_process(int read_fd) {
    int prime;
    int bytes_read = read(read_fd, &prime, sizeof(prime));
    
    if (bytes_read == 0 || prime == END_MARKER) {
        close(read_fd);
        exit(0);
    }

    printf("prime %d\n", prime);

    int next_pipe[2];
    pipe(next_pipe);

    if (fork() == 0) {
        close(read_fd);
        close(next_pipe[1]);
        sieve_process(next_pipe[0]);
    } else {
        close(next_pipe[0]);

        int number;
        while (read(read_fd, &number, sizeof(number)) > 0) {
            if (number == END_MARKER) {
                write(next_pipe[1], &number, sizeof(number));
                break;
            }
            if (number % prime != 0) {
                write(next_pipe[1], &number, sizeof(number));
            }
        }

        close(read_fd);
        close(next_pipe[1]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char **argv) {
    int numbers_pipe[2];
    pipe(numbers_pipe);

    if (fork() == 0) {
        close(numbers_pipe[1]);
        sieve_process(numbers_pipe[0]);
    } else {
        close(numbers_pipe[0]);
        
        for (int i = 2; i <= MAX_NUMBER; i++) {
            write(numbers_pipe[1], &i, sizeof(i));
        }
        
        int end_marker = END_MARKER;
        write(numbers_pipe[1], &end_marker, sizeof(end_marker));
        close(numbers_pipe[1]);
        
        wait(0);
    }

    exit(0);
}