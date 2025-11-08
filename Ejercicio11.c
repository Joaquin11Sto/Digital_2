#define SRAM_SIZE		((uint32_t) 0x00005000)
#define SRAM_BASE		((uint32_t) 0x20000000)
#define STACKINIT		((interrupt_t)(SRAM_BASE+SRAM_SIZE))

typedef int			   int32_t;
typedef short		   int16_t;
typedef char		   int8_t;
typedef unsigned int   uint32_t; // un entero de 32 bits
typedef unsigned short uint16_t; 
typedef unsigned char  uint8_t; // un entero de 8 bits

typedef void(*interrupt_t)(void);

typedef union {
	uint8_t  byte[4]; // un array de 4 bytes osea es el 32/4 = 8, por eso se usa unit8_t
	uint16_t hword[2]; // un array de dos media palabra, de 16 bits
	uint32_t word; // Trata una sola palabra de 32 bits 
} word_t;

typedef word_t page[0x400/sizeof(uint32_t)]; // es de tamaño de 1024 bytes 


// Memory map

enum {TIM2	= 0, TIM3  = 1, TIM4  = 2 };
enum {GPIOA = 0, GPIOB = 1, GPIOC = 2, GPIOD = 3, GPIOE = 4, GPIOF = 5 };
enum {DMA1	= 0 };
enum {CHN1	= 0, CHN2  = 1, CHN3  = 2, CHN4  = 3, CHN5	= 4, CHN6  = 5, CHN7 = 6, CHN8 = 7 };
enum {ADC1	= 0 };

struct {
	union {
		struct { // Toda las acciones que puede hacer los timers 
			uint32_t CR1;
			uint32_t CR2;
			uint32_t SMCR;
			uint32_t DIER;
			uint32_t SR;
			uint32_t EGR;
			uint32_t CCMR1;
			uint32_t CCMR2;
			uint32_t CCER;
			uint32_t CNT;
			uint32_t PSC;
			uint32_t ARR;
			uint32_t RES1;
			uint32_t CCR1;
			uint32_t CCR2;
			uint32_t CCR3;
			uint32_t CCR4;
			uint32_t BDTR;
			uint32_t DCR;
			uint32_t DMAR;
		} REGs;
		page reserved;
	} TIMs[3];

	word_t reserved1[(0x40002800-0x40000c00)/sizeof(word_t)];
	page RTC;
	page WWDG;
	page IWDG;
	word_t reserved2[(0x40003800-0x40003400)/sizeof(word_t)];
	page SPI2;
	word_t reserved3[(0x40004400-0x40003c00)/sizeof(word_t)];
	page USART[2];
	word_t reserved4[(0x40005400-0x40004c00)/sizeof(word_t)];
	page I2C[2];
	page USB;
	page USBCAN_SRAM;
	page bxCAN;
	word_t reserved5[(0x40006c00-0x40006800)/sizeof(word_t)];
	page BKP;
	page PWR;
	word_t reserved6[(0x40010000-0x40007400)/sizeof(word_t)];

	page AFIO;
	page EXTI;

	union {
		struct { // Todas las acciones que hacen las GPIOs
			uint32_t CRL;
			uint32_t CRH;
			uint32_t IDR;
			uint32_t ODR;
			uint32_t BSRR;
			uint32_t BRR;
			uint32_t LCKR;
		} REGs;
		page reserved;
	} GPIOs[5];
	word_t reserved7[(0x40012400-0x40011C00)/sizeof(word_t)];
	union {
		struct { // Todas las acciones que hace los ADCs
			uint32_t SR;
			uint32_t CR1;
			uint32_t CR2;
			uint32_t SMPR1;
			uint32_t SMPR2;
			uint32_t JOFR;
			uint32_t HTR;
			uint32_t LTR;
			uint32_t SQR1;
			uint32_t SQR2;
			uint32_t SQR3;
			uint32_t JSQR;
			uint32_t JDR;
			uint32_t DR;
		} REGs;
		page reserved;
	} ADC[2];
	page TIM1;
	page SPI1;
	word_t reserved8[(0x40013800-0x40013400)/sizeof(word_t)];
	union  {
		struct {
			uint32_t SR;
			uint32_t DR;
			uint32_t BRR;
			uint32_t CR1;
			uint32_t CR2;
			uint32_t CR3;
			uint32_t GTPR;
		} REGs;
		page reserved;
	} USART1;
	word_t reserved9[(0x40020000-0x40013C00)/sizeof(word_t)];
	union {
		struct {
			uint32_t ISR;
			uint32_t IFCR;
			struct {
				uint32_t CCR;
				uint32_t CNDTR;
				uint32_t CPAR;
				uint32_t CMAR;
				uint32_t RESERVED;
			} CHN[8];
		} REGs;
		page reserved;
	} DMAs[1];
	word_t reservedA[(0x40021000-0x40020400)/sizeof(word_t)];

