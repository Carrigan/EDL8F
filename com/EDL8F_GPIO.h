#ifndef EDL8F_GPIO_H
#define EDL8F_GPIO_H

#include "EDL8F_types.h"
#include "EDL8F_pindefs.h"

// Setup Stuff
void gpio_setup();
void gpio_pinMode(Pin_t pPin, PinMode_t pMode);

// Digital Reads
unsigned int gpio_read(unsigned int pMask);
unsigned int gpio_readPin(Pin_t pPin);

// Digital Writes
void gpio_write(unsigned int pMask, unsigned int pValue);
void gpio_setPin(Pin_t pPin);
void gpio_clearPin(Pin_t pPin);

#endif
