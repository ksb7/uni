#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t adc_result1 = 0;
volatile uint16_t adc_result3 = 0;
volatile uint8_t newData = 0;
volatile uint16_t skip_count = 0;

#define PRINT_EVERY 500   /* print one line every N samples */

void adc_start(uint8_t ch)
{
	ch &= 0x07;
	ADMUX = (ADMUX & 0xF8) | ch;
	ADCSRA |= (1<<ADSC);
}

ISR(ADC_vect)
{
	/* ADC1 just finished */
	if ((ADMUX & 0x0F) == 0x01)
	{
		adc_result1 = ADC;
		adc_start(3); /* switch to ADC3 */
	}
	else /* ADC3 just finished */
	{
		adc_result3 = ADC;
		adc_start(1);  /* switch to ADC1 */
		newData = 1;
	}
}

void tx(char c)
{
	while (!(UCSRA & (1 << UDRE)));
	UDR = c;
}

void tx_str(const char *s)
{
	while (*s) tx(*s++);
}

void tx_uint(uint16_t v)
{
	char buf[6];
	uint8_t i = 5;
	buf[i] = '\0';
	if (v == 0) { buf[--i] = '0'; }
	else { while (v) { buf[--i] = '0' + (v % 10); v /= 10; } }
	tx_str(buf + i);
}

void display(uint16_t r1, uint16_t r3, uint16_t out)
{
	/* ADC1 */
	tx_str("ADC1: ");
	tx_uint(r1);
	tx_str("  ADC3: ");
	/* ADC3 */
	tx_uint(r3);
	tx_str("  Out: ");
	/* weighted output */
	tx_uint(out);
	tx_str("\r\n");
}

void USART_Init(unsigned int ubrr)
{
	/* write UBRRH first */
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	/* enable TX */
	UCSRB = (1<<TXEN);
	/* write UCSRC — overwrites UBRRH due to shared address */
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	/* restore UBRRH immediately after */
	UBRRH = (unsigned char)(ubrr >> 8);
}

int main(void)
{
	/* Configure PORTA, PORTB, PORTC as input */
	DDRA = 0;
	DDRB = 0;
	DDRC = 0;
	/* Configure PORTD as input except for TX pin */
	DDRD = (1<<PD1);

	/* Set PORTA as pull up resistor except for input pins */
	PORTA = ~((1<<PA1)|(1<<PA3));
	/* Set all other ports as pull up resistor */
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;

	/* ADC init */
	/* AVcc reference, start on ADC1 */
	ADMUX  = (1<<REFS0) | 0x01;
	/* Enable ADC, interrupt, prescaler 128 */
	/* 11.0592MHz / 128 = 86kHz (within 50-200kHz) */
	ADCSRA = (1<<ADEN)|(1<<ADIE)|
	(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

	/* UART init */
	USART_Init(287);
	/* Start the first ADC conversion on pin 1 */
	adc_start(1);
	sei(); /* Enable interrupts */

	while (1)
	{
		if (newData)
		{
			newData = 0;
			if (++skip_count < PRINT_EVERY) continue;
			skip_count = 0;

			cli();
			uint16_t r1 = adc_result1;
			uint16_t r3 = adc_result3;
			sei();

			uint16_t out = 2 * r1 + r3;
			display(r1, r3, out);
		}
	}
	return 0;
}