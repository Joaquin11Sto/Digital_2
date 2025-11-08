/* --- Definiciones de Memoria y Vector de Interrupción --- */
#define SRAM_SIZE     ((unsigned int) 0x00005000)
#define SRAM_BASE     ((unsigned int) 0x20000000)
#define STACKINIT     ((interrupt_t)(SRAM_BASE + SRAM_SIZE))
typedef void(*interrupt_t)(void);

#define RCC_BASE      0x40021000
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18))

// GPIOC (Salida para el LED)
#define GPIOC_BASE    0x40011000
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN_C     13

// GPIOA (Entrada para el pin PA0)
#define GPIOA_BASE    0x40010800
#define GPIOA_CRL     (*(volatile unsigned int*)(GPIOA_BASE + 0x00)) // CRL para pines 0-7
#define GPIOA_IDR     (*(volatile unsigned int*)(GPIOA_BASE + 0x08)) // Registro de DATOS DE ENTRADA
#define GPIOA_ODR     (*(volatile unsigned int*)(GPIOA_BASE + 0x0C))
#define INPUT_PIN_A   0

int main(void){
    RCC_APB2ENR |= (1 << 4) | (1 << 2);

    // 2. Configurar el LED de la placa (PC13) como salida
    GPIOC_CRH &= ~(0b1111 << 20); 
    GPIOC_CRH |= (0b0010 << 20);

    // 3. Configurar el pin de entrada (PA0) como "Entrada Flotante"
    //    MODE0 = 00 (Modo Entrada)
    //    CNF0  = 01 (Entrada Flotante)
    //    Configuración total para el pin 0: 0b0100
    GPIOA_CRL &= ~(0b1111 << 0); // Limpia los 4 bits del pin 0
    GPIOA_CRL |= (0b1000 << 0);

    // 4. HABILITAR la resistencia de PULL-UP (no la pull-down)
    //    Para entradas, el registro ODR selecciona el tipo de resistor.
    //    ODR = 1 -> Pull-Up
    //    ODR = 0 -> Pull-Down
    GPIOA_ODR |= (1 << 0);

    
    while(1){
        if (GPIOA_IDR & (1 << 0)) {
            // Si el pin está en ALTO (HIGH, 3.3V) -> Botón NO PRESIONADO
            // Apagar el LED (lógica invertida -> 1)
            GPIOC_ODR |= (1 << LED_PIN_C);
        } else {
            // Si el pin está en BAJO (LOW, GND) -> Botón PRESIONADO
            // Encender el LED (lógica invertida -> 0)
            GPIOC_ODR &= ~(1 << LED_PIN_C);
        }
    };
    return 0;
};

/* --- Tabla de Vectores --- */
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
    STACKINIT,               
    (interrupt_t) main,      
};