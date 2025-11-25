#include <stdio.h>

union aux {
    int a;
    char b;
};

int main(void){
    union aux var;
    var.a = 77;
    printf("a: %d\n", var.a);
    printf("b: %c\n", var.b);
};

/* Resultado del terminal:
a: 77
b: M


En el b como definimos un char, este es de tamaño de un 1 byte.
Como definimos una union , el valor leido por b es 77.
Siguiendo la tabla del codigo ASCII el 77 = 'M'
por eso se imprime la M
*/