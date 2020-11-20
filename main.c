#include "calc.h"
#include "process.h"


void my_process(Process *process){
    char *array = NULL;
    int fatorialNumberInitial, fatorialNumberFinal;

    fscanf(process->fp_input,"%d;%d", &fatorialNumberInitial, &fatorialNumberFinal);
    fclose(process->fp_input);
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
    // printf("->%d;%d", fatorialNumberInitial, fatorialNumberFinal);

    ArrayInt *ptr_res = factorial(fatorialNumberFinal, fatorialNumberInitial);
    // ptr_res->printNumber(ptr_res, 0);
    // printf("\n");
    array = ptr_res->dumps(ptr_res);

    fprintf(process->fp_output, "%dB", ptr_res->size+1);

    for (size_t i = 0; i < ptr_res->size+1; i++){
        fprintf(process->fp_output, "%c", array[i]);
    }
    fprintf(process->fp_output, "\n");    
    
    fclose(process->fp_output);
    process->fp_output = 0;
}

ArrayInt** distribute(int fatorialNumber, int processNumber){
    ArrayInt** array= NULL;

    array = (ArrayInt**)calloc(processNumber, sizeof(ArrayInt));

    int initial = 0;
    int step = fatorialNumber/processNumber;
    
    for (size_t i = 0; i < processNumber; i++){
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

int main(int argc, char const *argv[]){
    int fatorialNumber = 0;
    int numberProcess = 0;
    char* array_dumps = NULL;

    if (argc < 3){
        return -1;
    }

    fatorialNumber = atoi(argv[1]);
    numberProcess = atoi(argv[2]);

    if (fatorialNumber < 0){ return -1; }
    if (numberProcess < 0){ return -1; }

    ArrayInt** load_balance = distribute(fatorialNumber, numberProcess);

    
    Process process[numberProcess];
    for (size_t i = 0; i < numberProcess; i++){
        create_process(&process[i], my_process);
    }

    for (size_t i = 0; i < numberProcess; i++){
        // printf("%d;%d ", load_balance[i]->data[0], load_balance[i]->data[1]);
        fprintf(process[i].fp_input, "%d;%d", load_balance[i]->data[0], load_balance[i]->data[1]);
    }

    for (size_t i = 0; i < numberProcess; i++){
        fclose(process[i].fp_input);
        process[i].fp_input = 0;
    }

    ArrayInt* array[numberProcess];
    for (size_t i = 0; i < numberProcess; i++)
    {
        array[i] = createArray();
    }
    
    char *buffer = NULL;
    char c;
    int sizeBuffer;
    for (size_t i = 0; i < numberProcess; i++){
        sizeBuffer = 0;
        while ((c = fgetc(process[i].fp_output)) != 'B'){
            printf("%c", c);
            sizeBuffer++;
        }
        buffer = (char*)calloc(sizeBuffer, sizeof(char));
        
        fgets(buffer, sizeBuffer, process[i].fp_output);
        array[i]->load(array[i], buffer);
        
        fclose(process[i].fp_output);
        process[i].fp_output = 0;
    }
    
    ArrayInt *res = createArray();

    res->push(res, 1);

    for (size_t i = 0; i < numberProcess; i++)
    {   
        // array[i]->print(array[i]);
        res = multiply_array(*array[i], *res);
    }
    
    res->printNumber(res, 0);
    printf("\n");
    // res->print(res);

    wait_for_process(numberProcess, process);

    // ArrayInt *ptr_res = factorial(fatorialNumber, 1);

    // ptr_res->printNumber(ptr_res, 0);

    return 0;
}




