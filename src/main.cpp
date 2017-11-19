#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Srf02.hpp"
#include <unistd.h>

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

	if (cflag) {
		char *old_addr = argv[optind];
		char *new_addr = argv[optind+1];
		cout << "Changing sensor ID from " << hex << old_addr << " to "<< hex << new_addr << endl;
	}

	return EXIT_SUCCESS;

}
