#include "translate.h"


int main(){

	std::ifstream file("capture_2.dump", std::ios_base::in |  std::ios_base::binary);
    if(!file.good()){
	    std::cout << "error opening file" << std::endl;
	}

	uint64_t header;
    uint64_t puppi;
	uint8_t  Npuppi;
	std::vector<float> pt_vec;
	std::vector<float> eta_vec;
	std::vector<float> phi_vec;
	std::vector<int>   pid_vec;
	std::vector<int>   N_vec;

    // while(true)
    while(true){
        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (file.gcount() < sizeof(header)) {
            break;
        }

        if(header==0){
            std::cout << "null header?\n";
            continue;
        }
        Npuppi = header & 0xFF;
        N_vec.push_back(Npuppi);

        for(int i=0; i<Npuppi;i++){
            file.read(reinterpret_cast<char*>(&puppi), sizeof(puppi));
            float pt;
            float eta;
            float phi;
            short int id;
            convert(puppi, pt, eta, phi, id);
    		pt_vec.push_back(pt);
            eta_vec.push_back(eta);
            phi_vec.push_back(phi);
            pid_vec.push_back(id);
        }
        if (file.gcount() < sizeof(header)) {
            break;
        }

    }

    std::cout << "First puppi candidate features\n";
	std::cout << "pt "  << pt_vec[0]  << std::endl;
	std::cout << "eta " << eta_vec[0] << std::endl;
	std::cout << "phi " << phi_vec[0] << std::endl;
	std::cout << "id "  << pid_vec[0]  << std::endl;
	std::cout << "Npuppi = " << N_vec[0] << std::endl;
	
	file.close();

    // file per puppi features
    std::ofstream output("p-feats-from-DTH.dat");
	
    for(const auto &p : pt_vec) output << p << " ";
	output << "\n";
	for(const auto &e : eta_vec) output << e << " ";
	output << "\n";
	for(const auto &ph : phi_vec) output << ph << " ";
	output << "\n";	
	for(const auto &id : pid_vec) output << id << " ";

    // file per N puppi
	std::ofstream output_n("n-puppi-from-DTH.dat");

	for(const auto &p : N_vec) output_n << p << " ";
	output_n << "\n";

    std::cout << "\nnumber of events: " << N_vec.size() << std::endl;
    std::cout << "\nnumber of pts: " << pt_vec.size() << std::endl;


    return 0;
}