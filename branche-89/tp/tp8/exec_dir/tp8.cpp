/*
 * code pour tester la librairie prise du tp5
 */
#define F_CPU			8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include "../include/moteurA.h"

void init(void)
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
}

/* programme principal */
int main(void)
{
	init();
	MoteurA moteurDroit();
	uint8_t i = 0;
	moteurDroit.stop;
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.fwd(0x40);
	for(; i > 0x00; i--) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.fwd(0x80);
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.fwd(0xc0);
	for(; i > 0x00; i--) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.fwd(0xff);
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	return 0;
}
