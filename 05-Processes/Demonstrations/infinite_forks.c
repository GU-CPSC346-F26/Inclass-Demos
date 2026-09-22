#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int flag = 0;

int main( ) {
    int children_created = 0;
    while(flag == 0){
        if(fork()==0){
            flag = 1;
        }
        else{
            children_created++;
            if(children_created%10000 == 0){
                printf("%d children created\n", children_created);
            }
            if (children_created == 50000){
                return -1;
            }
        }
    }
    return 0;

}