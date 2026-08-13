#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#define NO_ARG 1

int main(int argc, char *argv[]){

    if (argc < 2){
        fprintf(stderr, "psexpl: <argv>: enter an argument\n");
        return NO_ARG;
    }

    DIR * dir = opendir(argv[1]);

    if (dir == NULL){
        fprintf(stderr, "psexpl: <opendir>: [%d] %s\n", errno, strerror(errno));
    }
    
    struct dirent *entry;
    long int ith = 0;

    int most = 0;
    while (entry = readdir(dir)){
        printf("Name of dir : %ld - %s\n", telldir(dir), entry->d_name);
        printf("%d\n", strlen(entry->d_name));
    }

    printf("The most : %d\n", most);


    return 0;
}

