#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "Srf02.hpp"


using namespace std;



int main (int argc, char **argv){

	char optstring[] = "c"; //allowed options
	int c;
	int cflag = 0; //if -c option detected

	cout << "---- srf02 sensors utility ----" << endl;

	while((c=getopt(argc, argv, optstring))!=-1){
		switch (c)
		{
			case 'c':
				cflag = 1;
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
	int bus;

	if (cflag) {
		if (argv[optind] && argv[optind+1]){
			bus = atoi(argv[optind]);
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

		Srf02 *sensor = new Srf02(bus, *old_addr);
		int check = sensor->changeAddress(new_addr);
		if (check) {
			cout << "Done." << endl;
		}
		else {
			cout << "FAILED : Error while changing the address." << endl;
		}

	}

	return EXIT_SUCCESS;

}
