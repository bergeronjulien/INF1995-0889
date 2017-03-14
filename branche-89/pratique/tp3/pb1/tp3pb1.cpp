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
	enum etat {INIT, E1, E2};
	uint8_t compteur = 0;
	uint8_t i = 0;
	etat e = INIT;
	for(;;)  // boucle sans fin
	{
		switch(e)
		{
			case INIT:
				PORTC = DEL_ETEINTE;
				if(PIND & 0x04) // antirebond
				{
					_delay_loop_2(20000); // delai de 10ms
					if(PIND & 0x04)
						e = E1; // si bouton correctement enfonce => etat suivant
				}
				break;
			case E1:
				while(PIND & 0x04)
				{
					// ne rien faire tant que le bouton-poussoir reste enfonce
				}
				compteur++; // compteur s'incremente quand le bouton est relanche
				e = INIT; // retourner a la scrutation pour prochaine action bouton
				break;
			case E2:
				PORTC = DEL_ROUGE;
				for(; i < 100; i++) // 100 X 10ms = 1s
					_delay_loop_2(20000); // delai de 10ms
				compteur = 0;
				i = 0;
				e = INIT; // retourner a la scrutation pour prochaine action bouton
				break;
			default:
				e = INIT; // assure l'etat INIT
		}
		if(compteur > 4)
			e = E2; // passe a l'etat E2 si le bouton a ete appuye plus de 4 fois
	}
	return 0;
}