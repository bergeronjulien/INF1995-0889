/*
 * Travail pratique 3
 * Section 01
 * Equipe 89
 * Date : 26 Janvier 2017
 * Nom du programme : Code du probleme 1 du TP3
 * Auteurs : Guillaume Renaud et Yann-Joel Dorsainville Tessier
 * Description: Allume une DEL lorsqu'on appuie sur un bouton-poussoir.
 */

/*
 * Tableau des etats:
 * Etat present | PIND | compteur | Etat suivant | PORTB
 * INIT         | 0x00 | X        | INIT         | 0x00
 * INIT         | 0x04 | X        | E1           | 0x00
 * INIT         | 0x00 | 5        | E2           | 0x00
 * E1           | 0x04 | X        | E1           | 0x00
 * E1           | 0x00 | X        | INIT         | 0x00
 * E2           | X    | X        | INIT         | 0x02
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode lecture

	unsigned long compteur = 0; // Le compteur est initialise a 0, c'est un compteur de 32 bits
	enum etat {INIT, E1, E2} e = INIT;

	for(;;) // Boucle infinie
	{
		switch(e)
		{
			case INIT : // Etat initial, verifie si le bouton-poussoir est bien pousse, si oui on passe a l'etat E1
				if(compteur == 5) // Une fois que le compteur atteint 5, il faut aller a l'etat E2
				{
					e = E2;
				}
				if(PIND & 0x04) // Verification pour antirebonds
				{
					_delay_ms(1);
					if(PIND & 0x04)
					{
						e = E1;
					}
				}
			break;
			case E1 : // Second etat, si le bouton-poussoir a ete relache, le compteur s'incremente et on revient a l'etat initial
				if((PIND & 0x04) == 0)
				{
					compteur++;
					e = INIT;
				}
			break;
			case E2 : // Troisieme etat, allume la DEL en rouge  pendant une seconde
				PORTB = 0x02;
				_delay_ms(1000);
				compteur = 0;
				e = INIT;
				PORTB = 0;
			break;
		}
	}
	return 0;
}
