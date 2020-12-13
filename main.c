#include "calc.h"
#include "process.h"
#include <string.h>

// ###############################
void my_process_factorial(Process *process);
void* my_thread_factorial(void* arg);
ArrayInt** distribute(int fatorialNumber, int processNumber);
int process_main(int factorialNumber, int numberProcess);
int thread_main(int factorialNumber, int numberProcess);
// ###############################



int main(int argc, char const *argv[]){
    int factorialNumber = 0;
    int error = 0;
    int numberProcess = 0;

    if (argc < 4){
        return -1;
    }

    factorialNumber = atoi(argv[2]);
    numberProcess = atoi(argv[3]);

    if (factorialNumber < 0){ return -1; }
    if (numberProcess < 0){ return -1; }

    if (strcmp("--thread", argv[1]) == 0){
        error = thread_main(factorialNumber, numberProcess);
    }else if (strcmp("--fork", argv[1]) == 0){
        error = process_main(factorialNumber, numberProcess);
    }else{
        return -1;
    }

    return error;
}





/**
 * Função a ser executado em paralelo (Process)
**/
void my_process_factorial(Process *process){
    int fatorialNumberInitial, fatorialNumberFinal;

    read(process->fp_input, &fatorialNumberInitial, sizeof(int));
    read(process->fp_input, &fatorialNumberFinal, sizeof(int));
    close(process->fp_input);
    process->fp_input = 0;
    

    if (fatorialNumberInitial < 0){
        fatorialNumberInitial = 1;
    }
    if (fatorialNumberFinal < 0){
        fatorialNumberFinal = 1;
    }
    if (fatorialNumberFinal < fatorialNumberInitial){
        int aux = fatorialNumberInitial;
        fatorialNumberInitial = fatorialNumberFinal;
        fatorialNumberFinal = aux; 
    }

    ArrayInt *ptr_res = factorial(fatorialNumberFinal, fatorialNumberInitial);
    write(process->fp_output, &ptr_res->size, sizeof(int));
    write(process->fp_output, ptr_res->data, sizeof(int)*ptr_res->size);
    close(process->fp_output);
    process->fp_output = 0;
}

/**
 * Função a ser executado em paralelo (Thread)
**/
void* my_thread_factorial(void* arg){
    Thread* thread = (Thread*)arg;
    int fatorialNumberInitial, fatorialNumberFinal;

    ArrayInt* input = (ArrayInt*)thread->input;

    fatorialNumberInitial = input->data[0];
    fatorialNumberFinal = input->data[1];

    if (fatorialNumberInitial < 0){
        fatorialNumberInitial = 1;
    }
    if (fatorialNumberFinal < 0){
        fatorialNumberFinal = 1;
    }
    if (fatorialNumberFinal < fatorialNumberInitial){
        int aux = fatorialNumberInitial;
        fatorialNumberInitial = fatorialNumberFinal;
        fatorialNumberFinal = aux; 
    }

    thread->output = (void *)factorial(fatorialNumberFinal, fatorialNumberInitial);

    return NULL;
}

/**
 * Função que distribui igualmente o trabalho dos n processos
**/
ArrayInt** distribute(int fatorialNumber, int processNumber){
    ArrayInt** array= NULL;

    array = (ArrayInt**)calloc(processNumber, sizeof(ArrayInt));

    int initial = 0;
    int step = fatorialNumber/processNumber;
    
    for (int i = 0; i < processNumber; i++){
        array[i] = createArray();
        array[i]->push(array[i], initial+1);
        
        if (initial + step < fatorialNumber && i + 1 >= processNumber){
            array[i]->push(array[i], fatorialNumber);
        }else{
            array[i]->push(array[i], initial + step);
        }        
        initial += step;
    }

    return array;
}

/**
 * Função que criar, administra e espera o retorno dos Processos, unindo os retornos 
 * em um resultado final. 
**/

int process_main(int factorialNumber, int numberProcess){
    ArrayInt** load_balance = distribute(factorialNumber, numberProcess);
    int err = 0;
    Process process[numberProcess];
    for (int i = 0; i < numberProcess; i++){
        err = create_process(&process[i], my_process_factorial);
        if (err != 0){
            printf("Não foi possível criar processo\n");
            return -1;
        }
        
    }

    for (int i = 0; i < numberProcess; i++){
        write(process[i].fp_input, &load_balance[i]->data[0], sizeof(int));
        write(process[i].fp_input, &load_balance[i]->data[1], sizeof(int));
        close(process[i].fp_input);
        process[i].fp_input = 0;
    }

    ArrayInt* array[numberProcess];
    int size = 0;
    for (int i = 0; i < numberProcess; i++){
        array[i] = createArray();
        read(process[i].fp_output, &size, sizeof(int));
        array[i]->resize(array[i], size);
        read(process[i].fp_output, array[i]->data, sizeof(int)*size);
        close(process[i].fp_output);
        process[i].fp_output = 0;
    }

    wait_for_process(numberProcess, process);
    
    ArrayInt *res = createArray();
    res->push(res, 1);

    for (int i = 0; i < numberProcess; i++){   
        res = multiply_array(*array[i], *res);
    }

    printf("%d! = ", factorialNumber);
    res->printNumber(res, 40);
    printf("\n");
    
    return 0;
}

/**
 * Função que criar, administra e espera o retorno das Threads, unindo os retornos 
 * em um resultado final. 
**/

int thread_main(int factorialNumber, int numberProcess){
    ArrayInt** load_balance = distribute(factorialNumber, numberProcess);
    int err = 0;

    Thread threads[numberProcess];
    for (int i = 0; i < numberProcess; i++){
        threads[i].input = (void *)load_balance[i];
        err = create_thread(&threads[i], my_thread_factorial, (void *)&threads[i]);
        if (err != 0){
            printf("Não foi possível criar thread\n");
            return -1;
        }
        
    }

    wait_for_threads(numberProcess, threads);

    ArrayInt *res = createArray();
    res->push(res, 1);

    for (int i = 0; i < numberProcess; i++){   
        res = multiply_array(*(ArrayInt *)threads[i].output, *res);
    }

    printf("%d! = ", factorialNumber);
    res->printNumber(res, 40);
    printf("\n");
    
    return 0;
}
