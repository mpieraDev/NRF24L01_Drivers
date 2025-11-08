#ifndef REGISTERS_ATMEGA328P_H
#define REGISTERS_ATMEGA328P_H

#include <stdint.h>

#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define _SFR_MEM8(mem_addr) _MMIO_BYTE(mem_addr)
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t*)(mem_addr))
#define __SFR_OFFSET 0x20

#define SPCR _SFR_IO8(0x2C)                 // SPI Control Register
#define SPIE 7                              // SPI Interrupt Enable
#define SPE 6                               // SPI Enable
#define DORD 5                              // Data Order
#define MSTR 4                              // Master/Slave Select
#define CPOL 3                              // Clock Polarity
#define CPHA 2                              // Clock Phase
#define SPR1 1                              // SPI Clock Rate Select 1
#define SPR0 0                              // SPI Clock Rate Select 0

#define SPSR _SFR_IO8(0x2D)                 // SPI Status Register
#define SPIF 7                              // SPI Interrupt Flag
#define WCOL 6                              // Write COLlision Flag
#define SPI2X 0                             // Double SPI Speed Bit

#define SPDR _SFR_IO8(0x2E)                 // SPI Data Register

#define DD_SPI DDRB                         // SPI Data Direction Register
#define DD_MOSI DDB3
#define DD_MISO DDB4
#define DD_SCK DDB5
#define DD_SS DDB2

#define SS PB2

#define PORTB _SFR_IO8(0x05)                // The Port B Data Register
#define PORTB7 7
#define PORTB6 6
#define PORTB5 5
#define PORTB4 4
#define PORTB3 3
#define PORTB2 2
#define PORTB1 1
#define PORTB0 0

#define DDRB _SFR_IO8(0x04)                 // The Port B Data Direction Register
#define DDB7 7
#define DDB6 6
#define DDB5 5
#define DDB4 4
#define DDB3 3
#define DDB2 2
#define DDB1 1
#define DDB0 0


#define PINB _SFR_IO8(0x03)                // The Port B Input Pin Address
#define PB7 7
#define PB6 6
#define PB5 5
#define PB4 4
#define PB3 3
#define PB2 2
#define PB1 1
#define PB0 0

#define PORTC _SFR_IO8(0x08)                // The Port C Data Register
#define PORTC7 7
#define PORTC6 6
#define PORTC5 5
#define PORTC4 4
#define PORTC3 3
#define PORTC2 2
#define PORTC1 1
#define PORTC0 0

#define DDRC _SFR_IO8(0x07)                 // The Port C Data Direction Register
#define DDC7 7
#define DDC6 6
#define DDC5 5
#define DDC4 4
#define DDC3 3
#define DDC2 2
#define DDC1 1
#define DDC0 0


#define PINC _SFR_IO8(0x06)                // The Port C Input Pin Address
#define PC7 7
#define PC6 6
#define PC5 5
#define PC4 4
#define PC3 3
#define PC2 2
#define PC1 1
#define PC0 0

#define PORTD _SFR_IO8(0x0B)                // The Port D Data Register
#define PORTD7 7
#define PORTD6 6
#define PORTD5 5
#define PORTD4 4
#define PORTD3 3
#define PORTD2 2
#define PORTD1 1
#define PORTD0 0

#define DDRD _SFR_IO8(0x0A)                 // The Port D Data Direction Register
#define DDD7 7
#define DDD6 6
#define DDD5 5
#define DDD4 4
#define DDD3 3
#define DDD2 2
#define DDD1 1
#define DDD0 0


#define PIND _SFR_IO8(0x09)                // The Port D Input Pin Address
#define PD7 7
#define PD6 6
#define PD5 5
#define PD4 4
#define PD3 3
#define PD2 2
#define PD1 1
#define PD0 0

typedef struct
{
    uint8_t PORTx;
    uint8_t DDRx;
    uint8_t PINx;
}
GPIO_RegDef_t;

#define GPIOB (GPIO_RegDef_t*)PORTB 
#define GPIOC (GPIO_RegDef_t*)PORTC
#define GPIOD (GPIO_RegDef_t*)PORTD

#endif