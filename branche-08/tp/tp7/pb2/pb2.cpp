/*
 * Fichier: pb1.cpp
 * Par: Julien Bergeron (1829496) et Loic Bellemare-Alford (1846135)
 * Description: Change la couleur en utilisant une source analogique phovoltaïque.
 * Fait le: 27 février 2017
 * Derni're modification: 27 février 2017
 */


/*
8 bits = 255 valeurs

4.4V normal
2.8V fonc < 140
4.8V Lumière max > 240
*/

#define VERT 0x02
#define ROUGE 0x01

#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>
#include "can.h"


int main()
{
  	DDRA = 0x00; // PORT A est en mode sortie
  	DDRB = 0xff; // PORT B est en mode sortie
  	
  	can resistance = can();
	
	for(;;){

	  uint16_t valeur = resistance.lecture(0);
	  valeur = valeur >> 2; // Ramène la valeur à 8bits
	  
	  if(valeur > 240) {
	    PORTB = ROUGE;
	  } else if (valeur < 180){
	    PORTB = VERT;
	  } else {
	    PORTB = 0x01;
	    _delay_ms(1);
	    PORTB = 0x02;
	    _delay_ms(4);
	  }
	  
	    
	}


  return 0; 
}

