#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(void){
    // Fix: Leave brackets empty [] so the compiler automatically 
    // allocates 5 bytes (including the null terminator)
    char one[] = "5918233"; 
    char sec[20] = "/proc/";    
    char final[20];
    
    int len = strlen(one);
    int len2 = strlen(sec);
    
    // This will now safely copy "/proc/1234/" into 'final'
    int a = snprintf(final, 20, "/proc/%s/", one);
    
    DIR *str = opendir(final);
    if (str == NULL){
        printf("cia\n");
    }

    printf("daidwa\n");

    return 0;
}

