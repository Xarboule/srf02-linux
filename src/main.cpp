#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "Srf02.hpp"

#define DEBUG

using namespace std;



int main (int argc, char **argv){

	#ifdef DEBUG
		cout << " == DEBUG MODE == " << endl;
	#endif

	char optstring[] = "cvr"; //allowed options
	int c;
	int cflag = 0; // if -c option detected
	int vflag = 0; // -v option
	int rflag = 0;

	while((c=getopt(argc, argv, optstring))!=-1){
		switch (c)
		{
			case 'c':
				cflag = 1;
				break;
			case 'v':
				vflag = 1;
				break;
			case 'r':
				rflag = 1;
				break;
			case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
		}
	}
	//printf("%s\n", argv[optind]);

	unsigned char *old_addr, *new_addr;
	char *bus;

	if (cflag && vflag){
		cout << "Too many arguments." << endl;
	}
	else if (cflag) {
		if (argv[optind] && argv[optind+1]){
			bus = argv[optind];
			old_addr = reinterpret_cast<unsigned char *>(argv[optind+1]);
			//*old_addr = (unsigned char) argv[optind+1];
			new_addr = reinterpret_cast<unsigned char *>(argv[optind+2]);
			//*new_addr = (unsigned char) argv[optind+2];
		}
		else {
			cout << "Missing argument. Expected syntax : srf02-utility -c bus old_addr new_addr" << endl;
			return -1;
		}
		cout << "Changing sensor ID from " << hex << old_addr << " to "<< hex << new_addr << " on bus " << bus << endl;
		int busI2C = open(bus, O_RDWR);
		Srf02 *sensor = new Srf02(busI2C, *old_addr);
		int check = sensor->changeAddress(new_addr);
		if (check) {
			cout << "Done." << endl;
		}
		else {
			cout << "FAILED : Error while changing the address." << endl;
		}
}

		else if(rflag){

			if (argv[optind] && argv[optind+1]){
				bus = argv[optind];
				old_addr = reinterpret_cast<unsigned char *>(argv[optind+1]);
				//*old_addr = (unsigned char) argv[optind+1];
				new_addr = reinterpret_cast<unsigned char *>(argv[optind+2]);
				//*new_addr = (unsigned char) argv[optind+2];
			}
			else {
				cout << "Missing argument. Expected syntax : srf02-utility -c bus old_addr new_addr" << endl;
				return -1;
			}

			int busI2C = open(bus, O_RDWR);
			Srf02 *sensor = new Srf02(busI2C, *old_addr);

			cout << "refresh sensor value..." << endl;
			sensor->refreshValue();


		}
		else if (vflag){
			bus = argv[optind];
			int busI2C = open(bus, O_RDWR);
			unsigned char *sensor_addr = reinterpret_cast<unsigned char *>(argv[optind+1]);

			Srf02 *sensor = new Srf02(busI2C, *sensor_addr);

			sensor->refreshValue();
			usleep(2000000); // Waiting for the sensor

			if(!(sensor->readValue())){
				cout << "Error while reading the value" << endl;
			}
			else {
				int distance = sensor->getValue();
				cout << "Distance : " << distance << " cm" << endl;
			}
		}


	return EXIT_SUCCESS;

}
