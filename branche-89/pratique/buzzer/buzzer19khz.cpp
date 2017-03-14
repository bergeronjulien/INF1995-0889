/*
 * Travail pratique 2
 * Section 01
 * Equipe 89
 * Date : 1er mars 2017
 * Nom du programme : Controle DEL
 * Auteurs : Guillaume Renaud
 */
#define F_CPU			8000000UL

#include <avr/io.h>
#include <util/delay_basic.h>

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode sortie
  for(;;)  // boucle sans fin
  {
	if(PIND & 0x04)
	{
		_delay_loop_2(20000); // delai antirebond
		if(PIND & 0x04)
		{
			while(PIND & 0x04) // tant que le bouton est enfonce
			{
				PORTC = 0x01;
				_delay_loop_2(50); // frequence de 16 666Hz
				PORTC = 0x02;
				_delay_loop_2(50);
			}
			PORTC = 0x00;
		}
  	}
  }
  return 0;
}
