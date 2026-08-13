#include <stdio.h>
#include <string.h>

int main(void){

    char a[] = "testing: aaaa";
    char b[32] = {0};

    size_t c = strcspn(a, ":");
    strncpy(b, a, c);
    
    b[c] = '\0';

    printf("%s\n", b);





    return 0;
}
