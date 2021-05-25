#include "CO2Sensor.h"

int CO2Sensor::getData(){
	int CO2ppmValue;
	Wire.beginTransmission(adress);
	Wire.write(0x04);
	Wire.write(0x13);
	Wire.write(0x8B);
	Wire.write(0x00);
	Wire.write(0x01);
	// end transmission
	Wire.endTransmission();
	// read report of current gas measurement in ppm
	delay(2000);
	Wire.requestFrom(adress, 4); // request 4 bytes from slave device
	data[0] = Wire.read();
	data[1] = Wire.read();
	data[2] = Wire.read();
	data[3] = Wire.read();
	CO2ppmValue = ((data[2] * 0xFF) + data[3]);

	return CO2ppmValue;
}