/*
 * Travail pratique 2
 * Section 01
 * Equipe 89
 * Date: 1er mars 2017
 * Nom du programme: tp2pb3
 * Auteurs: Guillaume Renaud
 */
#define F_CPU			8000000UL
#define DEL_ETEINTE		0x00
#define DEL_ROUGE		0x01
#define DEL_VERTE		0x02
#include <avr/io.h>
#include <util/delay_basic.h>
int main()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode entree
	for(;;)  // boucle sans fin
	{
		if(PIND & 0x04)
		{
			_delay_loop_2(20000); // delai antirebond de 10ms
			if(PIND & 0x04)
			{
				while(PIND & 0x04) // tant que le bouton est enfonce
				{
					PORTC = DEL_ROUGE;
					_delay_loop_2(100);
					PORTC = DEL_VERTE;
					_delay_loop_2(300);
				}
				PORTC = DEL_ETEINTE;
			}
		}
	}
	return 0;
}