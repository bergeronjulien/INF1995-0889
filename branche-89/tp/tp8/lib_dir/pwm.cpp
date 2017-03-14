#include "../include/pwm.h"
void pwmA(uint8_t duty)
{
	OCR2A = duty;
}
void pwmB(uint8_t duty)
{
	OCR2B = duty;
}
void initPwm(void)
{
	TCCR2A = 0xa1; // TOP 0xff, phase correct, OC2A et OC2B pins clr upcount
	TCCR2B = 0x02; // no noise canceler, TOP 0xff, phase correct, clk/8
}
