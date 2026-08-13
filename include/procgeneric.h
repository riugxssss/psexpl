#ifndef PROC_STR_H
#define PROC_STR_H

#include <sys/types.h>


typedef struct process_info {
    pid_t pid;
    pid_t ppid;
    char *name;
    char *state;
    mode_t umask;
    int threads;
}proc_var;

proc_var *generic_info(const char *pid);
void free_struct(proc_var *proc_struct);


#endif
