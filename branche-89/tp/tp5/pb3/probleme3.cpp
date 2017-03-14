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

enum etat {INIT, E1, E2, E3, E4} e = INIT;

void ajustementPWM ( uint8_t rapport )
{
	// mise a un des sorties OC1A et OC1B sur comparaison
	// reussie en mode PWM 8 bits, phase correcte
	// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
	// page 130 de la description technique du ATmega324PA)
	TCCR1A = 0xF2 ;
	OCR1A = rapport ;
	OCR1B = rapport ;

	// division d'horloge par 8 - implique une frequence de PWM fixe
	TCCR1B = 0x02 ;
	TCCR1C = 0;
}

int main ()
{
		DDRA = 0xFF;
		DDRB = 0xFF;
		DDRC = 0xFF;
		DDRD = 0x00;
		
		rapportPWM = 0x00;

		   for (;;) // Boucle infinie.
		{
				switch (e)
				{
						case INIT : // PWM 0%
							if( PIND & 0x04 )
							{
								_delay_ms( 30 );
								if ( PIND & 0x04 ) // Anti-rebonds
								{
									e = E1;
								}
							}
						break;
						case E1 : // PWM 0%  
							ajustementPWM( rapportPWM );
							_delay_ms(2000);
							e = E1;
						break;
						case E2 : // PWM 25%
							rapportPWM = 0x40;
							ajustementPWM( rapportPWM );
							_delay_ms(2000);
							e = E2;
						break;
						case E3 : // PWM 50%
							rapportPWM = 0x80;
							ajustementPWM( rapportPWM );
							_delay_ms(2000);
							e = E3;
						break;
						case E4 : // PWM 75%
							rapportPWM = 0xC0;
							ajustementPWM( rapportPWM );
							_delay_ms(2000);
							e = E2;
						break;
						case E5 : // PWM 100%
							rapportPWM = 0xFF;
							ajustementPWM( rapportPWM );
							_delay_ms(2000);
							e = INIT;
						break;
				}
				
		}
		return 0;
}