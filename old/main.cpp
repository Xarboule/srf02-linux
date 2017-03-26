#include <iostream>
#include <unistd.h>
#include "Srf02.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <vector>
#include <numeric>

using namespace std;

int main(){

	int Bus_I2C = open("/dev/i2c-2", O_RDWR);

	Srf02 test(Bus_I2C, 0x70);

	vector<int> values(10, 100);

	while(1){

		for(int j=0; j<5; j++){
			int value = (int)test.get_i2c_register(3);
			values.insert(values.begin(), value);
			values.pop_back();
			usleep(1000);
			test.writeValue(0x51);
			usleep(200000);
		}
		float average = accumulate( values.begin(), values.end(), 0.0)/values.size();
		
		cout << "Current Value : " << average << endl;
		float ratio = (average / 250.0) * 20; // 20 caracteres = range maxi
		cout << "DEBUG : " << average << endl;
		for(int i=0; i<ratio; i++){
			cout << "=";
		}
		cout << ">" << endl;
	
	}

	return 0;
}
