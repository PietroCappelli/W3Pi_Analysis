#include "unpack.h"


int main(){

	std::fstream file("capture_data/capture_4_seed.dump", std::ios_base::in |  std::ios_base::binary);
    if(!file.good()){
	    std::cout << "error opening file" << std::endl;
	}

    TFile *fout = TFile::Open("stream.root", "RECREATE");
    TTree *tree = new TTree("Events", "Events");

	uint64_t header;
	uint16_t Npuppi;
	uint16_t bx;
	uint16_t orbit;
	uint16_t run;
    uint64_t puppi;

	std::vector<float> pt_vec;
	std::vector<float> eta_vec;
	std::vector<float> phi_vec;
	std::vector<int>   pid_vec;
	std::vector<int>   charge_vec;
	std::vector<float> mass_vec;

	std::vector<int>   N_vec;

    tree->Branch("pt",   &pt_vec);
    tree->Branch("eta",  &eta_vec);
    tree->Branch("phi",  &phi_vec);
    tree->Branch("pid",  &pid_vec);
    tree->Branch("charge", &charge_vec);
    tree->Branch("mass",   &mass_vec);
    tree->Branch("Npuppi", &Npuppi);

    TStopwatch timer;
    timer.Start();

    while(true){

        pt_vec.clear();
        eta_vec.clear();
        phi_vec.clear();
        pid_vec.clear();
        mass_vec.clear();
        charge_vec.clear();

        // file.read(reinterpret_cast<char*>(&header), sizeof(header));
        readheader(file, header, Npuppi, bx, orbit, run);
        if (file.gcount() < sizeof(header)) {
            break;
        }

        if(header==0){
            // std::cout << "null header?\n";
            continue;
        }
        Npuppi = header & 0xFF;
        N_vec.push_back(Npuppi);
        for(int i=0; i<Npuppi; i++){
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
            mass_vec.push_back(give_mass(id));
            charge_vec.push_back(sign(id));
            if(pt>100) std::cout << "error\n";
        }
        tree->Fill();
        if (file.gcount() < sizeof(header)) {
            break;
        }
    }
    tree->Write();
	fout->Close();
    file.close();
    timer.Stop();

    double tcpu = timer.CpuTime(), treal = timer.RealTime();
    std::cout << "timer: " << tcpu << ", real: " << treal << std::endl;
    return 0;
}
