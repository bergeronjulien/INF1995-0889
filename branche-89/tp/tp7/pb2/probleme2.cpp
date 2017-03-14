/*
 * Travail pratique 7
 * Section 01
 * Equipe 89
 * Date : 23 Février 2017
 * Nom du programme : Code du probleme 2 du TP7
 * Auteurs : Guillaume Renaud et Yann-Joel Dorsainville Tessier
 * Description: Introduction a l'utilisation des capteurs sur le breadboard
 */
// ce code respecte la convention de 80 caracteres par ligne de code
#define F_CPU          8000000UL
#define DEL_ROUGE      0x01
#define DEL_VERTE      0x02
#define DEL_ETEINTE    0x00
#define LUMIERE_FORTE  0xF5 // valeur equivalente a 4.80V (11 1101 0111 = 983)
#define LUMIERE_FAIBLE 0xD8 // valeur equivalente a 4.22V (11 0110 0000 = 864)

#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

int main ()
{
	DDRA = 0x00; // PORT A est en mode entree
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0xff; // PORT D est en mode sortie

	uint8_t valNum = 0;

	can photoresist = can(); // creation objet pour utilisation du ADC

	for (;;) // boucle infinie
	{
		/* la tension par rapport a la masse du fil bleu est lue par la
		   broche 1 (port 0) du port A. Ce port est relie au ADC du
		   ATMega324PA. En faisant une lecture du DAC pour la broche 1
		   ([objet].lecture(0)), nous obtenons la conversion numerique de
		   la tension (analogique) lue par la broche 1 sur une valeur de
		   10 bits. Nous voulons que conserver les 8 bits les plus
		   significatifs (car valNum est un entier non signe de 8 bits) de la
		   valeur numerique retournee. Nous faisons donc un deplacement de bits
		   de 2 positions vers la droite ce qui elemine les 2 bits les moins
		   significatifs */
		valNum = ((photoresist.lecture(0)) >> 2);

		/* la tension de reference pour le ADC est controlee par le
		   potentiometre. En effet, celui-ci ajuste la tension a la
		   broche AREF du ATMega324PA ce qui donne au ADC une plage
		   de tension de 0 a 5V inclusivement. Le ADC va diviser
		   cette plage en 1024 valeurs (10 bits) ce qui veut dire que
		   chaque incrementation de 0.0049V environ de la tension lue
		   a la broche 1 correspond a une incrementation de 1 de la
		   valeur numerique retournee par le ADC */

		if(valNum >= LUMIERE_FORTE) // tension de 4.80V et plus
		{
			PORTC = DEL_ROUGE;
		}
		else if(valNum >= LUMIERE_FAIBLE) // tension entre 4.79V et 4.23V
		{
			for(uint8_t i = 0; i < 0xf; i++) // boucle pour couleur ambree
			{
				PORTC = DEL_VERTE;
				_delay_us(30); // pour compenser la faible luminosite du vert
				PORTC = DEL_ROUGE;
				_delay_us(10);
			}
		}
		else // sinon c'est que la tension est inferieure a 4.23V environ
		{
			PORTC = DEL_VERTE;
		}
	}
	return 0;
}
