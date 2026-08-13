#include <stdio.h>
#include "../include/support.h"
#include "../include/procgeneric.h"
#include "../include/infogeneric.h"

/*The terminal string will contain the PID 
 * and the rest of the program gonna use that to
 * show many info about a process only starting by a PID*/

int main(int argc, char *argv[]){

    if (argc < 2){
        fprintf(stderr, "psexpl: usage: ./program <pid>\n");
        return NO_ARG;
    }
    
    if (check_valid(argv[1]) == INVALID_PID){
        fprintf(stderr, "psexpl: invalid <pid>\n");
        return INVALID_PID;
    }

    proc_var *proc_struct = generic_info(argv[1]);
    if (proc_struct == NULL){
        return 1;
    }   

    printf("Name: %s\n", proc_struct->name);
    printf("State: %s\n", proc_struct->state);   
    printf("PPid: %d\n", proc_struct->ppid); 
    printf("Umask: %04o\n", proc_struct->umask);
    printf("Pid: %d\n", proc_struct->pid);
    printf("Threads: %d\n", proc_struct->threads);

    free_struct(proc_struct);

    return 0;

}
