#include "gpio_atmega328p.h"

#include <stdint.h>
#include "registers_atmega328p.h"

#define GPIO_CHECKBIT(bit) ((bit < 8) ? 1 : 0)
#define GPIO_CHECKOUTPUT(selfptr) ((*(selfptr)->GPIO_pGPIOx->DDRx & (1 << (selfptr)->GPIO_bit)) ? 1 : 0)
#define GPIO_CHECKINPUT(selfptr) ((*(selfptr)->GPIO_pGPIOx->DDRx & (1 << (selfptr)->GPIO_bit)) ? 0 : 1)

#define ERR 2

GPIO_responsecode_t gpio_init(GPIO_handle_t* self, GPIO_RegDef_t* pGPIOx, uint8_t bit)
{
    if (!GPIO_CHECKBIT(bit)) return GPIO_ERR_BIT_RANGE;
     
    self->GPIO_pGPIOx = pGPIOx;
    self->GPIO_bit = bit;

    return GPIO_OK;
}

void gpio_data_direction(GPIO_handle_t* self, GPIO_direction_t dd)
{
    switch (dd)
    {
    case GPIO_INPUT:
        self->GPIO_pGPIOx->DDRx &= ~(1 << self->GPIO_bit);
        break;
    
    case GPIO_OUTPUT:
        self->GPIO_pGPIOx->DDRx |= (1 << self->GPIO_bit);
        break;
    }
}

GPIO_responsecode_t gpio_write(GPIO_handle_t* self, GPIO_state_t state)
{
    if (!GPIO_CHECKOUTPUT(self)) return GPIO_ERR_DIR_INVALID;

    switch (state)
    {
    case GPIO_HIGH:
        self->GPIO_pGPIOx->PORTx |= (1 << self->GPIO_bit);
        break;
    
    case GPIO_LOW:
        self->GPIO_pGPIOx->PORTx &= ~(1 << self->GPIO_bit);
        break;
    }

    return GPIO_OK;
}

uint8_t gpio_read(GPIO_handle_t* self)
{
    if (!GPIO_CHECKINPUT(self)) return ERR;

    return (self->GPIO_pGPIOx->PINx & (1 << self->GPIO_bit)) ? 1 : 0;
}

GPIO_responsecode_t gpio_pullup(GPIO_handle_t* self, uint8_t enable)
{
    if (!GPIO_CHECKINPUT(self)) return GPIO_ERR_PULLUP_DIR;

    switch (enable)
    {
    case 1:
        self->GPIO_pGPIOx->PORTx |= (1 << self->GPIO_bit);
        break;
    
    case 0:
        self->GPIO_pGPIOx->PORTx &= ~(1 << self->GPIO_bit);
        break;
    }

    return GPIO_OK;
}
