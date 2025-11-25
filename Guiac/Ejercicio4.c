#include <stdio.h>


int main(){
    int x=1,y=2;

    int *ptr;

    printf("x:   Valor = %d, \nDireccion = %p\n", x, &x);
    printf("y:   Valor = %d, \nDireccion = %p\n", y, &y);
    printf("ptr: Valor = %p, \nDireccion = %p\n", ptr, &ptr);

    
    ptr= &x;
    printf("\nCambio \n");
    printf("x:   Valor = %d, \tDireccion = %p\n", x, &x);
    printf("y:   Valor = %d, \tDireccion = %p\n", y, &y);
    printf("ptr: Valor = %p, \tDireccion = %p\n", ptr, &ptr);

    y=*ptr;
    printf("\nCambio \n");
    printf("x:   Valor = %d, \tDireccion = %p\n", x, &x);
    printf("y:   Valor = %d, \tDireccion = %p\n", y, &y);
    printf("ptr: Valor = %p, \tDireccion = %p\n", ptr, &ptr);

    *ptr=0;
    printf("\nCambio \n");
    printf("x:   Valor = %d, \tDireccion = %p\n", x, &x);
    printf("y:   Valor = %d, \tDireccion = %p\n", y, &y);
    printf("ptr: Valor = %p, \tDireccion = %p\n", ptr, &ptr);


    return 0;
};