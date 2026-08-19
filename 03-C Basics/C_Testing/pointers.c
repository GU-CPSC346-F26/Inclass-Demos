#include <stdio.h>

int func1(int *p){
    *p=2*(*p);
    return *p;
}

int update(int *p, int *q){
    *p = *p + *q;
    *q = *q - *p;
    return *p;
}

int get(int arr[], int n){
    return arr[n-1];
}

int main(){
    // int x = 4;
    // int * pX = &x;
    // int y = *pX;
    // printf("x=%d, y = %d, px = %d\n", x,y,*pX);
    // y = 5;
    // printf("x=%d, y = %d, px = %d\n", x,y,*pX);
    // *pX = 6;
    // printf("x=%d, y = %d, px = %d\n", x,y,*pX);

    // int * p;
    // int a = 4;
    // p = &a;
    // *p = *p +1;
    // *p = *p + 3;
    // printf("%d\n", *p);
    // int a = 3;
    // int b = func1(&a);
    // printf("%d\n", a*b);
    // int a = 5, b = 3;
    // int result = update(&a, &b);
    // printf("%d %d %d\n", result, a, b);
    int A[] = {10,20,30,40,50};
    int *p = A;
    printf("%d\n", get(p+2,2));
    printf("%d\n", A[3]);
}