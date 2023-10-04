#include "gen4.h"

//#ifndef __SYNTHESIS__
//std::cout << std::endl;
//#endif

Xoshiro256ssRef::Xoshiro256ssRef() {}

uint64_t Xoshiro256ssRef::rol64(uint64_t x, int k) { return (x << k) | (x >> (64 - k)); }

uint64_t Xoshiro256ssRef::operator()(bool setseed, uint64_t seed) {
  uint64_t const result = rol64(state[1] * 5, 7) * 9;
  if (setseed) {
	state[0] = seed ^ 0x6b54c6575a2c794b;
	state[1] = rol64(seed, 13) ^ 0x514e9359bb2950cb;
	state[2] = rol64(seed, 27) ^ 0xc62c17550e3d1904;
	state[3] = rol64(seed, 42) ^ 0xf47e648fdd3da813;
	uint64_t const result = rol64(state[1] * 5, 7) * 9;
  } else {
	uint64_t const t = state[1] << 17;
	state[2] ^= state[0];
	state[3] ^= state[1];
	state[1] ^= state[2];
	state[0] ^= state[3];
	state[2] ^= t;
	state[3] = rol64(state[3], 45);
	uint64_t const result = rol64(state[1] * 5, 7) * 9;
  }
  return result;
}


////////////////////////////////////////////////////////////////////
ap_uint<8> calculate_Npuppi(ap_uint<12> rnd){
	ap_ufixed<10,8> N0 = 33;
	ap_ufixed<12,12, AP_RND> N = N0 * NLUT[rnd]; // using k=1.45
	ap_uint<8> Np = (N).to_uint();
	ap_uint<8> Npuppi = (Np < 208) ? Np:ap_uint<8>(208);
	return Npuppi;
}

//ap_uint<8> calculate_Npuppi_Nin(ap_uint<12> rnd, ap_uint<10> N0){
////	ap_ufixed<10,8> N0 = 28.5;
//	ap_ufixed<12,12, AP_RND> N = N0 * NLUT[rnd]; // using k=1.45
//	ap_uint<8> Np = (N).to_uint();
//	ap_uint<8> Npuppi = (Np < 208) ? Np:ap_uint<8>(208);
//	return Npuppi;
//}


////////////////////////////////////////////////////////////////////
ap_uint<3> assign_pid(ap_uint<11> rnd){
	ap_uint<10> prob = (rnd(9,0) * 1000) >> 10;
	ap_uint<1> charge = rnd(10,10);
	ap_uint<3> p_id_gen;

	if(prob <= idLUT[0]) { //pion
	    if(charge) p_id_gen = 2;
	    else  p_id_gen = 3;
	}
	if(prob>idLUT[0] && prob<= idLUT[1]) { // mu
	    if(charge) p_id_gen = 6;
	    else  p_id_gen = 7;
	}
	if(prob>idLUT[1] && prob<= idLUT[2]){ // e
	    if(charge) p_id_gen = 4;
	    else  p_id_gen = 5;
	}
	if(prob>idLUT[2] && prob<= idLUT[3]) {
		p_id_gen = 1; //gamma
	}
	if(prob>idLUT[3] && prob<= idLUT[4]){
		p_id_gen = 0; //h0
	}
	return p_id_gen;

}

////////////////////////////////////////////////////////////////////
ap_uint<64> gen_puppi(ap_uint<64> rnd){
	ap_uint<64> puppi = 0;
	ap_uint<10> idx   = rnd(9,0);
	ap_uint<24> fill  = rnd(34,10);
	ap_uint<14> pt  = ptLUT[idx];
	ap_uint<12> ueta = (rnd(11,0) * 1100) >> 12;
	ap_int<12> eta = static_cast<ap_int<12>>(ueta) - 550;
	ap_uint<11> uphi = (rnd(10,0) * 1440) >> 11;
	ap_int<11> phi = static_cast<ap_int<11>>(uphi) - 720;
	ap_uint<3>  id  = assign_pid(rnd(21,11));
	puppi(13,0) = pt;
	puppi(25,14) = eta;
	puppi(36,26) = phi;
	puppi(39,37) = id;
	puppi(63,40) = fill;
	return puppi;
}

