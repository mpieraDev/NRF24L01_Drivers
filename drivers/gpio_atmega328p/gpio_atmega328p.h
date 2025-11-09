#ifndef GPIO_ATMEGA328P_H
#define GPIO_ATMEGA328P_H

#include <stdint.h>

typedef struct 
{
    GPIO_RegDef_t*  GPIO_pGPIOx;
    uint8_t         GPIO_bit;

}
GPIO_handle_t;

typedef enum 
{
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD
} 
GPIO_port_t;

typedef enum 
{
    GPIO_LOW,
    GPIO_HIGH
}
GPIO_state_t;

typedef enum 
{
    GPIO_INPUT,
    GPIO_OUTPUT
}
GPIO_direction_t;

typedef enum 
{
  GPIO_OK,
  GPIO_ERR_NULL,
  GPIO_ERR_BIT_RANGE,
  GPIO_ERR_DIR_INVALID,
  GPIO_ERR_PULLUP_DIR,   
} 
GPIO_responsecode_t;

GPIO_responsecode_t gpio_init(GPIO_handle_t* self, GPIO_RegDef_t* pGPIOx, uint8_t bit);
void gpio_data_direction(GPIO_handle_t* self, GPIO_direction_t dd);
GPIO_responsecode_t gpio_write(GPIO_handle_t* self, GPIO_state_t state);
uint8_t gpio_read(GPIO_handle_t* self);
GPIO_responsecode_t gpio_pullup(GPIO_handle_t* self, uint8_t enable);

#endif