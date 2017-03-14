/*
 * Travail pratique 5
 * Section 01
 * Equipe 89
 * Date: 12 mars 2017
 * Nom du programme: tp5pb2
 * Auteurs: Guillaume Renaud
 */
#define F_CPU			8000000UL
#define DEL_ETEINTE		0x00
#define DEL_ROUGE		0x01
#define DEL_VERTE		0x02
#include <avr/io.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
volatile uint8_t minuterieExpiree = 0x00;
volatile uint8_t boutonPoussoir = 0x00;
ISR(INT0_vect)
{
	_delay_loop_2(2000); // delai de 1ms
	boutonPoussoir = 0x01;
}
ISR(TIMER1_COMPA_vect)
{
	minuterieExpiree = 0x01;
}
void init(void)
{
	cli(); // deactive globalement les interruptions (SREG I-bit = 0)
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode entree
	/* contenu de EIMSK => XXXX XXXX (don't care)
	 * _BV(INT) => left bit-shift de 1 (INT0 est la premiere position de EIMSK)
	 * XXXX XXXX OU 0000 0001 = XXXX XXX1
	 */
	EIMSK = EIMSK | _BV(INT0); // active l'interruption INT0 (PD2) seulement
	/* INT0 sur front montant */
	EICRA = EICRA | _BV(ISC00);
	//EICRA = EICRA | _BV(ISC01);
}
void partirMinuterie(uint16_t duree)
{
	// mode CTC du timer 1 avec horloge divisee par 1024
	// interruption apres la duree specifiee
	TCNT1 = 0x0000;
	OCR1A = duree;
	TCCR1A = 0x00;
	TCCR1B = 0x0d;
	TCCR1C = 0x00;
	TIMSK1 = TIMSK1 | _BV(OCIE1A);
}
/* programme principal */
int main(void)
{
	init();
	for(uint16_t i = 0x0000; i < 0x01f4; i++) // 500 X 20ms = 10 000ms = 10s
		_delay_loop_2(40000); // 20ms
	for(uint8_t i = 0x00; i < 0x05; i++) // 100ms
	{
		PORTC = DEL_ROUGE;
		_delay_loop_2(20000); // 10ms
		PORTC = DEL_ETEINTE;
		_delay_loop_2(20000); // 10ms
	}
	partirMinuterie(0x1e85); // valeur 16-bit pour 1s sur TCNT1
	sei(); // pour empecher toute interruption du bouton avant minuterie
	while(!(minuterieExpiree) && !(boutonPoussoir))
	{
		// attendre qu'une interruption survienne
	}
	cli(); // desactive globalement les interruptions
	if(boutonPoussoir)
		PORTC = DEL_VERTE;
	if(minuterieExpiree) // DEL rouge si delai de 1s depasse
		PORTC = DEL_ROUGE;
	return 0;
}
