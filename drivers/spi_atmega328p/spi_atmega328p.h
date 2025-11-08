#ifndef SPI_ATMEGA328P_H
#define SPI_ATMEGA328P_H

#include <stdint.h>
#include "gpio_atmega328p.h"

typedef enum 
{
  SPI_OK,
  SPI_ERR,
  SPI_DEVICE_OCCUPIED
} 
SPI_responsecode_t;

typedef struct SPI_handle_t;

SPI_responsecode_t spi_init(
    SPI_handle_t*   self, 
    GPIO_handle_t*  spi_slave, 
    SPI_device_t    spi_device 
);

void spi_config_role(SPI_handle_t* self, SPI_role_t role);
void spi_config_mode(SPI_handle_t* self, SPI_mode_t mode);
void spi_config_prescaler(SPI_handle_t* self, SPI_prescaler_t prescaler);
void spi_config_ddorder(SPI_handle_t* self, SPI_ddorder_t ddorder);  
void spi_begin(SPI_handle_t* self);
void spi_disable(SPI_handle_t* self);
SPI_responsecode_t spi_master_transmit(SPI_handle_t* self, uint8_t byte);
SPI_responsecode_t spi_master_receive(SPI_handle_t* self, uint8_t* byte);
SPI_responsecode_t spi_slave_transmit(SPI_handle_t* self, uint8_t byte);
SPI_responsecode_t spi_slave_receive(SPI_handle_t* self, uint8_t* byte);
SPI_responsecode_t spi_select_slave(SPI_handle_t* self);
SPI_responsecode_t spi_unselect_slave(SPI_handle_t* self);

#endif