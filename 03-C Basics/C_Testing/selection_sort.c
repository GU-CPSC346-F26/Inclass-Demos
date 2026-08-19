#include <stdio.h>
#include <stdlib.h>

void swap(int array[], int i, int j, int size){
    if(i >= size || j >= size){
        return;
    }
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void selectsort(int array[], int length){
    int i, j, min;
    for(i = 0; i < length; i++){
        min = i;
        for(j = i; j < length; j++){
            if (array[j]<array[min]){
                min = j;
            }
        }
        swap(array, i, min, length); 
    }

}

void listprint(int array[], int length){
    for(int i = 0; i < length; i++){
        printf("%d: %d\n", i, array[i]);
    }
}

int main(){
    int size = 6;
    int array[6] = {5,9,3,6,7,1};
    selectsort(array, 6);
    listprint(array, size);
    return 0;
}