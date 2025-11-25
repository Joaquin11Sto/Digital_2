#include <stdio.h>


int strlen_1(char *s);
int main();


int strlen_1(char *s){

    char *inicio = s;
    while (*s != '\0') {
        s++;
    };

    return s - inicio;
};

int main(){
    char mi_cadena[] = "hola";
    int largoCadena = strlen_1(mi_cadena);
    printf("Cadena: \"%s\"\n", mi_cadena);
    printf("Largo : %d\n", largoCadena);
};