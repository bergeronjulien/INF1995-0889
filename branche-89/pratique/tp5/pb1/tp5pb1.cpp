/*
 * Travail pratique 5
 * Section 01
 * Equipe 89
 * Date: 4 mars 2017
 * Nom du programme: tp5pb1
 * Auteurs: Guillaume Renaud
 */
#define F_CPU			8000000UL
#define DEL_ETEINTE		0x00
#define DEL_ROUGE		0x01
#define DEL_VERTE		0x02
#include <avr/io.h>
#include <util/delay_basic.h>
#include <avr/interrupt.h>
enum etatBtn {enfonce, relache};
volatile etatBtn bouton = relache;
ISR(INT0_vect)
{
	_delay_loop_2(2000); // delai de 1ms
	if(PIND & 0x04)
		bouton = enfonce;
	else
		bouton = relache;
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
	EICRA = EICRA | _BV(ISC00); // permet INT0 sur n'importe quel front
	sei(); // reactive globalement les interruptions (SREG I-bit = 1)
}
/* programme principal */
int main(void)
{
	init();
	for(;;)  // boucle sans fin
	{
		while(bouton == relache)
			PORTC = DEL_ROUGE;
		while(bouton == enfonce)
		{
			PORTC = DEL_ROUGE;
			_delay_loop_2(100);
			PORTC = DEL_VERTE;
			_delay_loop_2(300);
		}
		while(bouton == relache)
			PORTC = DEL_VERTE;
		while(bouton == enfonce)
			PORTC = DEL_ROUGE;
		while(bouton == relache)
			PORTC = DEL_ETEINTE;
		while(bouton == enfonce)
			PORTC = DEL_VERTE;
	}
	return 0;
}
