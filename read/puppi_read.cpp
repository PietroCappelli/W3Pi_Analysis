#include "translate.h"

int main(){

	std::fstream file("project/proj/solution1/csim/build/hello.bin", std::ios_base::in |  std::ios_base::binary);

	if(!file.good()){
	std::cout << "error opening file" << std::endl;
	}

	uint64_t puppi;
	std::vector<uint64_t> puppis;
	std::vector<float> pt_vec;
	std::vector<float> eta_vec;
	std::vector<float> phi_vec;
	std::vector<int>   pid_vec;
	uint8_t Npuppi;
	uint n=0;
	int i = 0;
	while(file.read(reinterpret_cast<char*>(&puppi), sizeof(puppi))){
		
		puppis.push_back(puppi);
		//file.seekg(sizeof(puppi), std::ios::cur);
		float pt;
		float eta;
		float phi;
		short int id;
		convert(puppi, pt, eta, phi, id);
		
		pt_vec.push_back(pt);
		eta_vec.push_back(eta);
		phi_vec.push_back(phi);
		pid_vec.push_back(id);
		n++;
	//	if( abs(eta) > 2.4 or abs(phi)>3.14 ) i++;
	}
	
	std::cout << "errors = " << i << std::endl;

	uint64_t first_puppi = puppis[0];
	file.read(reinterpret_cast<char*>(&first_puppi), sizeof(first_puppi));
	std::cout << "\nfirst_puppi: "<< first_puppi << std::endl;

	std::cout << "pt "  << pt_vec[0]  << std::endl;
	std::cout << "eta " << eta_vec[0] << std::endl;
	std::cout << "phi " << phi_vec[0] << std::endl;
	std::cout << "id "  << pid_vec[0]  << std::endl;
	//std::cout << "fill "  << fill << std::endl;
	std::cout << "Npuppi = " << npuppi << std::endl;
	
	file.close();

	
	std::ofstream output_file("p_feats.dat");

//	output_file << ;
	for(const auto &p : pt_vec) output_file << p << " ";
	output_file << "\n";
	for(const auto &e : eta_vec) output_file << e << " ";
	output_file << "\n";
	for(const auto &ph : phi_vec) output_file << ph << " ";
	output_file << "\n";	
	for(const auto &id : pid_vec) output_file << id << " ";
//	output_file << "};";
	
	return 0;
	
}
