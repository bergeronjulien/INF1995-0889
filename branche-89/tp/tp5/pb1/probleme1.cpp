/*
 * Travail pratique 5
 * Section 01
 * Equipe 89
 * Date : 9 Février 2017
 * Nom du programme : Code du probleme 1 du TP5
 * Auteurs : Guillaume Renaud et Yann-Joel Dorsainville Tessier
 * Description: Allume une DEL lorsqu'on appuie sur un bouton-poussoir avec concept d'interruptions.
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


const uint8_t INIT = 0, E1 = 1, E2 = 2, E3 = 3, E4 = 4, E5 = 5, E6 = 6;
volatile uint8_t etat = INIT;

ISR ( INT0_vect )
{
	_delay_ms(30);
	//if(PIND & 0x04)
	//{
		etat++;
	//}
	
	EIFR |= (1 << INTF0) ;
}


void initialisation (void)
{
	cli ();

	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode entree

	EIMSK |= _BV(INT0);
	
	EICRA |= _BV(ISC00);

	sei ();
}

int main ()
{
	initialisation ();
	
	// Possibles couleurs de la DEL
	const uint8_t ROUGE       = 0x02;
	const uint8_t VERT        = 0x01;
	const uint8_t ETTEINTE    = 0x00;
	
	for (;;) // Boucle infinie.
	{
		switch (etat)
		{
			case INIT : // Etat initial: La DEL est rouge et on va en E1 si le bouton est appuye
				PORTB = ROUGE;
			break;
			case E1 : // Etat E1: la DEL est ambree et on va en E2 si le bouton est relache
				PORTB = VERT;
				_delay_ms(3); // Un delai de 3ms pour le vert car vert plus faible que rouge
				PORTB = ROUGE;
				_delay_ms(1);
			break;
			case E2 : // Etat E2: la DEL est verte et on va en E3 si le bouton est appuye.
				PORTB = VERT;
			break;
			case E3 : // Etat E3: la DEL est rouge et on va en E4 si le bouton est relache.
				PORTB = ROUGE;
			break;
			case E4: // Etat E4: la DEL est etteinte et on va en E5 si le bouton est appuye
				PORTB = ETTEINTE;
			break;
			case E5: // Etat E5: la DEL est verte et on va en INIT si le bouton est relache.
				PORTB = VERT;
			break;
			case E6:
				etat = INIT;
			break;
		}
		
	}
	return 0;
}
