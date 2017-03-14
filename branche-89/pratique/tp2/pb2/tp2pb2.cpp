/*
 * Travail pratique 2
 * Section 01
 * Equipe 89
 * Date: 1er mars 2017
 * Nom du programme: tp2pb2
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
	DDRD = 0xff; // PORT D est en mode sortie
	uint16_t i = 0;
	for(;;)  // boucle sans fin
	{
		PORTC = DEL_ROUGE;
		for(; i < 100; i++) // boucle pour 1s
			_delay_loop_2(20000); // delai de 10ms
		PORTC = DEL_VERTE;
		for(; i > 0; i--)
			_delay_loop_2(20000);
		for(; i < 5000; i++)
		{
			PORTC = DEL_ROUGE;
			_delay_loop_2(100);
			PORTC = DEL_VERTE;
			_delay_loop_2(300);
		}
		i = 0;
	}
	return 0;
}