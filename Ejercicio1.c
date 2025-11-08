typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

// Dirección base del bus APB2 donde se encuentra el RCC
#define SRAM_SIZE ((uint32_t) 0x00005000)
#define SRAM_BASE ((uint32_t) 0x20000000)
#define STACKINIT ((interrupt_t)(SRAM_BASE+SRAM_SIZE))
#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18)) // Direccion del registro para conectarse el APB2

// Esto vendria siendo para el periferico APB2
#define GPIOC_BASE    0x40011000 // Direccion del GPIOC
// Dirección del registro de configuración "High" para los pines 8-15
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
// Voy a usar los altos por que se encuentra en el pin 13 la luz que hay que prender
// Dirección del registro de datos de salida del puerto C
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN 13 // Posicion del led que quiero prender 

int main (void){
    RCC_APB2ENR |= (1<<4); // Le asigno un 1 a la posicion 4 que es el que habilita el Puerto C en el manual.
    // Aca estoy habilitando el reloj para esta salida de los pines 
    GPIOC_CRH &= ~(0b1111 << 20);
    // Ahora estoy poninedo un 0 en los bits que se van a disponer usar para que quede todo limpio?
    GPIOC_CRH |= (0b0010 << 20);
    // Ten los bits 20,21,22,23 se encuentra el control del pin 13, que seria el led que posee la placa.
    // Por lo tanto para que tenga algo a la salida, indico 0010 que la salida es de 2MHz y de CNF push-up

    GPIOC_ODR &= ~(1 << LED_PIN);
    // En el bit 13 lo dejo bajo para que se prenda el led que estoy buscando prender, 
    // voy a probar con no prenderlo tambien para ver que pasa 


    for(;;);

	return 0;
}


typedef void(*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};
