#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include <stdlib.h>

#include "../include/support.h"

/*To check if the process really exist a lookup in 
 * the /proc directory will executed, every info about 
 * a process it is stored in there with the opportune
 * directory*/

int check_valid(const char *pid){

    //The buffer used to build the string
    char newbuf[32];

    //Building stream to check
    int writed_b = snprintf(newbuf, sizeof(newbuf), "/proc/%s", pid);    
    if (writed_b < 0){
        fprintf(stderr, "psexpl: <snprintf> error info:\nfile: %s\nline: %d\n", __FILE__, __LINE__);
        exit(-1);
    }
    
    /*If the opendir is equal to NULL, that means a directory with
     * the pid name does not exist, that mean's the pid is invalid
     * otherwise if the stream is not NULL the process exist*/

    //Open the directory
    DIR *stream = opendir(newbuf);
    if (stream == NULL){
        fprintf(stderr, "psexpl: <opendir> [%d] %s\n", errno, strerror(errno));
        return INVALID_PID;
    }
   
    closedir(stream);

    return VALID_PID;

}

/*This function's will return the correct path with the PID
 * in a mallocated string of 32 bytes
 *
 * The purpose of this it's only to simplify the string build
 * to the right path
 *
 * In case the malloc fail the program will raise a SIGABRT
 * causing an abnormal process termination.*/

char *build_str(const char *pid, const char *entry){
    
    char *new_str = malloc(32 * sizeof(char));

    if (new_str == NULL){
        fprintf(stderr, "psexpl: <malloc> [%d] %s\nat line: %d\nfile: %s\n",
                errno, strerror(errno), __LINE__, __FILE__);
        raise(SIGABRT);    
    }

    snprintf(new_str, 32, "/proc/%s/%s", pid, entry); 

    return new_str;
}

/*The only purpose of this function is to deallocate 
 * the block of memory used for this builded string*/

void free_str(const char *entry){
    if (entry == NULL){
        return; //We add this for make this more readable but calling free(NULL) is totally safe
    }
    free((void *)entry);
    return;
}
