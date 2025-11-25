#include <stdio.h>

int main(){
    int x[5] = {1,2,3,4,5};
    int *ptr;

    /*a) ¿Cómo haría para que el puntero ptr apunte a la primera posición del vector x?*/

    ptr = &x[0];
    printf("Direccion :");

    /*b) ¿Recorrer el vector completo utilizando incrementos en el puntero ptr?*/

    /*c) Realizar un printf del puntero ptr para cada incremento del punto b. Indicar por qué entrevalor y valor existe un salto en la secuencia.*/
    for (int i = 0; i < 5; i++) {
        printf("Posicion %d: Direccion (ptr) = %p, Valor (*ptr) = %d\n", i, ptr, *ptr);
        ptr++; 
    };

    /*d) Si en lugar de tener un vector de enteros (int) 
    en el ejemplo utilizáramos un vector de chars, elsalto entre 
    valores consecutivos del punto c cambiaría? 
    Corroborarlo modificando lo quecorresponda del código.*/
    char x_char[5] = {'A', 'B', 'C', 'D', 'E'};
    char *ptr_char; // Puntero a char


    ptr_char = x_char; // Apunta a x_char[0]
    
    for (int i = 0; i < 5; i++) {
        printf("Posicion %d: Direccion (ptr) = %p, Valor (*ptr) = %c\n", i, ptr_char, *ptr_char);
        ptr_char++; 
    };

    return 0;
};