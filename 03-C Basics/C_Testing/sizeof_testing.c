#include <stdio.h>
int main() {
    int i = 1;
    long l = 1234567891;
    long long ll = 12345678912345;
    float f = 1.2;
    double d = 123.456789;
    char c = 'a';
    printf("Size of int: %lu bytes\n", sizeof(i));
    printf("Size of long: %lu bytes\n", sizeof(l));
    printf("Size of long long: %lu bytes\n", sizeof(ll));
    printf("Size of float: %lu bytes\n", sizeof(f));
    printf("Size of double: %lu bytes\n", sizeof(d));
    printf("Size of char: %lu bytes\n", sizeof(c));

    int * iP;
    float * fP;
    double * dP;
    char * cP;
    char s[] = "0123456789";
    printf("Size of int *: %lu bytes\n", sizeof(iP));
    printf("Size of float *: %lu bytes\n", sizeof(fP));
    printf("Size of double *: %lu bytes\n", sizeof(dP));
    printf("Size of char *: %lu bytes\n", sizeof(cP));

    printf("Size of string %s: %lu bytes\n", s, sizeof(s));

}