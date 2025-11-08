#define SRAM_SIZE     ((unsigned int) 0x00005000)
#define SRAM_BASE     ((unsigned int) 0x20000000)
#define STACKINIT     ((interrupt_t)(SRAM_BASE + SRAM_SIZE))
typedef void(*interrupt_t)(void);

/* --- Definiciones de Periféricos (RCC y GPIO) --- */
#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18))
#define GPIOC_BASE    0x40011000
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN_C     13

/* --- Definiciones del SysTick Timer --- */
#define SYSTICK_BASE  0xE000E010
#define STK_CTRL      (*(volatile unsigned int*)(SYSTICK_BASE + 0x00)) // Control
#define STK_LOAD      (*(volatile unsigned int*)(SYSTICK_BASE + 0x04)) // Valor de recarga
#define STK_VAL       (*(volatile unsigned int*)(SYSTICK_BASE + 0x08)) // Valor actual

int main(void); 
void SysTick_Handler(void);

int main(void){
    // Activo el clock
    RCC_APB2ENR |= (1 << 4);

    GPIOC_CRH &= ~(0b1111 << ((LED_PIN_C) - 8) * 4); // Limpio los bits
    GPIOC_CRH &= ~(0b0010 << ((LED_PIN_C) - 8) * 4); // ACtivo el outpu push-pull de 50MHz

    // HAcemos que empieze el led apagasdo.

    GPIOC_ODR |=(1 << LED_PIN_C);

    // Ahora vamos a configurar el systick
    
    STK_LOAD = 499999;
    // Si quiero una interrupcion de medio segundo, tomo 500000 microsegundos.
    // por que el systick corre a 1 MHz y nosotros tenemos 8MHz
    STK_VAL = 0; // Limpio el contador para que inicie en 0.
    
    STK_CTRL = (1 << 1) | (1 << 0);
    // Aca es donde see habilita la interrupcion 
    // con bit 0 su modo es ENABLE, habilitando el contador
    // con bit 1 tickint nos habilita la interrupcion 
    while (1)
    {
        /* Todo el trabajo se hace fuera del bucle ocasionado por la  */
    }
    
    return 0;
};

void SysTick_Handler(void) {
    // Esta es la forma más rápida de "invertir" un bit
    // Si el bit 13 era 1, lo vuelve 0.
    // Si era 0, lo vuelve 1.
    GPIOC_ODR ^= (1 << LED_PIN_C);
    
    // No necesitamos limpiar ninguna bandera, el hardware
    // lo maneja al entrar a esta interrupción.
};

const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	[0] = STACKINIT,												// 0x0000_0000 Stack Pointer
	[1] = (interrupt_t) main,										// 0x0000_0004 Reset
    0,
    0,
    0,
    0,
    0,
    0,
    [15] = (interrupt_t) SysTick_Handler,
};