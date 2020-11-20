#include "calc.h"

ArrayInt* factorial(int n, int initial){ 

    ArrayInt *res = createArray();
    
    res->push(res, 1); 
  
    // n! = 1 * 2 * 3 * 4...*n 
    for (int x=initial; x<=n; x++){
        multiply(x, res, res);
    } 
    return res;
}


long double factorial_recursive(int n){
	if (n <= 1){
        return 1;
    }
	else{
  	  return n*factorial_recursive(n-1);
    }
}
