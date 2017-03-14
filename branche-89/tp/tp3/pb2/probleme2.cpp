/*
 * Travail pratique 3
 * Section 01
 * Equipe 89
 * Date : 26 Janvier 2017
 * Nom du programme : Code du probleme 2 du TP3
 * Auteurs : Guillaume Renaud et Yann-Joel Dorsainville Tessier
 * Description: Allume une DEL lorsqu'on appuie sur un bouton-poussoir.
 */

/*
 * Tableau des etats:
 * Etat present | PIND | Etat suivant | PORTB
 * INIT         | 0x00 | INIT         | 0x02
 * INIT         | 0x04 | E1           | 0x01/0x02
 * E1           | 0x04 | E1           | 0x01/0x02
 * E1           | 0x00 | E2           | 0x01
 * E2           | 0x00 | E2           | 0x01
 * E2           | 0x04 | E3           | 0x02
 * E3           | 0x04 | E3           | 0x02
 * E3           | 0x00 | E4           | 0x00
 * E4           | 0x00 | E4           | 0x00
 * E4           | 0x04 | E5           | 0x01
 * E5           | 0x04 | E5           | 0x01
 * E5           | 0x00 | INIT         | 0x02
 */

// Valeurs possibles du PORTB : 0x00 = 0, 0x01 = vert, 0x02 = rouge.

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode lecture

	enum etat {INIT, E1, E2, E3, E4, E5} e = INIT;

	for (;;) // Boucle infinie.
	{
		switch (e)
		{
			case INIT : // Etat initial: La DEL est rouge et on va en E1 si le bouton est appuye
				PORTB = 0x02;
				if(PIND & 0x04)
				{
					_delay_ms(1);
					if(PIND & 0x04)
					{
						e = E1;
					}
				}
			break;
			case E1 : // Etat E1: la DEL est ambree et on va en E2 si le bouton est relache
				PORTB = 0x01;
				_delay_ms(3); // Un delai de 3ms pour le vert car vert plus faible que rouge
				PORTB = 0x02;
				_delay_ms(1);
				if((PIND & 0x04) == 0)
				{
					e = E2;
				}
			break;
			case E2 : // Etat E2: la DEL est verte et on va en E3 si le bouton est appuye.
				PORTB = 0x01;
				if(PIND & 0x04)
				{
					_delay_ms(1);
					if(PIND & 0x04)
					{
						e = E3;
					}
				}
			break;
			case E3 : // Etat E3: la DEL est rouge et on va en E4 si le bouton est relache.
				PORTB = 0x02;
				if((PIND & 0x04) == 0)
				{
					e = E4;
				}
			break;
			case E4: // Etat E4: la DEL est etteinte et on va en E5 si le bouton est appuye
				PORTB = 0;
				_delay_ms(10); // Le delai ici nous empeche de cliquer rapidement et d'aller directement a l'etat E5
				if(PIND & 0x04)
				{
					_delay_ms(1);
					if(PIND & 0x04)
					{
						e = E5;
					}
				}
			break;
			case E5: // Etat E5: la DEL est verte et on va en INIT si le bouton est relache.
				PORTB = 0x01;
				if((PIND & 0x04) == 0)
				{
					e = INIT;
				}
			break;
		}
	}
	return 0;
}
