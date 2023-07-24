#include "translate.h"

int main(){

	// std::fstream file("output.txt", std::ios_base::in |  std::ios_base::binary);
	std::ifstream input("particles.txt");

	if(!input.good()){
	std::cout << "error opening file" << std::endl;
	}

	// uint64_t puppi;
	std::vector<uint64_t> puppis;
	std::vector<float> pt_vec;
	std::vector<float> eta_vec;
	std::vector<float> phi_vec;
	std::vector<int>   pid_vec;
	uint8_t Npuppi;
	int event = 0;

	std::string line;
	std::vector<int> N_Puppi_Event;

	while (std::getline(input, line)) {
		// leggo una riga i-esima (line) => un evento
		std::stringstream ss(line);
		std::string word;
		int wordCount = 0;
		while(ss >> std::hex >> word){
			// spacchetto una particella alla volta dalla riga i-esima (line)
			// std::cout << word << std::endl;
			uint64_t puppi = std::stoull(word, nullptr, 16);
			puppis.push_back(puppi);
			float pt;
			float eta;
			float phi;
			short int id;
		
			convert(puppi, pt, eta, phi, id);

			pt_vec.push_back(pt);
			eta_vec.push_back(eta);
			phi_vec.push_back(phi);
			pid_vec.push_back(id);

			wordCount++;
		}
		N_Puppi_Event.push_back(wordCount);
		std::cout << "Number of particles in the event " << event << " are: " << N_Puppi_Event[event] << std::endl;
		event++;

	}
	
	uint64_t first_puppi = puppis[0];
	std::cout << "\nfirst_puppi: "<< first_puppi << std::endl;
	std::cout << "pt "  << pt_vec[0]  << std::endl;
	std::cout << "eta " << eta_vec[0] << std::endl;
	std::cout << "phi " << phi_vec[0] << std::endl;
	std::cout << "id "  << pid_vec[0]  << std::endl;
	std::cout << "Npuppi = " << N_Puppi_Event[0] << std::endl;
	
	input.close();

	// write on file
	std::ofstream output_file("p_feats.dat");
	for(const auto &p : pt_vec) output_file << p << " ";
	output_file << "\n";
	for(const auto &e : eta_vec) output_file << e << " ";
	output_file << "\n";
	for(const auto &ph : phi_vec) output_file << ph << " ";
	output_file << "\n";	
	for(const auto &id : pid_vec) output_file << id << " ";

	std::ofstream output_file_n("n_puppi.dat");
	for(const auto &p : N_Puppi_Event) output_file_n << p << " ";
	output_file_n << "\n";

	return 0;
	
}