#ifndef MOTEURB_H
#define MOTEURB_H
#include <avr/io.h>
class MoteurB
{
	private:
		
	public:
		MoteurB(void);
		~MoteurB(void);
		void fwd(uint8_t);
		void rev(uint8_t);
		void stop(void);
};
#endif //MOTEURB_H
