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
volatile unsigned int g_ticks_ms = 0;
void delay_ms(unsigned int ms);
void SysTick_Handler(void);

void delay_ms(unsigned int ms){
    unsigned int start_ticks = g_ticks_ms;
    for(unsigned int cont = 0,cont<ms;cont++){

    };
};

int main(void){
    RCC_APB2ENR |= ( 4<<1 );

    GPIOC_CRH &= ~(0b1111 << ((LED_PIN_C) - 8) * 4); // Limpio los bits
    GPIOC_CRH &= ~(0b0010 << ((LED_PIN_C) - 8) * 4); // ACtivo el outpu push-pull de 50MHz

    STK_LOAD = 999;
    STK_VAL = 0; // Limpia el contador
    
    // 4. Habilitar SysTick CON INTERRUPCIÓN
    //    Bit 0 (ENABLE): Habilita el contador
    //    Bit 1 (TICKINT): Habilita la INTERRUPCIÓN cuando llega a 0
    STK_CTRL = (1 << 1) | (1 << 0); // 0x03

    while(1){
        // Encender LED (lógica invertida)
        GPIOC_ODR &= ~(1 << LED_PIN_C);
        
        // Llamar a nuestra nueva función de delay
        delay_ms(100); 
        
        // Apagar LED
        GPIOC_ODR |= (1 << LED_PIN_C);
        
        // Llamar a nuestra nueva función de delay
        delay_ms(1000); // Un segundo apagado
    };

    return 0;
};


void SysTick_Handler(void) {
    // Simplemente incrementa nuestro "reloj maestro" global
    g_ticks_ms++;
};

const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
    [0]  = STACKINIT,              // Vector 0: Stack Pointer
    [1]  = (interrupt_t) main,     // Vector 1: Reset
    // ...
    [15] = (interrupt_t) SysTick_Handler // Vector 15: SysTick
};