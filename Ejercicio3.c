typedef int            int32_t;
typedef short          int16_t;
typedef char           int8_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

/*
Agregar un led externo a la placa e implementar un código C  
de bajo nivel que lo encienda y apague, junto con el existente en la placa,  siguiendo algún patrón.
*/

/* --- Definiciones de Periféricos (RCC y GPIO) --- */
#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18))

#define GPIOC_BASE    0x40011000
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN_C     13

#define GPIOB_BASE    0x40010C00
#define GPIOB_CRL     (*(volatile unsigned int*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR     (*(volatile unsigned int*)(GPIOB_BASE + 0x0C))
// --- CAMBIO AQUÍ ---
#define LED_PIN_B     5  // Usamos el pin PB5, que es un GPIO normal

int main(void){
    volatile unsigned int cont;

    // 1. Activar el clock del Puerto C y Puerto B
    RCC_APB2ENR |= (1 << 4) | (1 << 3); 
    
    // 2. Configurar el LED de la placa (PC13) como salida
    GPIOC_CRH &= ~(0b1111 << ((LED_PIN_C - 8) * 4)); 
    GPIOC_CRH |= (0b0010 << ((LED_PIN_C - 8) * 4));  
    
    // 3. Configurar el LED externo (PB4) como salida
    //    El cálculo (LED_PIN_B * 4) ahora usa 4,
    //    por lo que apunta a los bits correctos para el pin 4 en GPIOB_CRL.
    GPIOB_CRL &= ~(0b1111 << (LED_PIN_B * 4));
    GPIOB_CRL |= (0b0010 << (LED_PIN_B * 4));
    
    // 4. ENCENDER AMBOS LEDS (fijo)
    

    while(1){
     // ---- ESTADO 1 ----
        // LED Placa (PC13) ENCENDIDO (lógica invertida: 0)
        // LED Externo (PB4) APAGADO (lógica normal: 0)
        GPIOC_ODR &= ~(1 << LED_PIN_C);
        GPIOB_ODR &= ~(1 << LED_PIN_B);
        
        // Retardo por software
        for (cont = 0; cont < 500000; cont++) {
        }
        
        // ---- ESTADO 2 ----
        // LED Placa (PC13) APAGADO (lógica invertida: 1)
        // LED Externo (PB4) ENCENDIDO (lógica normal: 1)
        GPIOC_ODR |= (1 << LED_PIN_C);
        GPIOB_ODR |= (1 << LED_PIN_B);
        
        // Retardo por software
        for (cont = 0; cont < 500000; cont++) {
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