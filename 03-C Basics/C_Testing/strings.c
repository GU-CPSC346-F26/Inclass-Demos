#include <stdio.h>
// gcc -Wall -Wextra -pedantic strings.c
int main(){
    char a[] = "abc";
    printf("%s\n", a);
    printf("%zu\n", sizeof(a));
    return 0;
}