#define SRAM_SIZE     ((unsigned int) 0x00005000)
#define SRAM_BASE     ((unsigned int) 0x20000000)
#define STACKINIT     ((interrupt_t)(SRAM_BASE + SRAM_SIZE))
typedef void(*interrupt_t)(void);

/* --- Definiciones de Periféricos (RCC y GPIO) --- */
#define RCC_BASE      0x40021000
#define RCC_CR        (*(volatile unsigned int)(RCC_BASE + 0x00))
#define RCC_CFGR      (*(volatile unsigned int*)(RCC_BASE + 0x04)) // Configuration Register
#define RCC_APB2ENR   (*(volatile unsigned int*)(RCC_BASE + 0x18))


int main(void){
    RCC_CR |= (1 << 16); // Activo el HSE que es el oscilador de (8MHz)

    while(!(RCC_CR & (1 << 17))){
    }; // Aca hago un polling, para detectar que el oscilador ya esta estable por que el tipo se carga.

    // Aca limpiamos los bits para setear todos los parametros de los preescalers
    RCC_CFGR &= ~((0b1111 << 4) | (0b111 << 8) | (0b111 << 11));
    // Configuro el HPRE que el bit del 7 al 4. aca se preescalea el AHB
    RCC_CFGR |= (0b1000 << 4);
    // Configuro el PPRE 1 que va del bit 8 al 10, aca se escalea el APB 1 que es de bajo velocity
    RCC_CFGR |=(0b100 << 8); // como lo quiero dividor por 2, pongo ese numero de bit
    // Configuro el PPRE 2 que va del bit 13 al 11, aca se escale el APB 2 que es el de alta velocity.
    RCC_CFGR |=(0b101 << 11); // lo tengo que setear en preescaler por 4, asi que coloco ese numero de bit.
     // hasta aca solamente se setearon los preescalers

    RCC_CFGR &= ~((1 << 16) | (1 << 17) | (0b1111 << 18));
    // Limpio los bits de esa posiciones.

    RCC_CFGR |= (1 << 16); // aca seteo el oscilador con el preescaler seteado. le digo que si.
    // Vos lo pusiste en 1, que significa: usar el HSE (cristal externo) como fuente.
    RCC_CFGR |=(1 << 17); // Un divisor que se aplica antes que se entre a la entrada.
    // como entran 8MHz se divide por 2. Osea 4MHz, luego se multiplitca por pllmull.

    RCC_CFGR |= (0b0010 << 18); // Aca se multiplica el factor de PLL el bit que se puso es para multiplicar por 4

    RCC_CR |= (1 << 24); // Con esto activamos el PLL = 1
    while(!(RCC_CR & (1 << 25))){
    };

    // Ahora vamos a setear el pll como la fuente de reloj principal
    RCC_CFGR &= ~(0b11 << 0); // Primero hago limpieza
    RCC_CFGR |= (0b10 << 0); // Elijo el PLL como reloj
    while ( (RCC_CFGR & (0b11 << 2)) != (0b10 << 2) ) {
    };
    // Aca hace polling para que se confirme el cambio al PLL
    while(1){
    };

    return 0;
};


/* --- Tabla de Vectores --- */
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
    [0] = STACKINIT,            // Stack Pointer
    [1] = (interrupt_t) main,   // Reset
};
