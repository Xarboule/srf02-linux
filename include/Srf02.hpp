#ifndef SRF02_H_
#define SRF02_H_
#define SRF02_I2C_BUFFER 6

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <iostream>
#include "i2c-sensor.hpp"

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif



class Srf02 {
	private:
		int I2CBus, I2CAddress;
		char dataBuffer[SRF02_I2C_BUFFER];

		int value;

		int convertValue(unsigned int MSB, unsigned int LSB);

	public:
		Srf02(int bus, unsigned char address);

		unsigned char get_i2c_register(unsigned char reg);
		int writeValue(unsigned char value);
		int refreshValue();
		int readValue();
		int getValue();
		int changeAddress(unsigned char *newAddress);
	};

#endif
