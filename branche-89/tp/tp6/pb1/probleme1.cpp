/*
 * Travail pratique 6
 * Section 01
 * Equipe 89
 * Date : 20 Février 2017
 * Nom du programme : Code du probleme 1 du TP6
 * Auteurs : Guillaume Renaud et Yann-Joel Dorsainville Tessier
 * Description: 
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <memoire_24.h>
#include <memoire_24.cpp>

int main ()
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x00;

	Memoire24CXXX mem;
	
	mem.init();
	
	mem.ecriture(0x00, 0x45); // Valeur de E en ASCII
	_delay_ms(5);
	
	mem.lecture();
	
	if ()
	{
	
	
	return 0;
}
