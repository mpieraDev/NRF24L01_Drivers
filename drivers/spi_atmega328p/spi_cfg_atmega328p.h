#ifndef SPI_CFG_ATMEGA328P_H
#define SPI_CFG_ATMEGA328P_H

#include <stdint.h>

// when the SPI is configured as slave it is only guranteed to work at f/4 or lower
// Atmega 328p is exclusively full_duplex and it does not have a configuration mode for cs (chip select), the datasize is fixed to 8bits to.

typedef struct 
{
  SPI_prescaler_t   SPI_prescaler;  
  SPI_mode_t        SPI_mode;
  SPI_ddorder_t     SPI_ddorder;
  SPI_role_t        SPI_role;        
} 
SPI_cfg_t;

typedef enum 
{
    SPI_PRESCALER2,     // SPI2X = 1, SPR1 = 0, SPR0 = 0
    SPI_PRESCALER4,     // SPI2X = 0, SPR1 = 0, SPR0 = 0
    SPI_PRESCALER8,     // SPI2X = 1, SPR1 = 0, SPR0 = 1
    SPI_PRESCALER16,    // SPI2X = 0, SPR1 = 0, SPR0 = 1
    SPI_PRESCALER32,    // SPI2X = 1, SPR1 = 1, SPR0 = 0
    SPI_PRESCALER64,    // SPI2X = 0, SPR1 = 1, SPR0 = 0
    SPI_PRESCALER128    // SPI2X = 0, SPR1 = 1, SPR0 = 1
}
SPI_prescaler_t;

typedef enum 
{
    SPI_MODE0,  // CPOL = 0, CPHA = 0
    SPI_MODE1,  // CPOL = 0, CPHA = 1  
    SPI_MODE2,  // CPOL = 1, CPHA = 0
    SPI_MODE3   // CPOL = 1, CPHA = 1   
}
SPI_mode_t;

typedef enum 
{
    SPI_MSB_FIRST,
    SPI_LSB_FIRST
}
SPI_ddorder_t;

typedef enum 
{
    SPI_MASTER,
    SPI_SLAVE
}
SPI_role_t;

#endif