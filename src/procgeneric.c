#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

#include "../include/infogeneric.h"
#include "../include/support.h"
#include "../include/procgeneric.h"


/*Initializing the process struct and the fields*/

proc_var *init_struct(){
    //Mallocating the entire struct with a return check
    proc_var *new_struct = malloc(sizeof(*new_struct));
    if (new_struct == NULL){
        fprintf(stderr, "psexpl: <malloc> [%d] %s\n", errno, strerror(errno));
        return NULL;
    }
   
    new_struct->name = (char *)malloc(sizeof(char) * 32); 
    if (new_struct->name == NULL){
        fprintf(stderr, "psexpl: <malloc> [%d] %s\n", errno, strerror(errno));
        return NULL;
    }

    new_struct->state = (char *)malloc(sizeof(char) * 32);
    if (new_struct->state == NULL) {
        fprintf(stderr, "psexpl: <malloc> [%d] %s\n", errno, strerror(errno));
        return NULL;
    }
 
    //Readbility init
    new_struct->pid = 0;
    new_struct->ppid = 0;
    new_struct->umask = 0;
    new_struct->threads = 0;

    return new_struct;
}
/*This function get's all the info of our process with the help of build str
 * function, it builds out the right path to the /proc/pid/status
 * */


proc_var *generic_info(const char *pid){
    
    //Calling the init var
    proc_var *new_struct = init_struct();
    if (new_struct == NULL) exit(errno);

    //Getting the pathname from the build_str
    char *pathname = build_str (pid, "status");

    //Opening the file with a FILE * stream to use fgets.
    FILE *fop = fopen(pathname, "r");
    if (fop == NULL){
        fprintf(stderr, "psexpl: <fopen> [%d] %s\n", errno, strerror(errno));
        return NULL;
    }

    //Declaration of the actual values
    char line[64];
    char *value = NULL;
    char fieldproc[64] = {0};

    while (fgets(line, sizeof(line), fop) != NULL){
        
        //Field string
        size_t b = strcspn(line, ":");
        strncpy(fieldproc, line, b);
        fieldproc[b] = '\0';    
    
        //String value
        value = strchr(line, ':');

        if (value != NULL){
            value++;
            while (isspace(*value)){
                value++;
            }
        }else continue;
    
        value[strcspn(value, "\n")] = '\0'; 


        int str_l = strlen(value);
        
            //Each case for field
        if (strcmp(fieldproc, "Name") == 0){
            strncpy(new_struct->name, value, str_l + 1);
            
        }else if (strcmp(fieldproc, "Umask") == 0){
            new_struct->umask = strtol(value, NULL, 8);
        
        }else if (strcmp(fieldproc, "State") == 0){
            strncpy(new_struct->state, value, str_l + 1);

        }else if (strcmp(fieldproc, "Pid") == 0){
            new_struct->pid = strtol(value, NULL, 10);
        }else if (strcmp(fieldproc, "PPid") == 0){
            new_struct->ppid = strtol(value, NULL, 10);
        }else if (strcmp(fieldproc, "Threads") == 0){
            new_struct->threads = strtol(value, NULL, 10);
            
        }else {
            continue;
        }
        
    }
    
    free_str(pathname);
    fclose(fop);
    return new_struct;

}

void free_struct(proc_var *proc_struct){
    if (proc_struct == NULL){
        return;
    }
    free(proc_struct->state);
    free(proc_struct->name);
    free(proc_struct);
}

