#include <chrono>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include "UnpackerBase.h"
#include "unpack.h"

class TTreeUnpackerPC : public UnpackerBase {

public:
    // set a random compression algo and put compression level = 0 ! we work without compression for now
    TTreeUnpackerPC() : compressionAlgo_(ROOT::RCompressionSetting::EAlgorithm::kZLIB), compressionLevel_(0) {} 
    ~TTreeUnpackerPC() override {}

    Report unpack(const std::vector<std::string> &ins, const std::string &fout) const override = 0;
    void setThreads(unsigned int threads) override;
    void setCompression(const std::string &algo, unsigned int level) override;

protected:
    int compressionAlgo_, compressionLevel_;

    Report unpack(const std::vector<std::string> &fin, const std::string &fout) const {
        //working with only one input file
        auto tstart = std::chrono::steady_clock::now();

        std::vector<std::fstream> fins;
        for(auto &in : ins){
            fins.emplace_back(in, std::ios_base::in | std::ios_base::binary);
            if(!fins.back().good()){
                throw std::runtime_error("Error opening " + in + " as input file\n");
            }
        }
        TFile *out_file = nullptr;
        TTree *tree = nullptr;
        out_file = TFile::Open(fout.c_str(), "RECREATE", "", compressionLevel_);
        if (out_file == nullptr || !out_file) {
            throw std::runtime_error("Error opening " + fout + " for output");
        }
        tree = new TTree("Events", "Events");
        //set the branches
	    uint64_t header, data[255];
	    uint16_t run, bx;
	    uint32_t orbit;
	    Bool_t good;
	    uint16_t npuppi;
	    float pt[255], eta[255], phi[255];
	    short int pdgid[255];
	    float z0[255];
	    float dxy[255];
	    float wpuppi[255];
	    uint16_t quality[255];
	    uint16_t id[255];
	    if (tree) {
            tree->Branch("run", &run, "run/s");
            tree->Branch("orbit", &orbit, "orbit/i");
            tree->Branch("bx", &bx, "bx/s");
            tree->Branch("good", &good, "good/O");
            tree->Branch("nPuppi", &npuppi, "nPuppi/s");
            tree->Branch("Puppi_pt", &pt, "Puppi_pt[nPuppi]/F");
            tree->Branch("Puppi_eta", &eta, "Puppi_eta[nPuppi]/F");
            tree->Branch("Puppi_phi", &phi, "Puppi_phi[nPuppi]/F");
            tree->Branch("Puppi_pdgId", &pdgid, "Puppi_pdgId[nPuppi]/S");
            tree->Branch("Puppi_z0", &z0, "Puppi_z0[nPuppi]/F");
            tree->Branch("Puppi_dxy", &dxy, "Puppi_dxy[nPuppi]/F");
            tree->Branch("Puppi_wpuppi", &wpuppi, "Puppi_wpuppi[nPuppi]/F");
            tree->Branch("Puppi_quality", &quality, "Puppi_quality[nPuppi]/b");
            tree->Branch("Puppi_id", &id, "Puppi_id[nPuppi]/b");
		}
	    unsigned long entries = 0;
        for (int ifile = 0, nfiles = fins.size(); fins[ifile].good(); ifile = (ifile == nfiles - 1 ? 0 : ifile + 1)) {
            std::fstream &fin = fins[ifile];
            while (fin.good()) {
                readevent(fin, header, run, bx, orbit, good, npuppi, data, pt, eta, phi, pdgid, z0, dxy, quality, wpuppi, id );
                if (tree) {
                    if(header != 0) {
                        tree->Fill();
                        entries++;
                    }
                }
            }        
        }

	    if (tree) {
		    tree->Write();
		    out_file->Close();
	    }
        double dt = (std::chrono::duration<double>(std::chrono::steady_clock::now() - tstart)).count();
        return make_report(dt, entries, fin.c_str(), fout.c_str());
    }
};