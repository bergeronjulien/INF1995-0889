/*
 * Nom: 
 * Description: 
 */

#define F_CPU 8000000
#include <avr/io.h> 
#include <util/delay.h>
void delai(unsigned int duree)
{
	unsigned int micro = 0;
	while(micro < duree)
	{
		_delay_us(1);
		micro++;
	}
}
int main()
{
	DDRA = 0xff; // PORT A est en mode sortie
	DDRB = 0xff; // PORT B est en mode sortie
	DDRC = 0xff; // PORT C est en mode sortie
	DDRD = 0x00; // PORT D est en mode lecture

	enum etat {INIT, E1, E2, E3, E4, E5} e = INIT;
	unsigned int a = 1000;
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
						PORTB = 0x02;
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
			case E2 : // Troisieme etat,
				unsigned int a = 1000;
				for(int i = 0; i < 500; i++)
				{
					for(int j = 0; j < 3; j++)
					{
						PORTB = 0x00;
						delai(1000 - a);
						PORTB = 0x02;
						delai(a);
					}
					a-=2;
				}
				PORTB = 0x00;
				e = E3;
			break;
			/*case E3 : // Quatrieme etat, 
				
			break;*/
		}
	}
}
