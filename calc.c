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
