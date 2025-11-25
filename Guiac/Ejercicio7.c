#include <stdio.h>

int main(void){
    int a = 0x12345678;
    short int b = 0xABCD;
    char c = 'a';
    int * ptr_a = &a;
    short int * ptr_b = &b;
    char * ptr_c = &c;
    printf("\nValor de ptr_a:\t\t %p\n", ptr_a); // Direccion:  00000000005FFEB4
    printf("Valor de ptr_a + 1:\t %p\n", ++ptr_a); // Direccion: 00000000005FFEB8
    // El ptr_a posee un tamaño de 4 bits, cuando se suma una posicion se mueven 4
    printf("\nValor de ptr_b:\t\t %p\n", ptr_b); // Direccion: 00000000005FFEB2
    printf("Valor de ptr_b + 1:\t %p\n", ++ptr_b); // Direccion: 00000000005FFEB4
    // El ptr_b posee un tamaño de 2 bits, cuando se suma una posicion se mueve 2
    printf("\nValor de ptr_c:\t\t %p\n", ptr_c); // Direccion: 00000000005FFEB1
    printf("Valor de ptr_c + 1:\t %p\n", ++ptr_c); // Direccion: 00000000005FFEB2
    // El ptr_c posee un tamaño de 1 bit, cuando se suma una poscion se mueve 1.

    
    return 0;
}