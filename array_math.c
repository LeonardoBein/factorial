#include "array_math.h"

/**
 * Função multiplica dois array e retorna o resultado
 * array1 * array2 = array3 
**/

ArrayInt* multiply_array(ArrayInt array1, ArrayInt array2){
    ArrayInt *array_larger = NULL;
    ArrayInt *array_less = NULL;
    ArrayInt *aux, *res;

    aux = createArray();
    res = createArray();

    if (array1.size > array2.size){ 
        array_larger = &array1;
        array_less = &array2;
    }
    else{ 
        array_larger = &array2;
        array_less = &array1; 
    }

    // printf("Pequeno: \t");
    // array_less->print(array_less);
    // printf("Grande: \t");
    // array_larger->print(array_larger);
    
    res->resize(res, 1);

    for (int i = 0; i < array_less->size; i++)
    {
        aux->clear(aux);
        multiply(array_less->data[i]*(int)pow(10, i), array_larger, aux);
        // res->print(aux);
        res = sum_array(*res, *aux);
    }
    return res;
}

/**
 * Função soma dois array e retorna o resultado
 * array1 + array2 = array3 
**/
ArrayInt* sum_array(ArrayInt array1, ArrayInt array2){
    int size = 0;
    int carry = 0;
    ArrayInt array_larger, *res;
    
    res = createArray();

    
    if (array1.size < array2.size){ 
        size = array1.size;
        array_larger = array2;
    }
    else{ 
        size = array2.size;
        array_larger = array1; 
    }
    
    res->resize(res, array_larger.size);

    for (int i = 0; i < res->size; i++)
    {
        res->data[i] = array_larger.data[i];
    }
    

    for (int i = 0; i < size; i++)
    {
        int sum = array1.data[i] + array2.data[i] + carry;
        res->data[i] = sum % 10;
        
        carry = sum/10;

    }

    while (carry) 
    { 
        if (res->size > size){
            res->data[size++] += carry%10;
        }else{
            res->push(res, carry%10);
        }
        
        carry = carry/10; 
    } 

    return res;
    
}

/**
 * Função multiplica um array por um numero e retorna o resultado
 * number * array2 = array3 
**/
void multiply(int x, ArrayInt *array, ArrayInt *res) { 
    int carry = 0;
    res->resize(res, array->size);
    // array->print(res);
    // printf("x %d", x);

    for (int i=0; i < array->size; i++) { 
        int prod = array->data[i] * x + carry; 
        // printf("prod: %d",prod);
        // printf("prod%%10: %d",prod%10);
        res->data[i] = prod % 10;
        carry  = prod/10;     
    } 
  
    while (carry) { 
        res->push(res, carry%10);
        carry = carry/10; 
    }
    // array->print(res);
 
} 

