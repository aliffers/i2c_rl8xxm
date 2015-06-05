#include <Arduino.h>
#include <Wire.h>
#include "I2C_RL8xxM.h"

I2C_RL8xxM::I2C_RL8xxM (int addr) { _addr = addr; }

bool I2C_RL8xxM::IsOn (int relay) {
	return ~ReadValue () & (1 << relay - 1);
}

void I2C_RL8xxM::Switch (int relay, bool on) {
	WriteValue ((on) ? ReadValue() & ~(1 << relay - 1) : ReadValue() | (1 << relay - 1));
	delay ((on) ? 10 : 5);
}

void I2C_RL8xxM::Toggle (int relay) {
	WriteValue ((relay > 0) ? ReadValue () ^ (1 << relay - 1) : ReadValue () ^ 0xFF);
	delay (10);
}

void I2C_RL8xxM::All (bool on) {
	WriteValue ((on) ? 0x00 : 0xFF);
	delay ((on) ? 10 : 5);
}

void I2C_RL8xxM::OnMask (byte mask) {
	WriteValue (ReadValue () & ~mask);
	delay (10);
}

void I2C_RL8xxM::OffMask (byte mask) {
	WriteValue (ReadValue () | mask);
	delay (5);
}

void I2C_RL8xxM::On (int relay) { Switch (relay, true); }
void I2C_RL8xxM::Off (int relay) { Switch (relay, false); }
void I2C_RL8xxM::AllOn () { All (true); }
void I2C_RL8xxM::AllOff () { All (false); }
void I2C_RL8xxM::AllToggle () { Toggle (0); }

byte I2C_RL8xxM::ReadValue () {
	Wire.requestFrom (_addr, 1);
	return (Wire.available () ? Wire.read () : 0xFF);
}

void I2C_RL8xxM::WriteValue (byte value) {
	Wire.beginTransmission (_addr);
	Wire.write (value);
	Wire.endTransmission ();
}
