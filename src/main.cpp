#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Srf02.hpp"
#include <argp.h>

using namespace std;

static char doc[] = "Usage : srf02-utility [-c current_addr new addr]";

static struct argp argp = { 0, 0, 0, doc };

int main (int argc, char **argv){


	argp_parse (&argp, argc, argv, 0, 0, 0);
	
	cout << "---- srf02 sensors utility ----" << endl;
	return EXIT_SUCCESS;

}
