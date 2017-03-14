#include <avr/io.h>
#include "../include/moteurA.h"
MoteurA::MoteurA(void)
{
	TCCR2A = 0xa1; // TOP 0xff, phase correct, OC2A et OC2B pins clr upcount
	TCCR2B = 0x02; // no noise canceler, TOP 0xff, phase correct, clk/8;
	DDRD = 0xff; // PORT D en mode sortie
}
MoteurA::~MoteurA(void)
{
	
}
void Moteur::fwd(uint8_t speed)
{
	PD5 = 0b0;
	OCR2A = speed;
}
