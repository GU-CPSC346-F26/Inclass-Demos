#include <stdio.h>
#include "func.h"

#define SIZE 5
#define NAME dom

int	main() {
    // char NAME[]= "jim";
    printf("%d\n", fact(SIZE)) ; 
    printf("%s\n", NAME);
    return	0;
}

int fact(int i){
    int	k ;

    int	res ;

    for(res=1,k=1 ; k<=i ; k++){

        res = res * k ;
    }
    return	res;
}