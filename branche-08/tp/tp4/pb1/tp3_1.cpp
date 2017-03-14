/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 * 
 * Fichier: tp3_1.cpp
 * Par: Julien Bergeron (1829496) et Loic Bellemare-Alford (1846135)
 * Fait le: 2 février 2017
 * Derni're modification: 27 janvier 2017
 */



#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

 void delay_us(unsigned int milliseconds)
 {
   while(milliseconds > 0)
   {
      _delay_us(1);
      milliseconds--;
    }
 }

int main()
{
  	DDRA = 0xff; // PORT A est en mode sortie
  	DDRB = 0xff; // PORT B est en mode sortie
  	DDRC = 0xff; // PORT C est en mode sortie
  	DDRD = 0x00; // PORT D est en mode entree

  	PORTB = 0x00;
	int i =0;
	int a = 1000;
	bool ouvert = true;


	while(i < 3000000){
		if(a % 3000) {
			a--;
		}

		if(ouvert) {
			PORTB = 0x01;
			delay_us(a);
		}else{ 
			PORTB = 0x00;
			delay_us(1000 - a);
		}
		ouvert = !ouvert;
		
		i++;
	}


  return 0; 
}

