#include <stdio.h>
int sumar(int x, int y);
int main();



int main(){
    int x=0,y=2;
    printf("Cuenta: %d + %d = %d\n\n", x, y, sumar(x,y));

    return 0;
};

int sumar(int x, int y){
    int suma;
    suma = x + y;
    return suma;
};