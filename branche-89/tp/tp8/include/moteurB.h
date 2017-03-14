///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Classe MoteurB                                                            //
//                                                                           //
// Description: Cette classe permet de manipuler un moteur avec le registre  //
//              OCB du timer 2 du ATMega324PA en utilisant un pwm.           //
//                                                                           //
// Librairie:   inf1995                                                      //
// Auteur:      Guillaume Renaud, B.A.A.                                     //
// Equipe:      08-89                                                        //
// Cours:       INF1995                                                      //
// Date:        14 mars 2017                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
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