	union {
		struct {
			uint32_t CR;
			uint32_t CFGR;
			uint32_t CIR;
			uint32_t APB2RSTR;
			uint32_t APB1RSTR;
			uint32_t AHBENR;
			uint32_t APB2ENR;
			uint32_t APB1ENR;
			uint32_t BDCR;
			uint32_t CSR;
			uint32_t AHBRSTR;
			uint32_t CFGR2;
		} REGs;
		page reserved;
	} RCC;
	word_t reservedB[(0x40022000-0x40021400)/sizeof(word_t)];

	union {
		struct {
			uint32_t ACR;
			uint32_t KEYR;
			uint32_t OPTKEYR;
			uint32_t SR;
			uint32_t CR;
			uint32_t AR;
			uint32_t reserved;
			uint32_t OBR;
			uint32_t WRPR;
		} REGs;
		page reserved;
	} FLASH;
} volatile *const DEVMAP = (void *) 0x40000000;


#define ENA_IRQ(IRQ) {CTX->NVIC.REGs.ISER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define DIS_IRQ(IRQ) {CTX->NVIC.REGs.ICER[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}
#define CLR_IRQ(IRQ) {CTX->NVIC.REGs.ICPR[((uint32_t)(IRQ) >> 5)] = (1 << ((uint32_t)(IRQ) & 0x1F));}

struct {
	word_t reversed0[(0xe000e010-0xe0000000)/sizeof(word_t)];
	union {
		struct {
			uint32_t CSR;
			uint32_t RVR;
			uint32_t CVR;
			uint32_t CALIB;
		} REGs;
	} SYSTICK;
	word_t reversed1[(0xe000e100-0xe000e020)/sizeof(word_t)];
	union {
		struct {
			uint32_t ISER[8];
			uint32_t RES0[24];
			uint32_t ICER[8];
			uint32_t RES1[24];
			uint32_t ISPR[8];
			uint32_t RES2[24];
			uint32_t ICPR[8];
			uint32_t RES3[24];
			uint32_t IABR[8];
			uint32_t RES4[56];
			uint8_t  IPR[240];
			uint32_t RES5[644];
			uint32_t STIR;
		} REGs;
	} NVIC; // Controla las interrupciones, es el gestor.
} volatile *const CTX = ((void *) 0xE0000000);

enum IRQs {
	IRQ_DMA1CHN2  = 12,
	IRQ_ADC1_2	  = 18,
	IRQ_TIM2	  = 28,
	IRQ_USART1	  = 37,
};
#define LED_PIN 13
#define LED_ON (1<<(LED_PIN + 16))
#define LED_OFF (1<<LED_PIN )
#define PATTERN_LEN 8
const uint32_t g_led_pattern[PATTERN_LEN] = {
    LED_ON,     // dum (on)
    LED_OFF,    //    (off)
    LED_ON,     // DUM (on)
    LED_ON,     // DUM (on - más largo)
    LED_OFF,    //    (off)
    LED_OFF,    //    (pausa)
    LED_OFF,    //    (pausa)
    LED_ON     //    (pausa)
};

