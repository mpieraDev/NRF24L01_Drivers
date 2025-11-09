#include "spi_atmega328p.h"
#include "spi_cfg_atmega328p.h"

#include <stdint.h>
#include "registers_atmega328p.h"
#include "gpio_atmega328p.h"

#define SPI_DEFAULT_CONFIG(self_ptr) \
    self_ptr->SPI_pSPIx->SPCRx = 0; \
    self_ptr->SPI_pSPIx->SPSRx = 0; \
    spi_config_role(self_ptr, SPI_MASTER); \
    spi_config_mode(self_ptr, SPI_MODE0); \
    spi_config_prescaler(self_ptr, SPI_PRESCALER16); \
    spi_config_ddorder(self_ptr, SPI_LSB_FIRST); 

/*typedef enum 
{
    SPI0
} 
SPI_device_t;*/

typedef struct 
{
    SPI_RegDef_t*   SPI_pSPIx;
    SPI_cfg_t*      SPI_cfg;
    GPIO_handle_t*  SPI_slave_pin; 
} 
SPI_handle_t;

// para no corromper el bus spi utilizar metodologia acquirie release (mutex, semafor) 
// dentro de las funciones que interactuen con el para no corromper la informacion
// (encadenar bits de transacciones diferentes, como consequencia data erronea)

SPI_responsecode_t spi_init(
    SPI_handle_t*   self, 
    GPIO_handle_t*  spi_slave, 
    SPI_RegDef_t*   spi_pSPIx
) 
{   
    self->SPI_pSPIx = spi_pSPIx;
    self->SPI_slave_pin = spi_slave; 

    SPI_DEFAULT_CONFIG(self)

    return SPI_OK;
}

// asegurarse de que inicializa los campos que necesita que sean 
// 0 para la configuracion a 0, no asumir que los registros estan a 0
void spi_config_role(SPI_handle_t* self, SPI_role_t role) 
{
    self->SPI_cfg->SPI_role = role;

    switch (role)
    {
        case SPI_MASTER:
            DD_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
            PORTB |= (1 << SS); 
            gpio_data_direction(self->SPI_slave_pin, GPIO_OUTPUT);

            self->SPI_pSPIx->SPCRx |= (1 << MSTR);
            break;

        case SPI_SLAVE:
            DD_SPI |= (1 << DD_MISO);
            DD_SPI &= ~((1<<DD_MOSI) | (1<<DD_SCK) | (1<<DD_SS));
            gpio_data_direction(self->SPI_slave_pin, GPIO_INPUT);
            gpio_write(self->SPI_slave_pin, GPIO_HIGH);

            self->SPI_pSPIx->SPCRx &= ~(1 << MSTR);
            break;
    }
}

// asegurarse de que inicializa los campos que necesita que sean 
// 0 para la configuracion a 0, no asumir que los registros estan a 0
void spi_config_mode(SPI_handle_t* self, SPI_mode_t mode) 
{
    self->SPI_cfg->SPI_mode = mode;

    switch (mode) 
    {
        case SPI_MODE0: 
            self->SPI_pSPIx->SPCRx &= ~((1 << CPOL) | (1 << CPHA)); 
            break;

        case SPI_MODE1: 
            self->SPI_pSPIx->SPCRx &= ~(1 << CPOL);
            self->SPI_pSPIx->SPCRx |= (1<< CPHA);
            break;

        case SPI_MODE2: 
            self->SPI_pSPIx->SPCRx |= (1 << CPOL);
            self->SPI_pSPIx->SPCRx &= ~(1<< CPHA);
            break;

        case SPI_MODE3: 
            self->SPI_pSPIx->SPCRx |= (1 << CPOL) | (1 << CPHA); 
            break;
    }
}

