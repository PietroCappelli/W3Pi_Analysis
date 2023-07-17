#include "gen4.h"
#include <time.h>

int main(){

	bool valid1;
	bool valid2;
	ap_uint<64> seed, seed_p1, seed_p2, seed_p3, seed_p4;
	ap_uint<64> particle_idx1,particle_idx2,particle_idx3,particle_idx4;
	ap_uint<64> npuppi_idx;

	ap_uint<64> data_out[4];
	bool orbit_out[4];
	bool start_out[4];
	bool end_out[4];
	bool valid_out[4];

	seed  = time(NULL);
	seed_p1  = time(NULL);
	seed_p2  = time(NULL);
	seed_p3  = time(NULL);
	seed_p4  = time(NULL);
	Xoshiro256ssRef rng_particle1;
	Xoshiro256ssRef rng_particle2;
	Xoshiro256ssRef rng_particle3;
	Xoshiro256ssRef rng_particle4;
	// SET ALL THE SEEDS
	rng_particle1(true, seed*1);
	rng_particle2(true, seed*2);
	rng_particle3(true, seed*3);
	rng_particle4(true, seed*4);

	Xoshiro256ssRef rng_npuppi;
	rng_npuppi(true, seed*5);

//	std::cout << "seed " << seed << std::endl;


//	for(int j=0; j<200; j++){
//		std::cout << "\n\nj= " << j << std::endl;
//		if(j==0){
//			seed = time(NULL);
//			std::cout << "seed k=0 " << seed << std::endl;
//			valid=true;
//		}
//		if(j==1){
//			seed = time(NULL) * j;
//			std::cout << "\nseed k=1 " << seed << std::endl;
//			valid=false;
//		}
//		if(j==2){
//			seed = time(NULL) * j;
//			std::cout << "\nseed k=2 " << seed << std::endl;
//			valid=false;
//		}
//		gen4(valid, seed, data_out, orbit_out, start_out, end_out, valid_out, 1);
//
//		for(short int i=0; i<4; ++i){
//			std::cout << "particle i=" << i << ":\t " << data_out[i] << " \t" << valid_out[i] << "\t" << orbit_out[i] << "\t" << start_out[i] << "\t"<< end_out[i] << std::endl;
//		}
//	}
	for (unsigned int frame = 0; frame < 1024; ++frame) {
//		seed  = time(NULL) * frame;
		// GENERATE NUMBERS
		ap_uint<64> p_idxs[4] = {0x0036000100000025,0x000000000000004b,0x000000000000004b,0x000000000000004b};
//		ap_uint<64> p_idxs_35[4] = {0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000};

//		ap_uint<64> npuppi_idx   = rng_npuppi(false,0);
//		if (frame <= 5) {
//		  valid1 = false;
//		  valid2 = false;
//		} else if (frame == 6) {
//		  valid1 = true;
//		  valid2 = true;
//		} else if (frame == 7) {
//		  valid1 = true;
//		  valid2 = false;
//		} else if (frame == 8) {
//		  valid1 = true;
//		} else if (frame == 10) {
//		  valid1 = true;
//		} else if (frame <= 12) {
//		  valid1 = true;
//		} else {
//			valid1 = false;
//		}
		if(frame<9){
			valid1=false;
			valid2=false;
		}
		else if(frame == 9){
			valid1=true;
			valid2=true;
		}
		else if(frame>9 && frame<35){
			valid1=true;
			valid2=false;
		}
		else if(frame==35){
			valid1=false;
			valid2=false;
		}

//		if(frame<=35){
			gen4(valid1, valid2, p_idxs, data_out, orbit_out, start_out, end_out, valid_out, 1);
//		}
//		else{
//			gen4(valid1, valid2, p_idxs_35, data_out, orbit_out, start_out, end_out, valid_out, 1);
//		}
		std::cout << std::setbase(10) << "Frame  " << frame << "\t";
		for(short int i=0; i<4; ++i){
//			std::cout << "particle i=" << i << ":\t " << data_out[i] << " \t" << valid_out[i] << "\t" << orbit_out[i] << "\t" << start_out[i] << "\t"<< end_out[i] << std::endl;
			std::cout << orbit_out[i] << start_out[i] << end_out[i] << valid_out[i] << " " << std::hex << data_out[i] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
