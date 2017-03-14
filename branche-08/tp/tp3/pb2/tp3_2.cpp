/*
 * Nom: Machine a etat
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple de machine a etat simple
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
 *     INIT      |  0  |     INIT     |      ROUGE
 * -------------------------------------------------------
 *     INIT      |  1  |      E1      |      AMBRE
 * -------------------------------------------------------
 *      E1       |  0  |      E2      |      VERT
 * -------------------------------------------------------
 *      E1       |  1  |      E1      |       X
 * -------------------------------------------------------
 *      E2       |  0  |      E2      |       X
 * -------------------------------------------------------
 *      E2       |  1  |       E3     |      ROUGE
 * -------------------------------------------------------
 *      E3       |  0  |      E4      |      VIDE
 * -------------------------------------------------------
 *      E3       |  1  |      E3      |       X
 * -------------------------------------------------------
 *      E4       |  0  |      E4      |       X
 * -------------------------------------------------------
 *      E4       |  1  |       E5     |      VERT
 * -------------------------------------------------------
 *      E5       |  0  |      INIT    |      ROUGE
 * -------------------------------------------------------
 *      E5       |  1  |      E5      |       X
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
    bool etat_bool = false;
    bool etat_change = false;

    enum ETAT_ENUM {
      INIT,
      E1,
      E2,
      E3,
      E4,
      E5
    };
    enum ETAT_ENUM etat = INIT;
    
    enum COLOR_ENUM {
        ROUGE,
        VERT,
        AMBRE,
        VIDE
    };
    enum COLOR_ENUM color = ROUGE;
    
    bool orange = false;
    

  for(;;)  // boucle sans fin
  {  


	if(PIND & 0x04 ){

		if(!etat_bool) {
			etat_bool = true;
            		etat_change = true;
		} 
	} 
	else {
		if(etat_bool) {
            		etat_bool = false;
            		etat_change = true;
        	}
	}
	
	if (etat_change) {

     
                
                    switch(etat) {
                        case INIT :
                            etat = E1;
                            color = AMBRE;
                            break;
                        case E1 :
                            etat = E2;
                            color = VERT;
                            break;
                        case E2 :
                            etat = E3;
                            color = ROUGE;
                            break;
                        case E3 :
                            etat = E4;
                            color = VIDE;
                            break;
                        case E4 :
                            etat = E5;
                            color = VERT;
                            break;
                        case E5 :
                            etat = INIT;
                            color = ROUGE;
                            break;

                    }

                
        
            etat_change = false;
    }
	
    

        switch(color) {
            case ROUGE :
                PORTB = 0x02;
                break;
            case VERT : 
                PORTB = 0x01;
                break;
            case AMBRE :
                if(orange) {
                    PORTB = 0x01;
                    _delay_ms (3); 
                } else {
                    PORTB = 0x02;
                    _delay_ms (1); 
                } 
                orange = !orange;
                break;
            case VIDE : 
                PORTB = 0x00;
                break;
        }
    
        if(color != AMBRE) {
            _delay_ms (10); 
        }
    


  }
  return 0; 
}

