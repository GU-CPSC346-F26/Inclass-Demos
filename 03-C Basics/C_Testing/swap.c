#include <stdio.h>


void swap1(int * a, int * b){
   	int * temp;
	temp = a;
    a=b;
    b=temp;
}
// Works
void swap2(int * a, int * b){
   	int temp;
	temp = *a; 
    *a=*b; 
    *b=temp;

}

int main(){
    int a = 3;
    int b = 5;
    swap1(&a,&b);
    printf("a is now %d, b is now %d", a, b);
}