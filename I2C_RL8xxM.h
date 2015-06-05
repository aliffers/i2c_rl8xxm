#ifndef I2C_RL8xxM_H
#define I2C_RL8xxM_H

#include <Arduino.h>

class I2C_RL8xxM {

	public:
		I2C_RL8xxM (int addr);
		bool IsOn (int relay);
		void Switch (int relay, bool on = true);
		void Toggle (int relay = 0);
		void All (bool on = true);
		void On (int relay);
		void Off (int relay);
		void AllOn ();
		void AllOff ();
		void AllToggle ();
		void OnMask (byte);
		void OffMask (byte);
		byte ReadValue ();
		void WriteValue (byte value);
		
	private:
		int _addr;

};

#endif
