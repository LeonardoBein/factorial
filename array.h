#include <stdlib.h>
#include <stdio.h>

typedef struct _ArrayInt
{
    int* data;
    int size;

    void (*push)(struct _ArrayInt* array, int value);
    void (*clear)(struct _ArrayInt* array);
    void (*copy)(struct _ArrayInt* destiny, struct _ArrayInt* source);
    void (*resize)(struct _ArrayInt* array, int size);
    char* (*dumps)(struct _ArrayInt* array);
    void (*load)(struct _ArrayInt* array, char* string);
    void (*print)(struct _ArrayInt* array);
    void (*printNumber)(struct _ArrayInt* array, int limite);
} ArrayInt;

void push_array(ArrayInt* array, int value);
void clear_array(ArrayInt* array);
void print_array(ArrayInt* array);
void print_number(ArrayInt* array, int limite);
void copy_array(ArrayInt* destiny, ArrayInt* source);
void resize_array(ArrayInt* array, int size);
char* dumps_array(ArrayInt* array);
void load_array(ArrayInt* array, char* string);
ArrayInt* createArray();