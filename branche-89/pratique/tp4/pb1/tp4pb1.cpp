/*
 * Travail pratique 4
 * Section 01
 * Equipe 89
 * Date: 2 mars 2017
 * Nom du programme: tp4pb1
 * Auteurs: Guillaume Renaud
 */
#define F_CPU			8000000UL
#define DEL_ETEINTE		0x00
#define DEL_ROUGE		0x01
#define DEL_VERTE		0x02
#include <avr/io.h>
#include <util/delay_basic.h>
/* programme principal */
int main()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0xff; // PORT D est en mode sortie
	uint16_t i = 0x00;
	uint8_t j = 0x00;
	uint16_t k = 0x00;
	for(;;)  // boucle sans fin
	{
		while(i < 1000) // 1000 iterations X 3ms = 3 000ms => 3s en theorie
		{
			for(j = 0; j < 0x03; j++) // boucle pour 3ms
			{
				/* duree de 1ms = periode de 1ms => frequence de 1kHz */
				PORTC = DEL_ROUGE;
				for(k = 1000; k > i; k--) // 500us
					_delay_loop_2(0x01);
				PORTC = DEL_ETEINTE;
				for(k = 0; k < i; k++)
					_delay_loop_2(0x01); // 500us
				/* fin duree de 1ms */
			}
			i++;
		}
	}
	return 0;
}