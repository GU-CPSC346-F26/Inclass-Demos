#include <stdio.h>
#include <string.h>

struct student{
    char name[32];
    float gpa;
    int a[2];
    struct student * friend;
};


void update_array(int array[]){
    array[0] = 100;
}
int main(){
    // struct student students[2] = {{"Timmy", 5.0, {7,8}}};
    // strcpy(students[1].name, "Johnny");
    // students[1].gpa = 4.0;

    // printf("student first element name: %s\n", students[0].name);

    // printf("student second element name: %s\n", students[1].name);
    

    struct student john = {"JOHN", 3.0, {1,2}};
    struct student dom = {"DOM", 2.0, {3,4}};
    struct student chiana = {"CHIANA", 4.0, {5,6}};
    
    dom.friend = &chiana;
    john = dom;

    printf("john's friend's name: %s\n", john.friend->name);
    printf("dom's friend's name: %s\n", dom.friend->name);

    john.friend->name[0] = 'X';

    printf("john's friend's name: %s\n", john.friend->name);
    printf("dom's friend's name: %s\n", dom.friend->name);

    printf("john array[0]: %d\n", john.a[0]);
    printf("dom array[0]: %d\n", dom.a[0]);
    
    update_array(john.a);

    printf("dom array[0]: %d\n", dom.a[0]);
    printf("john array[0]: %d\n", john.a[0]);














    // struct student students[] = {john, dom};
    
    // john.name[0] = 'X';
    // john.a[0]= 6;
    // printf("john: %s\n", john.name);
    // printf("student[0]: %s\n", students[0].name);
    // printf("john: %d\n", john.a[0]);
    // printf("student[0]: %d\n", students[0].a[0]);

    return 0;
}