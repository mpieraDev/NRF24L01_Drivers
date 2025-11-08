#include "gpio_atmega328p.h"

#include <stdint.h>
#include "registers_atmega328p.h"

#define GPIO_CHECKBIT(bit) ((bit < 8) ? 1 : 0)
#define GPIO_CHECKOUTPUT(selfptr) ((*(selfptr)->GPIO_ddport & (1 << (selfptr)->GPIO_bit)) ? 1 : 0)
#define GPIO_CHECKINPUT(selfptr) ((*(selfptr)->GPIO_ddport & (1 << (selfptr)->GPIO_bit)) ? 0 : 1)

#define ERR 2

GPIO_responsecode_t gpio_init(GPIO_handle_t* self, GPIO_port_t port, uint8_t bit)
{
    if (!GPIO_CHECKBIT(bit)) return GPIO_ERR_BIT_RANGE;
        
    self->GPIO_bit = bit;

    switch (port) {
        case GPIO_PORTB:
            self->GPIO_port   = &PORTB;
            self->GPIO_ddport = &DDRB;
            self->GPIO_pinreg = &PINB;
            break;

        case GPIO_PORTC:
            self->GPIO_port   = &PORTC;
            self->GPIO_ddport = &DDRC;
            self->GPIO_pinreg = &PINC;
            break;

        case GPIO_PORTD:
            self->GPIO_port   = &PORTD;
            self->GPIO_ddport = &DDRD;
            self->GPIO_pinreg = &PIND;
            break;
    }

    return GPIO_OK;
}

void gpio_data_direction(GPIO_handle_t* self, GPIO_direction_t dd)
{
    switch (dd)
    {
    case GPIO_INPUT:
        *(self)->GPIO_ddport &= ~(1 << (self)->GPIO_bit);
        break;
    
    case GPIO_OUTPUT:
        *(self)->GPIO_ddport |= (1 << (self)->GPIO_bit);
        break;
    }
}

GPIO_responsecode_t gpio_write(GPIO_handle_t* self, GPIO_state_t state)
{
    if (!GPIO_CHECKOUTPUT(self)) return GPIO_ERR_DIR_INVALID;

    switch (state)
    {
    case GPIO_HIGH:
        *(self)->GPIO_port |= (1 << (self)->GPIO_bit);
        break;
    
    case GPIO_LOW:
        *(self)->GPIO_port &= ~(1 << (self)->GPIO_bit);
        break;
    }

    return GPIO_OK;
}

uint8_t gpio_read(GPIO_handle_t* self)
{
    if (!GPIO_CHECKINPUT(self)) return ERR;

    return (*(self)->GPIO_pinreg & (1 << (self)->GPIO_bit)) ? 1 : 0;
}

GPIO_responsecode_t gpio_pullup(GPIO_handle_t* self, uint8_t enable)
{
    if (!GPIO_CHECKINPUT(self)) return GPIO_ERR_PULLUP_DIR;

    switch (enable)
    {
    case 1:
        *(self)->GPIO_port |= (1 << (self)->GPIO_bit);
        break;
    
    case 0:
        *(self)->GPIO_port &= ~(1 << (self)->GPIO_bit);
        break;
    }

    return GPIO_OK;
}
