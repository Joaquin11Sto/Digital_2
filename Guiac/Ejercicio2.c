#include <stdio.h>
/*2. Crear un vector de enteros de 10 posiciones,
 recorrerlo e imprimir por pantalla cada uno de susvalores. ¿Qué tamaño ocupa en memoria? 
*/

int main(){
    int array[10] = {0,1,2,3,4,5,6,7,8,9};

    for(int i = 0; i < 10; i++){
        printf("Numero: %i \n",array[i]);
    }

    size_t TamanioVector = sizeof(array);
    printf("Tamaño total del vector : %zu bytes\n", TamanioVector);

    return 0;
};