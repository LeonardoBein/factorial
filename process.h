#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h> 

enum { P_READ, P_WRITE };   /* Read, write descriptor of a pipe */

typedef struct
{
    int fp_input;
    int fp_output;
    pid_t pid;
} Process;

typedef struct
{
    pthread_t uuid;
    void* input;
    void* output;
} Thread;


int create_thread(Thread* thread, void*(*function)(void* arg), void* args);
void wait_for_threads(int nthreads, Thread *threads);
 
int create_process(Process* process, void(*function)(Process* process));
void wait_for_process(int nprocess, Process *process);