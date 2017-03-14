///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Classe Del                                                                //
//                                                                           //
// Description: Cette classe permet de manipuler la del libre sur la carte   //
//              mere via des methodes simples.                               //
//                                                                           //
// Librairie:   inf1995                                                      //
// Auteur:      Guillaume Renaud, B.A.A.                                     //
// Equipe:      08-89                                                        //
// Cours:       INF1995                                                      //
// Date:        14 mars 2017                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include "../include/del.h"
Del::Del(void)
{
	if(PORTC & 0b00000001)
		PORTC ^= 0b00000001;
	else if(PORTC & 0b00000010)
		PORTC ^= 0b00000010;
}
Del::~Del(void)
{
	if(PORTC & 0b00000001)
		PORTC ^= 0b00000001;
	else if(PORTC & 0b00000010)
		PORTC ^= 0b00000010;
}
void Del::rouge(void)
{
	if(PORTC & 0b00000010)
		PORTC ^= 0b00000010;
	PORTC |= 0b00000001;
}
void Del::vert(void)
{
	if(PORTC & 0b00000001)
		PORTC ^= 0b00000001;
	PORTC |= 0b00000010;
}
void Del::off(void)
{
	if(PORTC & 0b00000001)
		PORTC ^= 0b00000001;
	else if(PORTC & 0b00000010)
		PORTC ^= 0b00000010;
}
