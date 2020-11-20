#include "process.h"



int create_process(Process* process, void(*function)(Process* process)){
    int pipe1[2];   /* From parent to child */
    int pipe2[2];   /* From child to parent */
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
    else if (process->pid == 0)
    {
        process->fp_input   = fdopen(pipe1[P_READ], "r");
        process->fp_output = fdopen(pipe2[P_WRITE], "w");
        close(pipe1[P_WRITE]);
        close(pipe2[P_READ]);
        /* Reads standard input from parent; writes standard output to parent */
        function(process);
        exit(0);
    }
    else{
        process->fp_input   = fdopen(pipe1[P_WRITE], "w");
        process->fp_output = fdopen(pipe2[P_READ], "r");
        close(pipe1[P_READ]);
        close(pipe2[P_WRITE]);
        return 0;
    }
}

void wait_for_process(size_t nprocess, Process *process){
    int pid;
    int status;

    while ((pid = waitpid(-1, &status, 0)) != -1)
    {
        for (size_t i = 0; i < nprocess; i++)
        {
            if (pid == process[i].pid)
                process[i].pid = -1;
        }
    }

    for (size_t i = 0; i < nprocess; i++)
    {
        if (process[i].pid != -1)
            printf("Processo %d morreu sem ser rastreado\n", (int)process[i].pid);
    }
}