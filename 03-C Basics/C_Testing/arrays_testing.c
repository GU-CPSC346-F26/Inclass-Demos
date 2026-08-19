#include <stdio.h>
// int main() {
//     int j = 8;
//     int a[100];
//     int i;
//     for(i =0; i<=101; i++){
//         a[i] = i;
//     }
//     printf("%d\n",j);
// }

int proc(int *a, int elements){
    int i;
    for(i = 0; i<elements-1; i++){
        a[i+1] += a[i];
    }
    return a[elements-1];
}

int proc_2(int a[], int elements){
    int i;
    for(i = 0; i<elements-1; i++){
        a[i+1] += a[i];
    }
    return a[elements-1];
}

int example3(int a[]){
    a++;
    return a[1];
}

int main(){
    int number[5] = {10,20,30,40,50};
    *(number + 1) = 60;
    printf("%d\n", *(number+1));
    printf("result = %d\n", proc(number, 5));

    int number2[5] = {10,20,30,40,50};
    printf("result = %d\n", proc_2(number2, 5));

    int number3[5] = {10,20,30,40,50};
    printf("result = %d\n", example3(number3));
    printf("result = %d\n", number3[1]);
    return 0;
}