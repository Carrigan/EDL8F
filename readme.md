#Event Driven LPC800 Framework

## Purpose
The purpose of the Event Driven LPC800 Framework (EDL8F) is to provide a 
simple interrupt driven framework for the LPC800 microcontroller. The EDL8F
manages events and provides language for users to implement
non-blocking, energy efficient solutions. This framework aims to be as user
friendly as Arduino- using a similar setup() function. Instead of a synchronous
looping function which controls program flow, the user defines which events will
wake the processor, and what the processor should do before falling back asleep. 
Since the LPC800 uses a switch matrix for all of its peripherals, this library
will also provide a routing function which allows the user to configure where
peripherals are located from within code.

Please see the Usage section for framework syntax, and the Examples section for 
the intended use of this library.

## Usage
- void setup(void)
  - This function is called during intialization one time, and should contain the user's initialization code.
- void onPERIPHERALNAME(arg0, arg1, ..., argN)
  - This function is called when an interrupt is processed by the Event Manager. 
  - For example, if a Wakeup Timer interrupt occured, the user's onWKT(void) function will be called.
  - Events such as UART and I2C will return their data using arguments as defined by each peripheral.
- void process(void)
  - This function resembles the loop() function in Arduino, but instead of being called in a repetitive fashion, it is called once all of the events have been handled and the processor is returning to sleep mode.
  - This function is meant to check flags set during interrupts and perform actions accordingly.

## Status

This framework is planned to be used on the LPC800-MAX board from NXP. This board will
provide a cheap and easy way for hobbyists to break into the ARM market. The `brd` folder
contains the gerbers for an LPC812M101FDH20 board which breaks out pins MBed style, 
contains a standard SWD programming header, pulls the boot and reset lines high, and 
provides a decoupling cap. This board was ordered on 4/28/13, and has not yet been tested.

![Board Pictures](http://graphsandwords.com/images/ldip.png)

## Modules

- EventManager Module
  - Queue module which accepts event data during interrupts to process later, in order.
- SystemManager Module
  - Module which builds upon the EDL8F peripheral layer and provides initialization routines and higher level peripheral access.

## Examples

Since this project is still in its infancy, the examples section is meant as the _intent_ of this framework. All examples are subject to change. For any currently working examples, check the examples directory.

### Example 1: Blinky

    void setup()
    {	
    	// Set up pin 11 as a push/pull output.
    	gpio_pinMode(P11, OUTPUT_PUSHPULL);
    	
    	// Set up the Wake-Up Timer to interrupt every 500ms.
    	setupWktTimer(500);
    }
    
    void onWkt()
    {
    	// Toggle the pin
    	gpio_togglePin(P11);
    }

### Example 2: UART Loopback
	// UART code has not been written -- this is the intent of the library.
	
    void setup()
    {
        route(UART_TX0, P1);
        route(UART_RX0, P2);
        setupUart(UART0, 9600, UART_NONE);
        
        wakeupOn(UART0);
    }

    onUART0()
    {
        uint8_t incomingData = uartRead(UART0);
        uartWrite(UART0, incomingData);
    }
