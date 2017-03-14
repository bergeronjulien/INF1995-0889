///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Classe Timer16                                                            //
//                                                                           //
// Description: Cette classe permet de manipuler le compteur 1 de 16 bits du //
//              ATMega324PA.                                                 //
//                                                                           //
// Librairie:   inf1995                                                      //
// Auteur:      Guillaume Renaud, B.A.A.                                     //
// Equipe:      08-89                                                        //
// Cours:       INF1995                                                      //
// Date:        14 mars 2017                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
#ifndef TIMER16_H
#define TIMER16_H
#include <avr/io.h>
class Timer16
{
	private:
	public:
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
#endif // TIMER_H
