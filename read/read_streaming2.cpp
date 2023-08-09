#include "translate.h"


int main(){

	std::fstream file("capture_data/capture_1_seed.dump", std::ios_base::in |  std::ios_base::binary);
    if(!file.good()){
	    std::cout << "error opening file" << std::endl;
	}

    TFile *fout = TFile::Open("stream2.root", "RECREATE");
    TTree *tree = new TTree("Events", "Events");

	uint64_t header;
	uint16_t Npuppi;
	uint16_t bx;
	uint32_t orbit;
	uint16_t run;
    std::vector<uint64_t> puppi;
	
    std::vector<float> pt;
	std::vector<float> eta;
	std::vector<float> phi;
	std::vector<short int> pid;
	std::vector<int>   charge;
	std::vector<float> mass;
	std::vector<float> z0;
	std::vector<float> dxy;
	std::vector<uint16_t> quality;
	std::vector<float>   wpuppi;
	std::vector<uint16_t> eg_id;

	std::vector<int> N;

    tree->Branch("pt",   &pt);
    tree->Branch("eta",  &eta);
    tree->Branch("phi",  &phi);
    tree->Branch("pid",  &pid);
    tree->Branch("charge", &charge);
    tree->Branch("mass",   &mass);
    tree->Branch("Npuppi", &Npuppi);
    tree->Branch("Orbit", &orbit);

    tree->Branch("z0",  &z0);
    tree->Branch("dxy", &dxy);
    tree->Branch("quality", &quality);
    tree->Branch("wpuppi",  &wpuppi);
    tree->Branch("eg_id",   &eg_id);

    TStopwatch timer;
    timer.Start();

    while(file.good()){
        pt.clear();
        eta.clear();
        phi.clear();
        pid.clear();
        mass.clear();
        charge.clear();

        readevent(file, header, puppi, run, bx, orbit, Npuppi,
                    pt, eta, phi, pid, charge, mass, z0, dxy, wpuppi, quality, eg_id);
        
        if(header!=0) tree->Fill();
    }

    tree->Write();
	fout->Close();
    file.close();
    timer.Stop();

    double tcpu = timer.CpuTime(), treal = timer.RealTime();
    std::cout << "timer: " << tcpu << ", real: " << treal << std::endl;

    return 0;
}