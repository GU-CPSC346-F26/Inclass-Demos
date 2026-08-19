#include <stdio.h>

// struct node
// {
//     int val;
//     float z;
// };


// int main() {
//     struct node x,*y;
//     x.z = 3.2;
//     x.val = 10;
//     y = &x;
//     printf("y points to node x with %d and %.1f\n", y->val,y->z);
// }



struct ComplexNumber{
    float real;
    float imag;
};

struct ComplexNumber ComplexAdd(struct ComplexNumber a1, struct ComplexNumber a2){
    struct ComplexNumber result;
    result.real = a1.real + a2.real;
    result.imag = a1.imag + a1.imag;
    return result;
}

void ComplexAddRef(struct ComplexNumber *a1, struct ComplexNumber *a2, struct ComplexNumber *result){
    result->real = a1->real + a2->real;
    result->imag = a1->imag + a1->imag;
}


int main(){
    struct ComplexNumber x, *y;
    x.real = 3.1;
    x.imag = 4.7;
    y = &x;
    printf("y points to node x with %.1f and %.1f\n", y->real,y->imag);
    struct ComplexNumber w, z;
    z.real = 3.1;
    z.imag = 4.7;
    w = z;
    z.real = 5.0;
    printf("w with %.1f and %.1f\n", w.real,w.imag);

    // struct ComplexNumber a,b,c;
    // a.real = 1.0;
    // a.imag = 3.0;
    // b.real = 1.0;
    // b.imag = 3.0;
    // c = ComplexAdd(a,b);
    // printf("now, c is has a real val of %.1f and a imag value of %.1f\n", c.real, c.imag);

    // struct ComplexNumber d;
    // ComplexAddRef(&a,&b,&d);
    // printf("now, d is has a real val of %.1f and a imag value of %.1f\n", d.real, d.imag);
}