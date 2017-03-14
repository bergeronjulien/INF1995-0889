/*
 * Travail pratique 5
 * Section 01
 * Equipe 89
 * Date: 12 mars 2017
 * Nom du programme: tp5pb3
 * Auteurs: Guillaume Renaud
 */
#define F_CPU			8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include "../include/pwm.h"
void init(void)
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0xff; // PORT D est en mode sortie
	PORTD = 0x00;
}
/* programme principal */
int main(void)
{
	init();
	initPwm();
	uint8_t i = 0;
	pwmA(0x00);
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwmA(0x40);
	for(; i > 0x00; i--) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwmA(0x80);
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwmA(0xc0);
	for(; i > 0x00; i--) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwmA(0xff);
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	return 0;
}
