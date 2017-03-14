/*
 * Test sur les ports et les broches
 * Section 01
 * Equipe 89
 * Date: 14 mars 2017
 * Nom du programme: port_test
 * Auteurs: Guillaume Renaud
 */
#include <avr/io.h>
int main()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0xff; // PORT D est en mode sortie
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	PORTD = 0b00000000;
	return 0;
}
