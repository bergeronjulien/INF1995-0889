/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 * 
 * Fichier: tp3_1.cpp
 * Par: Julien Bergeron (1829496) et Loic Bellemare-Alford (1846135)
 * Fait le: 27 janvier 2017
 * Derni're modification: 27 janvier 2017
 */

/*
 * 
 * Explications : 
 *     - BTN :
 *          0 : Le bouton n'est pas pese
 *          1 : Le bouton est pese
 * 
 *  ETAT PRESENT | BTN | ETAT SUIVANT | SORTIE (couleur)
 * -------------------------------------------------------
 *     INIT      |  0  |     INIT     |      ETEINTE
 * -------------------------------------------------------
 *     INIT      |  1  |      E1      |      ETEINTE
 * -------------------------------------------------------
 *      E1       |  0  |      E2      |      ETEINTE
 * -------------------------------------------------------
 *      E1       |  1  |      E2      |      ETEINTE
 * -------------------------------------------------------
 *      E2       |  0  |      E2      |      ETEINTE
 * -------------------------------------------------------
 *      E2       |  1  |      INIT    |      VERTE
 * -------------------------------------------------------
 */


#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  uint8_t compteur = 0; 
  bool etat = false;

  PORTB = 0x00;

  for(;;)  // boucle sans fin
  {

	_delay_ms (10);   


	if(compteur == 5) {
		PORTB = 0x01;
		_delay_ms (1000);
		compteur = 0;
		PORTB = 0x00;
	} 

	if(PIND & 0x04 ){

		if(!etat) {
			etat = true;
			compteur++;
		} 
		
	} else {
		if(etat)
			etat = false;
	}

 	

    

  }
  return 0; 
}

