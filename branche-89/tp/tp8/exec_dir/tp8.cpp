/*
 * Code pour tester les makefiles et la librairie
 */
#define F_CPU			8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include "../include/moteurA.h"
#include "../include/timer16.h"
#include "../include/del.h"
volatile uint8_t minuterieExpiree = 0x00;
ISR(TIMER1_COMPA_vect)
{
	minuterieExpiree = 0x01;
}
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
	MoteurA moteurDroit;
	Timer16 minuterie;
	Del delLibre;
	uint8_t i = 0;
	moteurDroit.stop();
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.rev(0x40);
	for(; i > 0x00; i--) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.rev(0x80);
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.fwd(0xc0);
	for(; i > 0x00; i--) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	moteurDroit.fwd(0xff);
	for(; i < 0x64; i++) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	minuterie.setmode(2);
	minuterie.setOCR1A(0x8000);
	minuterie.setclk(5);
	while(!minuterieExpiree)
	{
		delLibre.vert();
	}
	delLibre.rouge();
	for(; i > 0x00; i--) // 100 iterations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	delLibre.off();
	return 0;
}
