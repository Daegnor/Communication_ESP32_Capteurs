#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"
#include <stdio.h>
#include <string.h>
#include <Wire.h>

class CO2Sensor{
	private:
		int adress;
		uint8_t data[4];

	public:
		CO2Sensor(){
			adress = 0x15;
		};
		~CO2Sensor(){
			delete[] data;
		}
		int getData();
};