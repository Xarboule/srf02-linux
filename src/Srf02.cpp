#include "Srf02.hpp"

#define DEBUG 1

#if DEBUG
#include <iostream>
#endif

using namespace std;

#define VALUE_LSB 0x03
#define VALUE_MSB 0x02
#define COMMAND_REG 0x00
#define REFRESH_ORDER 0x51

#define MAX_BUF 64

Srf02::Srf02(int bus, unsigned char address){
	I2CBus = bus;
	I2CAddress = address;
	readValue();
}

int Srf02::writeValue(unsigned char value) {

	return i2c_write_value(I2CBus, I2CAddress, COMMAND_REG, value);
}


unsigned char Srf02::get_i2c_register(unsigned char reg) {

	return i2c_get_register(I2CBus, I2CAddress, reg);
}

int Srf02::refreshValue(){
	this->writeValue(REFRESH_ORDER);
	return 0;
}

int Srf02::readValue(){
	unsigned int LSB = this->get_i2c_register(VALUE_LSB);
	unsigned int MSB = this->get_i2c_register(VALUE_MSB);
#if DEBUG
	cout << "DEBUG : MSB = " << hex << MSB << "  LSB = " << hex << LSB << endl;
#endif

	this->value = convertValue(VALUE_MSB, VALUE_LSB);
	return 0;
}


int Srf02::convertValue(unsigned int MSB, unsigned int LSB){
	short temp = MSB;
	temp = (temp<<8) | LSB;
	return temp;
}

int Srf02::getValue(){
	this->readValue();
	return this->value;
}

int Srf02::changeAddress(unsigned char *newAddress){
	cout << "Please disconnect all not concerned sensors from the I2C bus." << endl;
	cout << "Press any key to continue..." << endl;
	cin.get();
	cout << endl << "Changing adress from " << hex << I2CAddress << " to " << hex << newAddress << endl;

	i2c_write_value(I2CBus, I2CAddress, COMMAND_REG, 0xA0);
	i2c_write_value(I2CBus, I2CAddress, COMMAND_REG, 0xAA);
	i2c_write_value(I2CBus, I2CAddress, COMMAND_REG, 0xA5);
	i2c_write_value(I2CBus, I2CAddress, COMMAND_REG, *newAddress);

	return 0;
}
