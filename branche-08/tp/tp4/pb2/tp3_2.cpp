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


#include <avr/io.h> 
#define F_CPU 8000000
#include <util/delay.h>

 void delay_ms(int milliseconds)
 {
   while(milliseconds > 0)
   {
      _delay_ms(1);
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
	bool ouvert = true;
	
	for(int i =0; i < 250; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_ms(0);
		} else {
			PORTB = 0x00;
			_delay_ms(16);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 250; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_ms(4);
		} else {
			PORTB = 0x00;
			_delay_ms(12);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 250; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_ms(8);
		} else {
			PORTB = 0x00;
			_delay_ms(8);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 250; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_ms(12);
		} else {
			PORTB = 0x00;
			_delay_ms(4);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 250; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_ms(16);
		} else {
			PORTB = 0x00;
			_delay_ms(0);
		}
		ouvert = !ouvert;
	}
	
	
	
	
	
	for(int i =0; i < 1600; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_us(0);
		} else {
			PORTB = 0x00;
			_delay_us(2500);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 1600; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_us(625);
		} else {
			PORTB = 0x00;
			_delay_us(1875);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 1600; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_us(1250);
		} else {
			PORTB = 0x00;
			_delay_us(1250);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 1600; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_us(1875);
		} else {
			PORTB = 0x00;
			_delay_us(625);
		}
		ouvert = !ouvert;
	}
	
	for(int i =0; i < 1600; i++) {
	    if(ouvert) {
			PORTB = 0x01;
			_delay_us(2500);
		} else {
			PORTB = 0x00;
			_delay_us(0);
		}
		ouvert = !ouvert;
	}

	
    PORTB = 0x00;


  return 0; 
}
