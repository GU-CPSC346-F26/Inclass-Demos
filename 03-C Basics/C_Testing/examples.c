#include <stdio.h>

int proc_1(int a[], int nelements){
    int b[5] = {0,1,2,3,4};
    a = b;
    return a[1];
}

int proc_2(int arg[]){
    arg++;
    return arg[1];
}


int main(){
    // example 1
    int array[50];
    printf("result = %d\n", proc_1(array, 50));

    // example 2
    int array2[5] = {40,30,20,10,0};
    printf("result proc_1 = %d\n", proc_1(array2, 50));
    printf("result array2 after proc_1 = %d\n", array2[1]);


    // example 3
    int A[3] = {0,1,2};
    printf("%d\n", proc_2(A));
    printf("%d\n", A[1]);
    return 0;
}