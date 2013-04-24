#Event Driven LPC800 Framework

## Purpose
The purpose of the Interrupt Driven LPC800 Framework (IDL8F) is to provide a 
simple interrupt driven framework for the LPC800 microcontroller. The IDL8F
manages events and provides language for users to implement
non-blocking, energy efficient solutions. This framework aims to be as user
friendly as Arduino- using a similar setup() function. Instead of a synchronous
looping function which controls program flow, the user defines which events will
wake the processor, and what the processor should do before falling back asleep. 
Since the LPC800 uses a switch matrix for all of its peripherals, this library
will also provide a routing function which allows the user to configure where
peripherals are located from within code.

Please see the Examples section for the intended use of this library.

## Modules

- EventManager Module
  - Queue module which accepts data during interrupts to process later, in order.
  - Contains two seperate buffers: an `Event_t` buffer and a `uint8_t` buffer. Each `Event_t` is allows to save as much data as it wants into the `uint8_t` buffer. For example, a UART might save one byte of received data, but the I2C bus might need to save a full buffer.

## Examples

Since this project is still in its infancy, the examples section is meant as the _intent_ of this framework. All examples are subject to change.

### Example 1: Blinky

    void setup()
    {
        pinMode(P1, OUTPUT);
        setupTimer(TIMER0, 1, unit_s);
        wakeupOn(TIMER0);
    }

    onTIMER0()
    {
        togglePin(P1);
    }

### Example 2: UART Loopback

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
