/*1. Armar un código en C para mostrar por pantalla los diferentes tamaños de los tipos:
 char, short,int, long, float y double (utilizar la función sizeof).*/
 #include <stdio.h>

int main(){
    printf("Tamaño de char:   %zu byte(s)\n", sizeof(char));
    printf("Tamaño de short:   %zu byte(s)\n", sizeof(short));
    printf("Tamaño de int:   %zu byte(s)\n", sizeof(int));
    printf("Tamaño de long:   %zu byte(s)\n", sizeof(long));
    printf("Tamaño de float:   %zu byte(s)\n", sizeof(float));
    printf("Tamaño de doblue:   %zu byte(s)\n", sizeof(double));
    return 0;
 };

 