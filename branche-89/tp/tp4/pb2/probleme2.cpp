/*
 * Nom: 
 * Description: 
 */

#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
void delai(uint8_t duree)
{
	uint8_t milli = 0;
	while(milli < duree)
	{
		_delay_ms(1);
		milli++;
	}
}
int main()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode lecture

	enum etat {INIT, E1, E2, E3, E4} e = INIT;
	uint8_t a = 0, b = 0;
	for (;;) // Boucle infinie
	{
		switch (e)
		{
			case INIT : // Etat initial, verifie si le bouton-poussoir est bien pousse, si oui on passe a l'etat E1.
				if(PIND & 0x04) // Verification pour antirebonds
				{
					_delay_ms(1);
					if(PIND & 0x04)
					{
						e = E1;
					}
				}
			break;
			case E1 : // Second etat, si le bouton-poussoir a ete relache, on passe a l'etat E2.
				if((PIND & 0x04) == 0)
				{
					e = E2;
				}
			break;
			case E2 : // Troisieme etat, 60Hz pendant 10s
				for(uint8_t i = 0; i < 5; i++)
				{
					for(uint8_t j = 0; j < 10; j++)
					{
						PORTB = 0x00;
						delai(60 - a);
						PORTB = 0x02;
						delai(a);
					}
					a+=15;
				}
				e = E3;
			break;
			case E3 : // Quatrieme etat, 400Hz pendant 10s
				for(uint8_t i = 0; i < 4; i++)
				{
					for(uint8_t j = 0; j < 10; j++)
					{
						PORTB = 0x00;
						delai(400 - b);
						PORTB = 0x02;
						delai(b);
					}
					b+=100;
				}
				e = E4;
			break;
		}
	}
}
