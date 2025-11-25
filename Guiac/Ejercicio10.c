#include <stdio.h>

int main(void){
    char a;
    int b = 0x12345678;
    short int c;
    printf("\n\nDireccion asignada para la variable a:\t %p\n", &a);
    printf("\nDireccion asignada para la variable b:\t %p\n", &b);
    printf("\nDireccion asignada para la variable c:\t %p\n", &c);

    // ¿Se logra alguna mejora en la utilización de la memoria?
    char d;
    short int e;
    int f = 0x12345678;
    printf("\n\nDireccion asignada para la variable a:\t %p\n", &d);
    printf("\nDireccion asignada para la variable b:\t %p\n", &e);
    printf("\nDireccion asignada para la variable c:\t %p\n", &f);

    // Al reordenarlo de esta forma,donde las vaariables quedan definidas de menor a mayor en lo que se refiere a tamaños de bytes,
    //  se elimina el espacio agregado por la cpu. Mejorando la optimizacion del mismo.

};

