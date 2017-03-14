/*

 * Fichier: pb1.cpp
 * Par: Julien Bergeron (1829496) et Loic Bellemare-Alford (1846135)
 * Description: Démarre une séquence de lumière selon le pression du bouton.
 * Fait le: 2 février 2017
 * Derni're modification: 27 février 2017
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

    PORTB = 0x00; // Initialisation de la DEL
    int compteur = 0;
	  bool allumee = false;
	
	  for(;;){

	    if(!(PIND & 0x04) && !allumee) {
	      _delay_ms(30); // Attirebond
	    
	      if(!(PIND & 0x04)) {
	        
	        do {
	            _delay_ms(100);
	            compteur++;
	        } while (!(PIND & 0x04) && compteur < 120);
	        
	        allumee = true;
	        compteur /= 2;
	        
	        for (int i=0; i<2; i++){
				    PORTB = 0x01;
				    _delay_ms(125);
				    PORTB = 0x00;
				    _delay_ms(125);
			    }
			    
	        _delay_ms(2000);
	         
	     }
	      
	    } 
	  
	    if(allumee && compteur > 0) {
	      PORTB = 0x02;
	      _delay_ms(250);
	      PORTB = 0x00;
	      _delay_ms(250);
	      compteur--;
	    } else if (allumee && compteur == 0) {
	      PORTB = 0x02;
	      _delay_ms(1000);
	      PORTB = 0x00;
	      allumee = false;
	    }
	  
	    
	  }


  return 0; 
  
}

