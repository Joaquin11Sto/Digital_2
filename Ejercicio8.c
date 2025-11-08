/* --- Definiciones de Memoria y Vector de Interrupción --- */
#define SRAM_SIZE     ((unsigned int) 0x00005000)
#define SRAM_BASE     ((unsigned int) 0x20000000)
#define STACKINIT     ((interrupt_t)(SRAM_BASE + SRAM_SIZE))
typedef void(*interrupt_t)(void);
void EXTI0_Handler(void);


/* --- Definiciones de Periféricos --- */
#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18))

// GPIOA (Botón)
#define GPIOA_BASE    0x40010800
#define GPIOA_CRL     (*(volatile unsigned int*)(GPIOA_BASE + 0x00)) 
#define GPIOA_ODR     (*(volatile unsigned int*)(GPIOA_BASE + 0x0C)) 
#define INPUT_PIN_A   0

// GPIOC (LED)
#define GPIOC_BASE    0x40011000
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN_C     13
// AFIO (Mapeo de interrupción)
#define AFIO_BASE     0x40010000
#define AFIO_EXTICR1  (*(volatile unsigned int*)(AFIO_BASE + 0x08))

// EXTI (Controlador de Interrupción Externa)
#define EXTI_BASE     0x40010400
#define EXTI_IMR      (*(volatile unsigned int*)(EXTI_BASE + 0x00)) // Interrupt Mask Register
#define EXTI_FTSR     (*(volatile unsigned int*)(EXTI_BASE + 0x0C)) // Falling Trigger...
#define EXTI_PR       (*(volatile unsigned int*)(EXTI_BASE + 0x14)) // Pending Register

// NVIC (Controlador de Interrupciones del CPU)
#define NVIC_ISER0    (*(volatile unsigned int*)(0xE000E100))
#define EXTI0_IRQ_NUM 6 // La interrupción EXTI0 es la número 6

int main(void){

    // 1. Activar Clocks: GPIOC (LED), GPIOA (Botón) y AFIO (Interrupción)
    RCC_APB2ENR |= (1 << 4) | (1 << 2) | (1 << 0); 
    
    // 2. Configurar el LED (PC13) como salida
    GPIOC_CRH &= ~(0b1111 << ((LED_PIN_C - 8) * 4)); 
    GPIOC_CRH |= (0b0010 << ((LED_PIN_C - 8) * 4));  
    
    // 3. Configurar el Botón (PA0) como Entrada con Pull-Up
    //    CNF=10 (Input pull-up/pull-down), MODE=00 (Input)
    GPIOA_CRL &= ~(0b1111 << (INPUT_PIN_A * 4)); 
    GPIOA_CRL |= (0b1000 << (INPUT_PIN_A * 4));  
    //    Habilitar el resistor de PULL-UP (escribiendo 1 en el ODR)
    GPIOA_ODR |= (1 << INPUT_PIN_A);
    // --- 4. CONFIGURACIÓN DE LA INTERRUPCIÓN ---
    
    // 4.a. Mapear PA0 a la línea EXTI0 (AFIO)
    //      Escribir 0000 en los bits EXTI0[3:0] de AFIO_EXTICR1
    AFIO_EXTICR1 &= ~(0b1111 << 0); // (0000 = Puerto A)

    // 4.b. Configurar la línea EXTI0 (EXTI)
    //      Habilitar la interrupción en la línea 0 (desenmascarar)
    EXTI_IMR |= (1 << 0);
    //      Configurar el disparador por "Flanco de Bajada" (Falling Edge)
    EXTI_FTSR |= (1 << 0);
    
    // 4.c. Habilitar la interrupción en el "cerebro" (NVIC)
    //      Habilitar la IRQ número 6 (EXTI0)
    NVIC_ISER0 |= (1 << EXTI0_IRQ_NUM);

    while(1){

    };
    return 0;
};

void EXTI0_Handler(void) {
    // 1. Acción: Invertir el estado del LED
    //    (Si estaba en 1, lo pone en 0. Si estaba en 0, lo pone en 1)
    GPIOC_ODR ^= (1 << LED_PIN_C);

    // 2. ¡MUY IMPORTANTE! Limpiar la bandera de la interrupción
    //    Si no hacemos esto, la CPU se quedará en un bucle infinito
    //    entrando a esta función sin parar.
    //    Se limpia escribiendo un '1' en el bit pendiente.
    EXTI_PR |= (1 << 0);
};

const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
    [0]  = STACKINIT,               // Vector 0: Stack Pointer
    [1]  = (interrupt_t) main,      // Vector 1: Reset
    // ...
    // La interrupción EXTI0 es el vector 22 (16 + 6)
    [22] = (interrupt_t) EXTI0_Handler 
};