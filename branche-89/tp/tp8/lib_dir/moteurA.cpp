///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Classe MoteurA                                                            //
//                                                                           //
// Description: Cette classe permet de manipuler un moteur avec le registre  //
//              OCA du timer 2 du ATMega324PA en utilisant un pwm.           //
//                                                                           //
// Librairie:   inf1995                                                      //
// Auteur:      Guillaume Renaud, B.A.A.                                     //
// Equipe:      08-89                                                        //
// Cours:       INF1995                                                      //
// Date:        14 mars 2017                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include "../include/moteurA.h"
MoteurA::MoteurA(void)
{
	TCCR2A = 0xa1; // TOP 0xff, phase correct, OC2A et OC2B pins clr upcount
	TCCR2B = 0x02; // no noise canceler, TOP 0xff, phase correct, clk/8;
	DDRD = 0b11111111; // PORT D en mode sortie
	PORTD = 0b00000000; // initialisation PORT D
}
MoteurA::~MoteurA(void)
{
	PORTC = 0b00000001;
}
void MoteurA::fwd(uint8_t speed)
{
	if(PORTD & 0b00100000) // si la direction est rev...
		PORTD ^= 0b00100000; // ...la changer pour fwd (met un 0 a la broche 6)
	OCR2A = speed;
}
void MoteurA::rev(uint8_t speed)
{
	PORTD = 0b00100000; // change la direction pour marche arriere
	OCR2A = speed;
}
void MoteurA::stop(void)
{
	OCR2A = 0x00; // pwm au OC2A au ground, moteur arrete
}
