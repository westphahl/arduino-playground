#include <avr/io.h>
#include <util/delay.h>
 
#define BAUD 19200
#include <util/setbaud.h>

#define BLINK_DELAY_MS 250

int main (void)
{

    /* Initialize UART */
    UBRR0H = UBRRH_VALUE; // Set baud rate
    UBRR0L = UBRRL_VALUE;

    UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable receiver and transmitter
    // TODO: Change frame format to 8n1
    UCSR0C = (1<<USBS0)|(1<<UCSZ00); // Frame format: 8data 2stop bits

    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);
 
    while(1) {
        /* set pin 5 high to turn led on */
        PORTB |= _BV(PORTB5);
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 5 low to turn led off */
        PORTB &= ~_BV(PORTB5);
        _delay_ms(BLINK_DELAY_MS);
    }

    return 0;
}