int main (void){
        // 1. Habilitacion de los clocks de los componentes que se usaran.
        DEVMAP->RCC.REGs.AHBENR |=(1 << 0); // Se habilita el clock del dma1 
        DEVMAP->RCC.REGs.APB2ENR |=(1 << 4); // Se habilita el clock para GPIOC del Led 13
        DEVMAP->RCC.REGs.APB1ENR |=(1 << 0); // Se habilita el clock para el TIM2EN

        // 2. Configuracion de los pines GPIO (PC13)
        DEVMAP->GPIOs[GPIOC].REGs.CRH &= ~((1 << 20) | (1 << 21) | (1 << 22) | (1 << 23));
        // Se limpia la configuracion del pin 13 para el led.
        
        DEVMAP->GPIOs[GPIOC].REGs.CRH |=((1 << 21) | (1 << 20) );
        // SE configura la salida del pin push-pull, 50MHz
        // el MODE = 11 en los bits 21 y 20.

        // al principio apagamos el LED
        DEVMAP->GPIOs[GPIOC].REGs.BSRR = LED_OFF;

        // 3. Se configura el DMA con el DMA1 = 0 y usamos CHN2 = 1
        DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CPAR = (uint32_t)&(DEVMAP->GPIOs[GPIOC].REGs.BSRR);
        // Aca se apunta al reset and set del GPIOC, esto para solamente escrbir en el pin 13 sin afectar
        // a los demas, se hace esa and para verificar que la direccion de destino es en el GPIOC.
        // Se escribe siempre en ese lugar. CPAR = pheriferial address register.

        DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CMAR = (uint32_t)g_led_pattern;
        // Aca es de donde sale la informacion, la fuente de informacion
        // CMAR = Memory Address register

        DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CNDTR = PATTERN_LEN;
         // Aca se cuenta la cantidad de trasnferencias que se van a llevar a cabo.
         //( CNDTR = Number of Data to Transfer.)

        DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |= ( (1 << 13) | (1 << 11) | (1 << 9) | (1 << 7) | (1 << 5) | (1 << 4));
        // PL = [1,0] es el bit 13 para dejarlo 1,0 -> Siendo esto de prioridad alta
        // MS = [1,0] es el size de bits de memoria q se usa, en este caso 32 ubicado en el 11 y 10
        // PS = [1,0] es el size de bits de periferico que se usa, en este caso 32 bits ubicado en el 9 y 8
        // MINC con esto incrementamos el puntero de memoria usando el bit 7
        // CINC con esto se genera el software circular con el bit 5, por que se usa?
        // DIR es para activar el memoria a periferico usando el bit 4.

        // 4. Ahora configuramos los timers
        DEVMAP->TIMs[TIM2].REGs.PSC = 8000 - 1;
        // el PSC es el pre escaler, al tener (8MHz) es muy rapido para manejar, hay que reducirlo.
        // como se pre escala con 8M / PSC + 1 = 1000 HZ. Con esto tenemos un tick de 1ms.
        DEVMAP->TIMs[TIM2].REGs.ARR = 100 - 1 ;
        // Esto es por que queremos registrar cada 200 ms, se repite lo de arriba.
        // Auto-Reload register.
        DEVMAP->TIMs[TIM2].REGs.DIER |= (1 << 8); 
        // esto se llama DMA/ Interrupt enable register, con esto notificamos al dma que se active
        // sin la necesidad de molestar a la CPU, solamente pasa por el DMA.
        
        // 5. Habilitaciones
        DEVMAP->DMAs[DMA1].REGs.CHN[CHN2].CCR |= (1 << 0);
        // con bit 0 se activa el canal 2 del dma1
        DEVMAP->TIMs[TIM2].REGs.CR1 |= (1 << 0);
        // con el bit 0 se activa el timer que configure.

        while (1)
        {
            /* code */
        };
    return 0;
};

typedef void(*interrupt_t)(void);
const interrupt_t vector_table[256] __attribute__ ((section(".vtab"))) = {
	STACKINIT,												// 0x0000_0000 Stack Pointer
	(interrupt_t) main,										// 0x0000_0004 Reset
};