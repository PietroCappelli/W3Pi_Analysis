#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>


#define _USE_MATH_DEFINES


int assignpid(uint8_t &pid){
	
	int16_t PDGID[8] = {130, 22, -211, 211, 11, -11, 13, -13};
	return PDGID[pid];
}

void convert(uint64_t &puppi, float &pt, float &eta, float &phi, short int &pid){

	uint16_t pt_int = puppi & 0x3FFF;
	int16_t eta_int = ( (puppi >> 25) & 1) ? ( (puppi >> 14) | (- 0x800) ) : ( (puppi >> 14) & (0xFFF) );
	int16_t phi_int = ( (puppi >> 36) & 1) ? ( (puppi >> 26) | (- 0x400) ) : ( (puppi >> 26) & (0x7FF) );
	uint8_t id_int  = (puppi  >> 37) & 0x7;
	//uint32_t fill = (first_puppi >> 40) & 0x1FFFFFF;
	
	pt  = pt_int * 0.25 ;
	eta = eta_int * M_PI/720.0 ;
	phi = phi_int * M_PI/720.0 ;
	pid = assignpid(id_int);

	if(abs(eta)>2.4) {
		std::cout << "error" << std::endl;
		std::cout << puppi << std::endl;
		std::cout << eta_int << std::endl;
		std::cout << eta << std::endl;
	}
}