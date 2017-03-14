/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */

#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie
  unsigned long compteur=0; // le compteur est initialise a 0.
                            // c'est un compteur de 32 bits

  for(;;)  // boucle sans fin
  {
   //compteur++;  // incremente le compteur

   PORTB = 0x01;
   _delay_ms(1000);
   PORTB = 0x02;
   _delay_ms(1000);
  for(unsigned long i = 0; i < 650000 ; i++) {
      PORTB = i;
   }
  }
  return 0; 
}

