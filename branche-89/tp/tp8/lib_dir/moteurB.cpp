///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Classe MoteurB                                                            //
//                                                                           //
// Description: Cette classe permet de manipuler un moteur avec le registre  //
//              OCB du timer 2 du ATMega324PA en utilisant un pwm.           //
//                                                                           //
// Librairie:   inf1995                                                      //
// Auteur:      Guillaume Renaud, B.A.A.                                     //
// Equipe:      08-89                                                        //
// Cours:       INF1995                                                      //
// Date:        14 mars 2017                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include "../include/moteurB.h"
MoteurB::MoteurB(void)
{
	TCCR2A = 0xa1; // TOP 0xff, phase correct, OC2A et OC2B pins clr upcount
	TCCR2B = 0x02; // no noise canceler, TOP 0xff, phase correct, clk/8;
	DDRD = 0b11111111; // PORT D en mode sortie
}
MoteurB::~MoteurB(void)
{
	/* le destructeur deconnecte OC2A et OC2B des broches 8 et 7 et coupe
	   l'horloge du compteur 2. Attention! Le destructeur eteint le moteur
	   A sans toutefois le detruire */
	TCCR2A = 0b00000000;
	TCCR2B = 0b00000000;
}
void MoteurB::fwd(uint8_t speed)
{
	if(PORTD & 0b00010000) // si la direction est rev...
		PORTD ^= 0b00010000; // ...la changer pour fwd (met un 0 a la broche 6)
	OCR2B = speed;
}
void MoteurB::rev(uint8_t speed)
{
	PORTD = 0b00010000; // change la direction pour marche arriere
	OCR2B = speed;
}
void MoteurB::stop(void)
{
	OCR2B = 0x00; // pwm au OC2A au ground, moteur arrete
}
