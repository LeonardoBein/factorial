#include "calc.h"


/**
 * Função realiza o calculo do fatorial
**/

ArrayInt* factorial(int n, int initial){ 

    ArrayInt *res = createArray();
    res->push(res, 1); 
  
    // n! = 1 * 2 * 3 * 4...*n 
    for (int x=initial; x<=n; x++){
        multiply(x, res, res);
    } 
    return res;
}


/**
 * Função multiplica dois array e retorna o resultado
 * array1 * array2 = array3 
**/

ArrayInt * multiply_array(ArrayInt array1, ArrayInt array2){
    ArrayInt *res = NULL;
    long int carry = 0;

    int initial1 = 0, initial2 = 0;

    if (array1.size > 1000){
        initial1 = array1.size - 1000;
    }

    if (array2.size > 1000){
        initial2 = array2.size - 1000;
    }    

    res = createArray();
    res->resize(res, array1.size + array2.size);
    
    for (int i = initial2; i < array2.size; i++){
        carry = 0;
        for (int j = initial1; j < array1.size; j++){
            res->data[j + i] += carry + (array1.data[j] * array2.data[i]);
            carry = res->data[j + i] / 10;
            res->data[j + i] = res->data[j + i] % 10;
        }
        res->data[i+array1.size] = carry;
    }

    if (res->data[res->size-1] == 0) {
        res->resize(res, res->size-1);
    }
    return res;
}

/**
 * Função multiplica um array por um numero e retorna o resultado (res)
 *  
**/
void multiply(int x, ArrayInt *array, ArrayInt *res) { 
    int carry = 0;
    res->resize(res, array->size);
   
    for (int i=0; i < array->size; i++) { 
        int prod = array->data[i] * x + carry; 
        res->data[i] = prod % 10;
        carry  = prod/10;     
    } 
  
    while (carry) { 
        res->push(res, carry%10);
        carry = carry/10; 
    }
 
} 
