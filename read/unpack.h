#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>

#include <TTree.h>
#include <TFile.h>
#include <Compression.h>
#include <TROOT.h>
#include <TStopwatch.h>


#define _USE_MATH_DEFINES


int assignpid(uint8_t &pid){
	
	int16_t PDGID[8] = {130, 22, -211, 211, 11, -11, 13, -13};
	return PDGID[pid];
}

void convert(uint64_t &puppi, float &pt, float &eta, float &phi, short int &pid){

	uint16_t pt_int = puppi & 0x3FFF;
	int16_t eta_int = ( (puppi >> 25) & 1) ? ( (puppi >> 14) | (- 0x800) ) : ( (puppi >> 14) & (0xFFF) );
	int16_t phi_int = ( (puppi >> 36) & 1) ? ( (puppi >> 26) | (- 0x400) ) : ( (puppi >> 26) & (0x7FF) );
	uint8_t id_int  = ( puppi  >> 37 ) & 0x7;
	//uint32_t fill = (first_puppi >> 40) & 0x1FFFFFF;
	
	pt  = pt_int * 0.25;
	eta = eta_int * M_PI/720.0;
	phi = phi_int * M_PI/720.0;
	pid = assignpid(id_int);

	if(abs(eta)>2.4) {
		std::cout << "error" << std::endl;
		std::cout << puppi << std::endl;
		std::cout << eta_int << std::endl;
		std::cout << eta << std::endl;
	}
}

void readheader(std::fstream &fin, uint64_t &header, uint16_t &Npuppi, uint16_t &bx, uint16_t &orbit, uint16_t &run){

    fin.read(reinterpret_cast<char*>(&header), sizeof(header));
    Npuppi = header & 0xFFF;
    // if(header==0) std::cout << "null header?\n";
    bx     = (header << 12) & 0xFFF;
    orbit  = (header << 24) & 0x3FFFFFFF;
    run    = (header << 53);
}

Float_t give_mass(int pid){
	Float_t mass;
	if(abs(pid)==211) mass=0.129883;
	if(abs(pid)==130) mass=0.5;
	if(abs(pid)==11)  mass=0.00500488;
	if(abs(pid)==13)  mass=0.10498;
	if(abs(pid)==22)  mass=0;
	return mass;
}

Int_t sign(int pid){
	Int_t charge;
	if(pid==22 || pid==130) charge=0;
	else{
		if(pid<0) charge=-1;
		if(pid>0) charge=1;
	}


	return charge;
}
