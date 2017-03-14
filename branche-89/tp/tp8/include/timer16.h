#ifndef TIMER16_H
#define TIMER16_H
#include <avr/io.h>
class Timer16
{
	public:
	private:
		Timer16(void);
		~Timer16(void);
		void setmode(uint8_t);
		void setclk(uint8_t);
		void stop(void);
		void reset(void);
		void setOCR1A(uint16_t);
		void setOCR1B(uint16_t);
		void setICR1(uint16_t);
		void allowAllInt(void);
		void stopAllInt(void);
};
#endif TIMER_H