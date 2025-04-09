#define F_CPU 1000000

#include<avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>

volatile unsigned char result;

ISR(ADC_vect){
	result=ADCH;	
}

void UART_init(void){
		UCSRA = 0b00000000;
		UCSRB = 0b00001000;
		UCSRC = 0b10000110;
		UBRRL = 0x12;
	UBRRH = 0x00;
}

void UART_send(unsigned char data){
		while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = data;
}

int main(void){
    ADCSRA=0b10001101;
    ADMUX=0b11100000;
    UART_init();
    sei();
    
    while (1){
		ADCSRA|=1<<ADSC;
		UART_send(result);
    }
}
