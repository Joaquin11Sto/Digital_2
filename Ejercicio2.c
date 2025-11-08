typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

/*
Implementar un código C de bajo nivel para que el led se encienda y
 se apague (parpadee) de acuerdo a un retardo que también deberán crear.

*/

// Dirección base del bus APB2 donde se encuentra el RCC
#define SRAM_SIZE ((uint32_t) 0x00005000)
#define SRAM_BASE ((uint32_t) 0x20000000)
#define STACKINIT ((interrupt_t)(SRAM_BASE+SRAM_SIZE))
#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18)) // Direccion del registro para conectarse el APB2
// Hacer un contador de reloj 
#define GPIOC_BASE    0x40011000 // Direccion del GPIOC
// Dirección del registro de configuración "High" para los pines 8-15
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
// Voy a usar los altos por que se encuentra en el pin 13 la luz que hay que prender
// Dirección del registro de datos de salida del puerto C
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN 13 // Posicion del led que quiero prender 



int main (void) {
    volatile unsigned int cont;
    RCC_APB2ENR |= (1<<4); // Activo el clock
    // Activo el pin 13 como salida
    GPIOC_CRH &= ~(0b1111 << ((LED_PIN - 8) * 4));
    GPIOC_CRH |= (0b0010 << ((LED_PIN - 8) * 4));

    while(1) {
        // Encender el LED (poner PC13 en BAJO)
        GPIOC_ODR &= ~(1 << LED_PIN);
        
        // Esperar 500 milisegundos (medio segundo)
        for(cont = 0;cont < 500000;cont++){

        };
        
        // Apagar el LED (poner PC13 en ALTO)
        GPIOC_ODR |= (1 << LED_PIN);
        
        // Esperar otros 500 milisegundos
        for(cont = 0;cont < 500000;cont++) {

        };
    }
    return 0;

};

typedef void(*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};
