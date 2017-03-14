#ifndef MOTEURA_H
#define MOTEURA_H
#include <avr/io.h>
class MoteurA
{
	private:
		TCCR2A;
		TCCR2B;
	public:
		MoteurA(void);
		~MoteurA(void);
		void fwd(uint8_t);
		void rev(uint8_t);
		void stop(void);
};
#endif //MOTEURA_H