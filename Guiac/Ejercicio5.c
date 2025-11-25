#include <stdio.h>
void swap(int *a,int*b);
int main();


void swap(int *a,int*b){
    int temp = *a;
    *a=*b;
    *b = temp;
};

int main(){
    int x = 1, y = 2;
    printf("Valores originales:\tx = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("Valores nuevos:\t\tx = %d, y = %d\n", x, y);
    return 0;
};