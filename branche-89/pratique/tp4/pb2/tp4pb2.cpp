/*
 * Travail pratique 4
 * Section 01
 * Equipe 89
 * Date: 4 mars 2017
 * Nom du programme: tp4pb2
 * Auteurs: Guillaume Renaud
 */
#define F_CPU			8000000UL
#define DIR_FWD_LOW		0x00
#define DIR_FWD_HIGH	0x01
#include <avr/io.h>
#include <util/delay_basic.h>
/* programme principal */
int main(void)
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0xff; // PORT D est en mode sortie
	uint16_t i;
	for(;;)  // boucle sans fin
	{
		i = 0x78; // 2 sec @ 60Hz
		for(; i > 0x00; i--) // boucle pour 2s @ 60Hz pour PWM @ 0%
		{
			PORTC = DIR_FWD_LOW;

			/* 0x8235 = 33 333 => 1 / F_CPU * 4 cycles d'horloge par increment
			de 1 de _delay_loop_2 * 33 333 = 16.6665ms = 60Hz */
			_delay_loop_2(0x8235);
		}
		for(; i < 0x78; i++) // boucle pour 2s @ 60Hz pour PWM @ 25%
		{
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(0x61a8); // 75% de 0x8235
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0x208d); // 25% de 0x8235
		}
		for(; i > 0x00; i--) // boucle pour 2s @ 60Hz pour PWM @ 50%
		{
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(0x411a); // 50% de 0x8235
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0x411b); // 50% de 0x8235
		}
		for(; i < 0x78; i++) // boucle pour 2s @ 60Hz pour PWM @ 75%
		{
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(0x208d); // 25% de 0x8235
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0x61a8); // 75% de 0x8235
		}
		for(; i > 0x00; i--) // boucle pour 2s @ 60Hz pour PWM @ 100%
		{
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0x8235);
		}
		i = 0x320; // 2 sec @ 400Hz
		for(; i > 0x00; i--) // boucle pour 2s @ 400Hz pour PWM @ 0%
		{
			PORTC = DIR_FWD_LOW;

			/* 0x1388 = 5 000 => 1 / F_CPU * 4 cycles d'horloge par increment
			de 1 de _delay_loop_2 * 5 000 = 2.5ms = 400Hz */
			_delay_loop_2(0x1388);
		}
		for(; i < 0x320; i++) // boucle pour 2s @ 400Hz pour PWM @ 25%
		{
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(0xea6); // 75% de 0x1388
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0x4e2); // 25% de 0x1388
		}
		for(; i > 0x00; i--) // boucle pour 2s @ 400Hz pour PWM @ 50%
		{
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(0x9c4); // 50% de 0x1388
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0x9c4); // 50% de 0x1388
		}
		for(; i < 0x320; i++) // boucle pour 2s @ 400Hz pour PWM @ 75%
		{
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(0x4e2); // 25% de 0x1388
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0xea6); // 75% de 0x1388
		}
		for(; i > 0x00; i--) // boucle pour 2s @ 400Hz pour PWM @ 100%
		{
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(0x1388);
		}
	}
	return 0;
}
