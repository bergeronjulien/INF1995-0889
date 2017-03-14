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


volatile enum etat {INIT, E1, E2, E3, E4, E5} e = INIT;
volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR ( TIMER1_CAPT_vect )
{
	minuterieExpiree = 1;
}

ISR ( INT0_vect )
{
	boutonPoussoir = 1;

	// anti-rebond
	if ( PIND & 0x04 )
	{
		_delay_ms(30);
		if ( PIND & 0x04 )
		{
			// METTRE QQC ICI
		}
	}
}

void partirMinuterie ( uint16_t duree )
{
	minuterieExpiree = 0;
	// mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree specifiee
	TCNT1 = 0 ;
	OCR1A = duree;
	TCCR1A = 0xF1;
	TCCR1B = 0x05;
	TCCR1C = 0;
	TIMSK1 = 0x20 ;
}

void initialisation (void)
{
	cli ();

	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode entree

	EIMSK |= _BV(INT0);
	
	EICRA |= ~_BV(ISC01) | _BV(ISC00);

	sei ();
}

int main ()
{
	initialisation ();

	const uint8_t COULEUR_ROUGE = 0x02;
	const uint8_t COULEUR_VERTE = 0x01;
	
	_delay_ms(10000);
	PORTB = 0x02;
	_delay_ms(100);
	PORTB = 0x00;

	do
	{
		// attendre qu'une des deux variables soit modifiee
		// par une ou l'autre des interruptions.
		partirMinuterie( 0xFFFF ); // CHANGER VALEUR ICI POUR AVOIR 1/10 DE SEC
	}
	while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

	// Une interruption s'est produite. Arreter toute
	// forme d'interruption. Une seule reponse suffit.
	cli ();

	// Verifier la reponse
	if (  )
	{
		// METTRE QQC ICI
	}

	return 0;
}
