/*
 * Travail pratique 5
 * Section 01
 * Equipe 89
 * Date: 12 mars 2017
 * Nom du programme: tp5pb3
 * Auteurs: Guillaume Renaud
 */
#define F_CPU			8000000UL
#include <avr/io.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
void init(void)
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0xff; // PORT D est en mode sortie
	TCCR1A = 0xa1; // TOP 0xff, phase correct, OCA1 et OCB1 pins clr upcount
	TCCR1B = 0x02; // no noise canceler, TOP 0xff, phase correct, clk/8
	TCCR1C = 0x00;
	PORTD = 0x00; // pour grounder les broches 3 et 4 (PD2 et PD3)
}
void pwm(uint8_t duty)
{
	OCR1A = duty;
	OCR1B = duty;
	TCNT1 = 0x0000;
}
/* programme principal */
int main(void)
{
	init();
	uint8_t i = 0;
	pwm(0x00);
	for(; i < 0x64; i++) // 100 interations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwm(0x40);
	for(; i > 0x00; i--) // 100 interations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwm(0x80);
	for(; i < 0x64; i++) // 100 interations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwm(0xc0);
	for(; i > 0x00; i--) // 100 interations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	pwm(0xff);
	for(; i < 0x64; i++) // 100 interations X 20ms = 2s
		_delay_loop_2(40000); // 20ms
	return 0;
}
