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
#define GPIOC_BASE    0x40011000 // Direccion del GPIOC
#define GPIOC_CRH     (*(volatile unsigned int*)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile unsigned int*)(GPIOC_BASE + 0x0C))
#define LED_PIN 13 // Posicion del led que quiero prender 

#define SYSTICK_BASE 0xE000E010 // Esta sacado de la pagina original del fabricante 
#define STK_CTRL      (*(volatile unsigned int*)(SYSTICK_BASE + 0x00)) // Control
#define STK_LOAD      (*(volatile unsigned int*)(SYSTICK_BASE + 0x04)) // Valor de recarga
#define STK_VAL       (*(volatile unsigned int*)(SYSTICK_BASE + 0x08)) // Valor actual


int main(void){
    // 1. Activar el clock del Puerto C
    RCC_APB2ENR |= (1 << 4); 
    
    // 2. Configurar el pin 13 como salida (GP Output Push-pull, 2MHz)
    GPIOC_CRH &= ~(0b1111 << ((LED_PIN - 8) * 4)); // Limpiar bits
    GPIOC_CRH |= (0b0010 << ((LED_PIN - 8) * 4));  // Escribir modo
    
    while(1){

        GPIOC_ODR &= ~(1 << LED_PIN);

        for(unsigned int i = 0;i < 500;i++){
            // Se carga el Systick
            STK_LOAD = 999;
            // Se limpia el contador actual
            STK_VAL = 0;

            STK_CTRL = (1 << 0);
            
            while((STK_CTRL & (1 << 16)) == 0){

            };
            // Se desactiva el Systick
            STK_CTRL = 0;
        };

        GPIOC_ODR |= (1 << LED_PIN);

        for(unsigned int i = 0;i < 5500;i++){
            STK_LOAD = 999;
            // Se limpia el contador actual
            STK_VAL = 0;

            STK_CTRL = (1 << 0);
            
            while((STK_CTRL & (1 << 16)) == 0){

            };
            // Se desactiva el Systick
            STK_CTRL = 0;
        };

    }
    return 0;
}

/* --- Tabla de Vectores --- */
typedef void(*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};