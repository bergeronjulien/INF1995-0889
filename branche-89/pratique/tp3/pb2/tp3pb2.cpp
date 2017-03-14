/*
 * Travail pratique 3
 * Section 01
 * Equipe 89
 * Date: 2 mars 2017
 * Nom du programme: tp3pb1
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
	enum etat {INIT, E1, E2, E3, E4, E5};
	etat e = INIT;
	for(;;)  // boucle sans fin
	{
		switch(e)
		{
			case INIT:
				PORTC = DEL_ROUGE;
				if(PIND & 0x04) // scrutation et antirebond
				{
					_delay_loop_2(20000); // delai de 10ms
					if(PIND & 0x04)
						e = E1; // si bouton correctement enfonce => etat suivant
				}
				break;
			case E1:
				while(PIND & 0x04) // DEL reste ambree tant que bouton est enfonce
				{
					PORTC = DEL_ROUGE;
					_delay_loop_2(100);
					PORTC = DEL_VERTE;
					_delay_loop_2(300);
				}
				e = E2; // passe a l'etat suivant si bouton est relache
				break;
			case E2:
				PORTC = DEL_VERTE;
				if(PIND & 0x04) // scrutation et antirebond
				{
					_delay_loop_2(20000); // delai de 10ms
					if(PIND & 0x04)
					{
						PORTC = DEL_ROUGE;
						e = E3; // si bouton correctement enfonce => etat suivant
					}
				}
				break;
			case E3:
				while(PIND & 0x04)
				{
					// ne rien faire tant que le bouton-poussoir est enfonce
				}
				PORTC = DEL_ETEINTE;
				e = E4; // passe a l'etat suivant si bouton est relache
				break;
			case E4:
				if(PIND & 0x04) // scrutation et antirebond
				{
					_delay_loop_2(20000);
					if(PIND & 0x04)
					{
						PORTC = DEL_VERTE;
						e = E5; // si bouton correctement enfonce => etat suivant
					}
				}
				break;
			case E5:
				while(PIND & 0x04)
				{
					// ne rien faire tant que le bouton-poussoir est enfonce
				}
				e = INIT; // retourne a l'etat initial si bouton est relache
			default:
				e = INIT; // assure l'etat INIT
		}
	}
	return 0;
}