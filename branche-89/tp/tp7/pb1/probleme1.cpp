/*
 * Travail pratique 7
 * Section 01
 * Equipe 89
 * Date : 23 Février 2017
 * Nom du programme : Code du probleme 1 du TP7
 * Auteurs : Guillaume Renaud et Yann-Joel Dorsainville Tessier
 * Description: Introduction a l'utilisation des capteurs sur le breadboard
 */
// ce code respecte la covention de 80 caracteres par ligne de code
#define F_CPU        8000000UL
#define DEL_ROUGE    0x01
#define DEL_VERTE    0x02
#define DEL_ETEINTE  0x00

#include <avr/io.h>
#include <util/delay.h>

enum etat {INIT, E1, E2, E3} e = INIT;

int main ()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode entree

	uint8_t compteur = 0x0;

	for (;;) // boucle infinie
	{
		switch (e)
		{
			case INIT: // etat initial, scrutation du bouton poussoir
				_delay_ms(30); // delai pour rebond

				/* OR sur 0000 0000 (bouton enfonce) avec 0000 0000 donne
				   un faux logique, !faux logique = vrai logique */
				if(!(PIND | 0x0))
				{
					for(compteur = 0; compteur < 120; compteur++)
					{
						/* AND sur 0000 0100 (bouton relache) avec 1111 1111 */
						if(PIND & 0xff) //srutation du bouton (si relache)
						{
							e = E1; // etat suivant si bouton relache
							break;
						}
						_delay_ms(100); // compteur incremente a chaque 0.1 sec
					}
					e = E1; // etat suivant si compteur atteint 120
				}
			break; // fin etat INIT

			case E1: // etat DEL allume et clignote

				/* boucle pour faire clignoter durant 0.5 sec */
				for (uint8_t i = 0; i < 5; i++)
				{
					PORTC = DEL_VERTE;
					_delay_ms(50);
					PORTC = DEL_ETEINTE;
					_delay_ms(50);
				}
				_delay_ms(2000); // on attend 2 sec...

				/* on clignote la DEL autant de fois que compteur / 2
				   et chaque clignotement dure 0.5 sec */
				for(compteur /= 2; compteur > 0; compteur--)
				{
					PORTC = DEL_ROUGE;
					_delay_ms(250);
					PORTC = DEL_ETEINTE;
					_delay_ms(250);
				}
				PORTC = DEL_VERTE;
				_delay_ms(1000);
				PORTC = DEL_ETEINTE;
				e = INIT; // on retourne a la scrutation du bouton poussoir
			break; // fin etat E1
			default:
				e = INIT; // assure l'etat INIT
		}
	}
	return 0;
}