// asegurarse de que inicializa los campos que necesita que sean 
// 0 para la configuracion a 0, no asumir que los registros estan a 0
void spi_config_prescaler(SPI_handle_t* self, SPI_prescaler_t prescaler) 
{
    self->SPI_cfg->SPI_prescaler = prescaler;

    switch (prescaler) 
    {
        case SPI_PRESCALER2:
            self->SPI_pSPIx->SPCRx &= ~((1 << SPR0) | (1 << SPR1));
            self->SPI_pSPIx->SPSRx |= (1 << SPI2X);
            break;
        
        case SPI_PRESCALER4:
            self->SPI_pSPIx->SPCRx &= ~((1 << SPR0) | (1 << SPR1));
            self->SPI_pSPIx->SPSRx &= ~(1 << SPI2X);
            break;

        case SPI_PRESCALER8:
            self->SPI_pSPIx->SPCRx &= ~(1 << SPR1);
            self->SPI_pSPIx->SPCRx |= (1 << SPR0);
            self->SPI_pSPIx->SPSRx |= (1 << SPI2X);
            break;

        case SPI_PRESCALER16:
            self->SPI_pSPIx->SPCRx &= ~(1 << SPR1);
            self->SPI_pSPIx->SPCRx |= (1 << SPR0);
            self->SPI_pSPIx->SPSRx &= ~(1 << SPI2X);
            break;

        case SPI_PRESCALER32:
            self->SPI_pSPIx->SPCRx |= (1 << SPR1);
            self->SPI_pSPIx->SPCRx &= ~(1 << SPR0);
            self->SPI_pSPIx->SPSRx |= (1 << SPI2X);
            break;

        case SPI_PRESCALER64:
            self->SPI_pSPIx->SPCRx |= (1 << SPR1);
            self->SPI_pSPIx->SPCRx &= ~(1 << SPR0);
            self->SPI_pSPIx->SPSRx &= ~(1 << SPI2X);
            break;
            
        case SPI_PRESCALER128:
            self->SPI_pSPIx->SPCRx |= (1 << SPR0) | (1 << SPR1);
            self->SPI_pSPIx->SPSRx &= ~(1 << SPI2X);
            break;
    }
}

// asegurarse de que inicializa los campos que necesita que sean 
// 0 para la configuracion a 0, no asumir que los registros estan a 0
void spi_config_ddorder(SPI_handle_t* self, SPI_ddorder_t ddorder) 
{
    self->SPI_cfg->SPI_ddorder = ddorder;

    switch (ddorder)
    {
        case SPI_MSB_FIRST:
            self->SPI_pSPIx->SPCRx &= ~(1 << DORD);
            break;
        
        case SPI_LSB_FIRST:
            self->SPI_pSPIx->SPCRx |= (1 << DORD);
            break;
    }
}

void spi_begin(SPI_handle_t* self)
{
    self->SPI_pSPIx->SPCRx |= (1 << SPE);
}

void spi_disable(SPI_handle_t* self)
{
    self->SPI_pSPIx->SPCRx &= ~(1 << SPE);
}

SPI_responsecode_t spi_master_transmit(SPI_handle_t* self, uint8_t byte)
{ 
    if (!spi_is_master(self)) return SPI_ERR;
    
    self->SPI_pSPIx->SPDRx = byte;

    while(!(self->SPI_pSPIx->SPSRx & (1 << SPIF)));

    return SPI_OK;
}

SPI_responsecode_t spi_master_receive(SPI_handle_t* self, uint8_t* byte)
{ 
    if (!spi_is_master(self)) return SPI_ERR;

    self->SPI_pSPIx->SPDRx = 0xFF;

    while(!(self->SPI_pSPIx->SPSRx & (1 << SPIF)));

    *byte = self->SPI_pSPIx->SPDRx;

    return SPI_OK;
}

SPI_responsecode_t spi_slave_transmit(SPI_handle_t* self, uint8_t byte)
{ 
    if (spi_is_master(self)) return SPI_ERR;

    self->SPI_pSPIx->SPDRx = byte;

    while(!(self->SPI_pSPIx->SPSRx & (1 << SPIF)));

    return SPI_OK;
}

SPI_responsecode_t spi_slave_receive(SPI_handle_t* self, uint8_t* byte)
{ 
    if (spi_is_master(self)) return SPI_ERR;

    while(!(self->SPI_pSPIx->SPSRx & (1 << SPIF)));

    *byte = self->SPI_pSPIx->SPDRx;

    return SPI_OK;
}

SPI_responsecode_t spi_select_slave(SPI_handle_t* self) 
{
    if (!spi_is_master(self)) return SPI_ERR;

    if (gpio_write(self->SPI_slave_pin, GPIO_LOW) == GPIO_ERR_DIR_INVALID) return SPI_ERR;

    return SPI_OK;
}

SPI_responsecode_t spi_unselect_slave(SPI_handle_t* self) 
{
    if (!spi_is_master(self)) return SPI_ERR;
    
    if(gpio_write(self->SPI_slave_pin, GPIO_HIGH) == GPIO_ERR_DIR_INVALID) return SPI_ERR;

    return SPI_OK;
}

// hardware check
static inline uint8_t spi_is_master()
{ 
    return ( (DD_SPI & (1 << DD_MOSI)) && 
             (DD_SPI & (1 << DD_SCK))  &&
             (DD_SPI & (1 << DD_SS))   &&
            !(DD_SPI & (1 << DD_MISO)) );
}

// API check
static inline uint8_t spi_is_master(SPI_handle_t* self)
{ 
    return (self->SPI_cfg->SPI_role == SPI_MASTER);
}

// añadir feature para que aunque el atmega sea master otro micro lo pueda cambiar a slave mediante el clk