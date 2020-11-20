#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


enum { P_READ, P_WRITE };   /* Read, write descriptor of a pipe */

typedef struct
{
    FILE *fp_input;
    FILE *fp_output;
    pid_t pid;
} Process;

int create_process(Process* process, void(*function)(Process* process));
void wait_for_process(size_t nprocess, Process *process);