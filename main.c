/*
Author: Jacob Anderson
RedID: 827419418
Date: February 10, 2023
Assignment: Lab 2
Description: Transmit a RedID through a serial connection.
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL  //16Mhz clock speed for CPU
#define BAUD 9600  //define Baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL) - 1)  //setting baud rate
#include <util/delay.h>

void uart_init(void){
	UBRR0H = (BAUDRATE >> 8);  //setting the high register
	UBRR0L = BAUDRATE;  //setting the low register
	UCSR0B |= (1 << TXEN0);  //enabling transmission
	UCSR0C |= (1 << UCSZ00 | 1 << UCSZ01);  //setting the 8 bit data format
}

void transmit(char RedID){
	while (!(UCSR0A & 1 << UDRE0));  //looping until register is free
	UDR0 = RedID;  //loading RedID in register to transmit
}

int main(void){
	uart_init();  //starting the uart_init function
	char RedID[] = "827419418\n\r";  //declaring RedID as array
    while (1){
		for(int i = 0; i < sizeof(RedID); i++){
			transmit(RedID[i]);  //passing the RedID array to the transmit function
			_delay_ms(50);
		}
    }
}

