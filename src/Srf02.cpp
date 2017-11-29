#include "Srf02.hpp"


using namespace std;

#define VALUE_LSB 3
#define VALUE_MSB 2
#define COMMAND_REG 0x00
#define REFRESH_ORDER 0x51

#define MAX_BUF 64

Srf02::Srf02(int bus, unsigned char address){
	I2CBus = bus;
	I2CAddress = address;
	readValue();
}

int Srf02::writeValue(unsigned char value) {

#ifdef DEBUG
	cout << "DEBUG : writeValue : " << hex << value << endl;
#endif
	return i2c_write_value(I2CBus, I2CAddress, COMMAND_REG, value);
}


unsigned char Srf02::get_i2c_register(unsigned char reg) {

	return i2c_get_register(I2CBus, I2CAddress, reg);
}

int Srf02::refreshValue(){

#ifdef DEBUG
	cout << "DEBUG : refreshValue" << endl;
#endif

	this->writeValue(REFRESH_ORDER);
	return 0;
}

int Srf02::readValue(){
	#ifdef DEBUG
	cout << "DEBUG : readValue" << endl;
#endif
usleep(200000);
	unsigned int LSB = this->get_i2c_register(VALUE_LSB);
	//usleep(200000);
	//unsigned int MSB = this->get_i2c_register(VALUE_MSB);
#ifdef DEBUG
	cout << "LSB = " << hex << LSB << endl;
#endif

	this->value = convertValue(MSB, LSB);
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
