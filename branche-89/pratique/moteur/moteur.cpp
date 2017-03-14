/*
 * Travail pratique 4
 * Section 01
 * Equipe 89
 * Date: 4 mars 2017
 * Nom du programme: moteur
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

	//for(;;)  // boucle sans fin
	//{
		for(i = 0; i < 139; i++) // 184.99676 Hz
		{
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(5405);
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(5406);
		}
		for(i = 0; i < 185; i++) // 246.94407 Hz
		{
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(4049);
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(4050);
		}
		for(i = 0; i < 740; i++) // 370.02775 Hz
		{
			PORTC = DIR_FWD_HIGH;
			_delay_loop_2(2703);
			PORTC = DIR_FWD_LOW;
			_delay_loop_2(2702);
		}
	//}
	return 0;
}
