#define F_CPU		8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/timer16.h"
Timer16::Timer16(void)
{
	TCCR1A = 0b00000000; // mode normal, aucune horloge, aucun force compare
	TCCR1B = 0b00000000; // mode normal, aucune horloge, aucun force compare
	TCCR1C = 0b00000000; // mode normal, aucune horloge, aucun force compare
	/* aucune initialisation du PORT D car OC1A et OC1B sont utilises pour
	   fixer la direction de rotation des moteurs, ne JAMAIS utiliser OC1A
	   et OC1B si des objets MoteurA et/ou MoteurB sont utilises! */
	TCNT1 = 0x0000; // initialisation du compteur
	TIMSK1 |= 0b00100111; // autorise toutes les interruptions du compteur
}
Timer16::~Timer16(void)
{
	/* reset global du compteur lorsque detruit */
	TCCR1A = 0b00000000;
	TCCR1B = 0b00000000;
	TCCR1C = 0b00000000;
	TCNT1 = 0x0000;
}
void Timer16::setmode(uint8_t mode)
{
	switch(mode)
	{
		case 1: // mode normal
			/* pour etre en mode normal, les bits 0 et 1 du TCCR1A et les bits
			   3 et 4 du TCCR1B (WGM13, WGM12, WGM11, WGM10, page 130) doivent
			   etre a zero chacun. Avec un XOR, si le bit est 1, 1 XOR 1 = 0 */
			if(TCCR1A & 0b00000001)
				TCCR1A ^= 0b00000001; // remplace bit 0 pour un 0 si bit 0 = 1
			else if(TCCR1A & 0b00000010)
				TCCR1A ^= 0b00000010; // remplace bit 1 pour un 0 si bit 1 = 1
			else if(TCCR1B & 0b00001000)
				TCCR1B ^= 0b00001000; // remplace bit 3 pour un 0 si bit 3 = 1
			else if(TCCR1B & 0b00010000)
				TCCR1B ^= 0b00010000; // remplace bit 4 pour un 0 si bit 4 = 1
			break;
		case 2: // mode CTC, TOP = OCR1A
			/* pour etre en mode CTC avec TOP = OCR1A, les bits 0 et 1 du 
			   TCCR1A et le 4 du TCCR1B (WGM13, WGM11, WGM10, page 130) doivent
			   etre a zero chacun. Le bit 3 du TCCR1B (WGM12) doit etre a 1 */
			if(TCCR1A & 0b00000001)
				TCCR1A ^= 0b00000001; // remplace bit 0 pour un 0 si bit 0 = 1
			else if(TCCR1A & 0b00000010)
				TCCR1A ^= 0b00000010; // remplace bit 1 pour un 0 si bit 1 = 1
			else if(TCCR1B & 0b00010000)
				TCCR1B ^= 0b00010000; // remplace bit 4 pour un 0 si bit 4 = 1
			TCCR1B |= 0b00001000;
			/* empeche une interruption de modificer OCR1A car valeur 16-bit se
			   modifie sur 2 cycles d'horloge, possibilite de corruption du
			   registre si une interruption y ecrit sur le 2e cycle */
			cli();
			OCR1A = 0xffff; // valeur max pour initialiser par prudence
			sei();
			break;
		case 3: // mode CTC. TOP = ICR1
			/* pour etre en mode CTC avec TOP = ICR1, les bits 0 et 1 du TCCR1A
			   (WGM11, WGM10, page 130) doivent etre a zero chacun. Les bits 3 
			   et 4 du TCCR1B (WGM13, WGM12) doivent etre a 1 chacun */
			if(TCCR1A & 0b00000001)
				TCCR1A ^= 0b00000001; // remplace bit 0 pour un 0 si bit 0 = 1
			else if(TCCR1A & 0b00000010)
				TCCR1A ^= 0b00000010; // remplace bit 1 pour un 0 si bit 1 = 1
			TCCR1B |= 0b00011000;
			/* empeche une interruption de modificer OCR1A car valeur 16-bit se
			   modifie sur 2 cycles d'horloge, possibilite de corruption du
			   registre si une interruption y ecrit sur le 2e cycle */
			cli();
			ICR1 = 0xffff; // valeur max pour initialiser par prudence
			sei();
		default: // si mode saisi est invalide, utiliser le mode normal
			if(TCCR1A & 0b00000001)
				TCCR1A ^= 0b00000001;
			else if(TCCR1A & 0b00000010)
				TCCR1A ^= 0b00000010;
			else if(TCCR1B & 0b00001000)
				TCCR1B ^= 0b00001000;
			else if(TCCR1B & 0b00010000)
				TCCR1B ^= 0b00010000;
	}
}
void Timer16::setclk(uint8_t clk)
{
	// consulter la page 131 pour voir les bits du TCCR1B a mettre a 1 et a 0
	switch(clk)
	{
		case 1: // horloge/1
			if(TCCR1B & 0b00000010)
				TCCR1B ^= 0b00000010);
			else if(TCCR1B & 0b00000100)
				TCCR1B ^= 0b00000100);
			TCCR1B |= 0b00000001;
			break;
		case 2: // horloge/8
			if(TCCR1B & 0b00000001)
				TCCR1B ^= 0b00000001);
			else if(TCCR1B & 0b00000100)
				TCCR1B ^= 0b00000100);
			TCCR1B |= 0b00000010;
			break;
		case 3: // horloge/64
			if(TCCR1B & 0b00000100)
				TCCR1B ^= 0b00000100);
			TCCR1B |= 0b00000011;
			break;
		case 4: // horloge/256
			if(TCCR1B & 0b00000001)
				TCCR1B ^= 0b00000001);
			else if(TCCR1B & 0b00000010)
				TCCR1B ^= 0b00000010);
			TCCR1B |= 0b00000100;
			break;
		case 5: // horloge/1014
			if(TCCR1B & 0b00000010)
				TCCR1B ^= 0b00000010);
			TCCR1B |= 0b00000101;
			break;
		case 6: // horloge externe (front descendant) broche 2 du PORT B
			if(TCCR1B & 0b00000001)
				TCCR1B ^= 0b00000001);
			TCCR1B |= 0b00000110;
			break;
		case 7: // horloge externe (front montant) broche 2 du PORT B
			TCCR1B |= 0b00000111;
			break;
		default: // si horloge saisie invalide, utiliser l'horloge du MCU
			if(TCCR1B & 0b00000010)
				TCCR1B ^= 0b00000010);
			else if(TCCR1B & 0b00000100)
				TCCR1B ^= 0b00000100);
			TCCR1B |= 0b00000001;
	}
}
void Timer16::stop(void)
{
	// 0 aux bits 2, 1, 0 (CS12, CS11, CS10) du TCCR1B arrete le timer
	if(TCCR1B & 0b00000001)
		TCCR1B ^= 0b00000001);
	else if(TCCR1B & 0b00000010)
		TCCR1B ^= 0b00000010);
	else if(TCCR1B & 0b00000100)
		TCCR1B ^= 0b00000100);
}
void Timer16::reset(void)
{
	TCNT1 = 0x0000;
}
void Timer16::setOCR1A(uint16_t val)
{
	cli();
	OCR1A = val;
	sei();
}
void Timer16::setOCR1B(uint16_t val)
{
	cli();
	OCR1B = val;
	sei();
}
void Timer16::setICR1(uint16_t val)
{
	cli();
	ICR1 = val;
	sei();
}
void Timer16::allowAllInt(void)
{
	TIMSK1 |= 0b00100111;
}
void Timer16::stopAllInt(void)
{
	TIMSK1 = 0x00;
}