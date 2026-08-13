#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "../include/infogeneric.h"
#include "../include/support.h"

int main(int argc, char *argv[]){

    const char *pid = (const char *)argv[1];

    int valid = check_valid(pid);

    if (valid == INVALID_PID){
        printf("inv\n");
        return -1;
    }else if (valid == VALID_PID) {
        printf("val\n");
    }

    char *t = "comm";

    char *path = build_str(pid, t);

    printf("%s\n", path);

    int fd = open(path, O_RDONLY);

    char buf[64];
    ssize_t b_read = read(fd, buf, sizeof(buf) - 1);
    if (b_read == -1){
        fprintf(stderr, "error\n");
    }
    buf[b_read] = '\0';

    printf("[%zd] %s\n",b_read, buf);

    free_str(path);


    close(fd);
    return 0;
}
