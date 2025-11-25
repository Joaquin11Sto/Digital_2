#include <stdio.h> 
#include <stddef.h> 

// Defino el stuct
struct pru_struct {
    char id1;
    char id2;
    char id3[10];
    char *Nombre;
    char *domicilio;
    int edad;
    int varios;
};

void showInfo(struct pru_struct *e);


int main() {

    struct pru_struct empleados = {
        'B',                        
        'C',
        "Sensible",                 
        "Pedro",                    
        "Av. Carlos Calva 1234",    
        23,                         
        68                          
    };
    showInfo(&empleados);
    
    return 0;
}

void showInfo(struct pru_struct *e) {
    
    printf("Valores iniciales de la estructura\n");
    printf("id1:       %c\n", e->id1);
    printf("id2:       %c\n", e->id2);
    printf("id3:       %s\n", e->id3);
    printf("Nombre:    %s\n", e->Nombre);
    printf("Direccion: %s\n", e->domicilio);
    printf("Edad:      %d\n", e->edad);
    printf("Varios:    %d\n", e->varios);
    printf("\n"); 

   
    printf("Direccion de la estructura: %p\n", e);
    printf("\n"); 

    
    printf("Direccion del miembro id1:        %p (offset: %zu bytes)\n", &e->id1, offsetof(struct pru_struct, id1));
    printf("Direccion del miembro id2:        %p (offset: %zu bytes)\n", &e->id2, offsetof(struct pru_struct, id2));
    printf("Direccion del miembro id3:        %p (offset: %zu bytes)\n", &e->id3, offsetof(struct pru_struct, id3));
    printf("Direccion del miembro nombre:     %p (offset: %zu bytes)\n", &e->Nombre, offsetof(struct pru_struct, Nombre));
    printf("Direccion del miembro domicilio:  %p (offset: %zu bytes)\n", &e->domicilio, offsetof(struct pru_struct, domicilio));
    printf("Direccion del miembro edad:       %p (offset: %zu bytes)\n", &e->edad, offsetof(struct pru_struct, edad));
    printf("Direccion del miembro varios:     %p (offset: %zu bytes)\n", &e->varios, offsetof(struct pru_struct, varios));
    printf("\n"); 
    printf("Dirección de la primera posición de memoria después de la estructura: %p\n", (char *)e + sizeof(struct pru_struct));

    // Para "id1" y " id2", se tiene asignados valores de 1 byte, al ser de tipo char (offset = 0 y 1)
    // En el "id3" se tiene una cadena de 8 caracteres que se copia dentro de la memoria de la estructura. Este ocupa 10 bytes para el offset (offset = 2)
    //El "Nombre" es un puntero, por lo tanto lo que se guarda en la estructura es la direccion del nombre. Al tener un sistema de 64 bits se le 
    // agrega un padding de 4 bytes, para asi el cpu quede alineado en 8 bytes, en lo que se corresponde a direccion de memoria.(offset = 16 )
    // Lo miso ocurre para "Direccion", solamente en la estructura sde guarda la direccion.(offset =24) en total va ocupar 8 bytes
    // Para "Edad" y "varios" son enteros de 4 bytes (offset = 32 y 36 )
};