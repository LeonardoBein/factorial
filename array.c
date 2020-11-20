#include "array.h"

void push_array(ArrayInt * array, int value){
    if (array->data == NULL)
    {
        array->data = (int *)calloc(1, sizeof(int));

        if (!array->data) { printf("Faltando memoria"); exit(1); }

        array->data[0] = value; 
        array->size = 1;
    }else{
        array->data = (int *)realloc(array->data, sizeof(int)*(array->size + 1));
        
        if (array->data == NULL) { printf("Faltando memoria"); exit(1); }
        
        array->data[array->size] = value;
        array->size += 1;
        
    }
}

void resize_array(ArrayInt * array, int size){
    
    if (array->size == size){
        return;
    }
    // if (size == 0){
    //     array->clear(array);
    //     return;
    // }
    
    

    if (array->data == NULL){
        array->data = (int *)calloc(size, sizeof(int));
    }else{
        array->data = (int *)realloc(array->data, sizeof(int)*size);
    }

    if (!array->data) { printf("Faltando memoria"); return; }
    array->size = size;
}

void clear_array(ArrayInt * array){
    if (array->data != NULL) {
        free(array->data);
        array->data = NULL;
    }
    array->size = 0;
}

void print_array(ArrayInt *array){
    printf("[");
    for (int i = 0; i < array->size; i++)
    {
        printf(" %d ", array->data[i]);
        if (i+1 < array->size){ printf(",");}
    }
    printf("]");
    
}

void print_number(ArrayInt* array, int limite){
    if (limite != 0 && array->size > limite){
        for (int i = array->size - 1; i >= array->size - 3; i--){
            printf("%d", array->data[i]);
        }
        printf(".%dE+%d",array->data[array->size-4],array->size-3);
    }else{
        for (int i = array->size - 1; i >= 0; i--){
            printf("%d", array->data[i]);
        }
    }
    
}

void copy_array(ArrayInt* destiny, ArrayInt* source){
    // destiny->clear(destiny);
    // destiny->resize(destiny,source->size);

    for (int i = 0; i < source->size; i++)
    {
        destiny->data[i] = source->data[i];
    }

}

char* dumps_array(ArrayInt* array){
    char* data = NULL;

    data = (char*)calloc(array->size+1,sizeof(char));

    if (data == NULL){ printf("Error ao exportar dados"); return NULL; }

    data[array->size] = 'A';

    for (int i = 0; i < array->size; i++)
    {
        data[i] = (char)(array->data[i]+48);
    }

    return data;
}

void load_array(ArrayInt* array, char* string){
    int size = 0;
    char *string_intial = string;
    while (*string != 'A'){
        size++;
        string++;
    }

    array->resize(array, size);

    for (int i = 0; i < array->size; i++){
        array->data[i] = (int)(string_intial[i]-48);
    }
}

ArrayInt* createArray(){

    ArrayInt *array = (ArrayInt *)calloc(1, sizeof(ArrayInt));

    if (array == NULL){
        printf("Error: createArray\n");
        exit(1);
    }

    array->clear = clear_array;
    array->push = push_array;
    array->print = print_array;
    array->copy = copy_array;
    array->resize = resize_array;
    array->load = load_array;
    array->dumps = dumps_array;
    array->printNumber = print_number;
    array->clear(array);

    return array;
}