////////////////////////////////////////////////////////////////////
//void gen4(bool valid, bool set, ap_uint<64> seed, ap_uint<64> data_out[4], bool orbit_out[4], bool start_out[4], bool end_out[4], bool valid_out[4], ap_uint<4> CLOCK_RATIO_MINUS_ONE){
//void gen4(bool valid, bool set, ap_uint<64> particle_idx1 , ap_uint<64> particle_idx2,  ap_uint<64> particle_idx3, ap_uint<64> particle_idx4, ap_uint<64> data_out[4], bool orbit_out[4], bool start_out[4], bool end_out[4], bool valid_out[4], ap_uint<4> CLOCK_RATIO_MINUS_ONE){
//void gen4(bool valid, bool set, ap_uint<64> particle_idx, ap_uint<64> npuppi_idx, ap_uint<64> data_out[4], bool orbit_out[4], bool start_out[4], bool end_out[4], bool valid_out[4], ap_uint<4> CLOCK_RATIO_MINUS_ONE){
void gen4(bool valid, bool set, ap_uint<64> p_idxs[4], ap_uint<64> data_out[4], bool orbit_out[4], bool start_out[4], bool end_out[4], bool valid_out[4], ap_uint<4> CLOCK_RATIO_MINUS_ONE){

	// input: p_idxs with the 4 random numbers (generated outside the main)
	//output: start_out, end_out, valid_out -> arrays of 4 bool elements;
	//			data_out -> array of 4 elements (particles)

	#pragma HLS array_partition variable = data_out complete
	#pragma HLS array_partition variable = orbit_out complete
	#pragma HLS array_partition variable = start_out complete
	#pragma HLS array_partition variable = end_out complete
	#pragma HLS array_partition variable = p_idxs complete
	#pragma HLS array_partition variable = valid_out complete
	#pragma HLS stable variable = CLOCK_RATIO_MINUS_ONE
	#pragma HLS pipeline II = 1

	//variables
	static ap_uint<8>  irow = 0, count = 54; //max 54 rows
	static ap_uint<10> rptr = 0, wptr = 0;
	static bool running;//false
	static ap_uint<8> npuppi, nremaining;
	static bool orbit;
//	std::cout << " valid : " << valid << std::endl;

	for(short int i=0; i<4; ++i){
		data_out[i]  = 0;
		valid_out[i] = 0;
		orbit_out[i] = 0;
		start_out[i] = 0;
		end_out[i]   = 0;
	}

	if(valid && set){ //starting
//	if(valid){ //starting
		irow=0;
		running = true;
		orbit = true;
//		N0=;
//		npuppi = calculate_Npuppi(p_idxs[0](10,0));
		npuppi = calculate_Npuppi_Nin(p_idxs[0](10,0));
	} else if(running){
		if(irow==0){
//			std::cout << "number of candidates = " << npuppi << std::endl;
			for(short int i=0; i<4; ++i){
//				ap_uint<64> id = rng(false,0);
				data_out[i]  = gen_puppi(p_idxs[i]);
				valid_out[i] = true;
//				orbit_out[i] = rptr==0;
				orbit_out[i] = orbit;
				start_out[i] = true;
				end_out[i]   = npuppi <= 4+i;
			}
			irow=1;
			nremaining = npuppi<=4? ap_uint<8> (0) : ap_uint<8>(npuppi - 4);
		}//first row full
		else{
//			std::cout << "n remaining = " <<  nremaining << std::endl;
			for(short int i=0; i<4; ++i){
//				ap_uint<64> id = rng(false,0);
//				data_out[i]  = (i<nremaining)? gen_puppi(id) : ap_uint<64> (0);
				data_out[i]  = (i<nremaining)? gen_puppi(p_idxs[i]) : ap_uint<64> (0);
				valid_out[i] = (i<nremaining);
				orbit_out[i] = false;
				start_out[i] = false;
				end_out[i] = i < nremaining && i >= nremaining - 4;
			}
			nremaining = nremaining<=4? ap_uint<8> (0) : ap_uint<8>(nremaining - 4);
			if(irow==count - 1) {
				irow=0;
				orbit=false; //is a static bool, preserve false
				npuppi = calculate_Npuppi(p_idxs[0](10,0));
//				if(rptr!=wptr) {
//					rptr++;
//					npuppi = calculate_Npuppi(p_idxs[0](10,0));
//				}
//				else running=false;
			}
			else irow++;
		}
//		if(valid){
//			wptr++;
//		}
	}
}
