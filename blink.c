#include <avr/io.h>
#include <util/delay.h>
 
#define BAUD 9600UL
#include <util/setbaud.h>

#define BLINK_DELAY_MS 250

int main (void)
{

    /* Initialize UART / set baud rate */
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1<<U2X0);
#else
    UCSR0A &= ~(1<<U2X0);
#endif

    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* Set frame format: 8data 2stop bit */
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);

    /* set pin 5 of PORTB for output*/
    DDRB |= (1<<DDB5);
 
    while(1) {
        /* set pin 5 high to turn led on */
        PORTB |= (1<<PORTB5);
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 5 low to turn led off */
        PORTB &= ~(1<<PORTB5);
        _delay_ms(BLINK_DELAY_MS);
    }

    return 0;
}
