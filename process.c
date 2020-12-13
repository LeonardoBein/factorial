#include "process.h"


/**
 * Função cria uma thread
**/

int create_thread(Thread* thread, void*(*function)(void* arg), void* args){
    return pthread_create(&thread->uuid, NULL, function, args);
}

/**
 * Função espera o termino das thread
**/

void wait_for_threads(int nthreads, Thread *threads){
    for (int i = 0; i < nthreads; i++){
        pthread_join(threads[i].uuid, NULL);
    }
}

/**
 * Função cria um novo processo (filho), usando o metodo fork.
**/

int create_process(Process* process, void(*function)(Process* process)){
    int pipe1[2];   /* De pai para filho */
    int pipe2[2];   /* De filho para pai */
    if (pipe(pipe1) != 0)
        return -1;
    if (pipe(pipe2) != 0)
    {
        close(pipe1[P_READ]);
        close(pipe1[P_WRITE]);
        return -1;
    }
    if ((process->pid = fork()) < 0)
    {
        close(pipe1[P_READ]);
        close(pipe1[P_WRITE]);
        close(pipe2[P_READ]);
        close(pipe2[P_WRITE]);
        return -1;
    }
    else if (process->pid == 0) // Filho
    {
        process->fp_input  = pipe1[P_READ];
        process->fp_output = pipe2[P_WRITE];
        close(pipe1[P_WRITE]);
        close(pipe2[P_READ]);

        function(process);
        exit(0);
    }
    else{ // Pai
        process->fp_input  = pipe1[P_WRITE];
        process->fp_output = pipe2[P_READ];
        close(pipe1[P_READ]);
        close(pipe2[P_WRITE]);
        return 0;
    }
}

/**
 * Função espera o termino dos processos (filhos) iniciados
**/

void wait_for_process(int nprocess, Process *process){
    int pid;
    int status;

    while ((pid = waitpid(-1, &status, 0)) != -1)
    {
        for (int i = 0; i < nprocess; i++)
        {
            if (pid == process[i].pid)
                process[i].pid = -1;
        }
    }
}