#include <stdio.h>
int main() {
    int i;
    float f;
    char c; 
    i = 34;
    f = 45.6789;
    double ff = 45.6789;
    c = 'a';
    printf("1:%d\n",i);
    printf("2:%3c\n",c);
    printf("3:%2c\n",c);
    printf("4:%1c\n",c);
    printf("5:%f\n",f);
    printf("6:%6.2f\n",f);
    printf("7:%5f\n",f);
    printf("8:%2.0f\n",f);
    printf("9:%lf\n",ff);
    printf("10:%f\n", ff);
}