typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18))

// 
#define GPIOC_BASE    0x40011000
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN_C     13

#define GPIOB_BASE    0x40010C00
#define GPIOB_CRL     (*(volatile unsigned int*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR     (*(volatile unsigned int*)(GPIOB_BASE + 0x0C))
#define LED_PIN_B     5

// GPIOA (Entrada para el pin PA0)
#define GPIOA_BASE    0x40010800
#define GPIOA_CRL     (*(volatile unsigned int*)(GPIOA_BASE + 0x00)) // CRL para pines 0-7
#define GPIOA_IDR     (*(volatile unsigned int*)(GPIOA_BASE + 0x08)) // Registro de DATOS DE ENTRADA
#define INPUT_PIN_A   0


int main(void){
    // 1. Activar el clock del Puerto C (LED) y Puerto A (Entrada)
    //    Bit 4 (IOPCEN) para Puerto C
    //    Bit 2 (IOPAEN) para Puerto A
    RCC_APB2ENR |= (1 << 4) | (1 << 3) | (1 << 2); 
    
    // 2. Configurar el LED de la placa (PC13) como salida
    GPIOC_CRH &= ~(0b1111 << 20); 
    GPIOC_CRH |= (0b0010 << 20);

    GPIOB_CRL &= ~(0b1111 << 20);
    GPIOB_CRL |= (0b0010 << 20);

    // 3. Configurar el pin de entrada (PA0) como "Entrada Flotante"
    //    MODE0 = 00 (Modo Entrada)
    //    CNF0  = 01 (Entrada Flotante)
    //    Configuración total para el pin 0: 0b0100
    GPIOA_CRL &= ~(0b1111 << 0); // Limpia los 4 bits del pin 0
    GPIOA_CRL |= (0b0100 << 0);  // Establece modo Entrada Flotante

    while(1){
        if (GPIOA_IDR & (1 << 0)) {
            // Si es 1 (HIGH), el cable está en 3.3V
            // Encender el LED (PC13 es lógica invertida -> 0)
            GPIOC_ODR &= ~(1 << 13);
            GPIOB_ODR |= (1 << 5);

        } else {
            // Si es 0 (LOW), el cable está en GND
            // Apagar el LED (PC13 es lógica invertida -> 1)
            GPIOC_ODR |= (1 << 13);
            GPIOB_ODR &= ~(1 << 5);
        }
    }
    return 0;
}



#define SRAM_SIZE ((uint32_t) 0x00005000)
#define SRAM_BASE ((uint32_t) 0x20000000)
#define STACKINIT ((interrupt_t)(SRAM_BASE+SRAM_SIZE))
typedef void(*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};