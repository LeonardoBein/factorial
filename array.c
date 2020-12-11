#include "array.h"

/**
 * Função adiciona numero no array, redimencionando.
**/

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

/**
 * Função altera o tamanho do array
**/

void resize_array(ArrayInt * array, int size){
    
    if (array->size == size){
        return;
    }
    if (size == 0){
        array->clear(array);
        return;
    }
    
    

    if (array->data == NULL){
        array->data = (int *)calloc(size, sizeof(int));
    }else{
        array->data = (int *)realloc(array->data, sizeof(int)*size);
    }

    if (!array->data) { printf("Faltando memoria"); return; }
    array->size = size;
}

/**
 * Função limpa o array
**/

void clear_array(ArrayInt * array){
    if (array->data != NULL) {
        free(array->data);
        array->data = NULL;
    }
    array->size = 0;
}

/**
 * Função mostra os elementos do array
**/

void print_array(ArrayInt *array){
    printf("[");
    for (int i = 0; i < array->size; i++)
    {
        printf(" %d ", array->data[i]);
        if (i+1 < array->size){ printf(",");}
    }
    printf("]");
    
}

/**
 * Função mostra o numero armazenado no array
 *  Exemplo [3,2,1]
 *  print -> 123
**/

void print_number(ArrayInt* array, int limite){
    if (limite != 0 && array->size > limite){
        printf("%d.", array->data[array->size - 1]);
        for (int i = array->size - 2; i >= array->size - 10; i--){
            printf("%d", array->data[i]);
        }
        printf(" E+%d",array->size-1);
    }else{
        for (int i = array->size - 1; i >= 0; i--){
            printf("%d", array->data[i]);
        }
    }
    
}

/**
 * Função copia dois array
**/

void copy_array(ArrayInt* destiny, ArrayInt* source){
    // destiny->clear(destiny);
    // destiny->resize(destiny,source->size);

    for (int i = 0; i < source->size; i++)
    {
        destiny->data[i] = source->data[i];
    }

}

/**
 * Função cria uma struct contento todos os metodos para manumular o array
**/

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
    array->printNumber = print_number;
    array->clear(array);

    return array;
}