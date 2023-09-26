#include <cstdio>
#include <iostream>
#include <cstdint>
#include <vector>
#include <TTree.h>
#include <TFile.h>
#include <Compression.h>
#include <TROOT.h>
#include <ROOT/RNTuple.hxx>
#include <ROOT/RNTupleModel.hxx>
#include <ROOT/RNTupleUtil.hxx>
#include <ROOT/RLogger.hxx>
#include <TStopwatch.h>
#include <string>
#include "unpack_tree.h"


void un(const char* in, const char* out, std::string format) {
    
    TStopwatch timer;
    std::fstream fin(in, std::ios_base::in | std::ios_base::binary);
    std::cout << "opening input file:" << in << std::endl;
    if (!fin.good()) {
        printf("Error opening input file %s\n", in);
    }
    const char *foutname = out;
    std::cout << "out file name: " << foutname << "\n" << std::endl;
    if(format == "tree"){
	    int compressionLevel = 0;
	    TFile *fout = nullptr;
	    TTree *tree = nullptr;
	    fout = TFile::Open(foutname, "RECREATE", "", compressionLevel);
	    tree = new TTree("Events", "Events");
	    unsigned long entries = 0;
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
	    while (fin.good()) {
		    readevent(fin, header, run, bx, orbit, good, npuppi, data, pt, eta, phi, pdgid, z0, dxy, quality, wpuppi, id );
		    if (tree) {
		        if(header != 0) {
			        tree->Fill();
			        entries++;
		        }
		    }
	    }  
	    if (tree) {
		    tree->Write();
		    fout->Close();
	    }
	    timer.Stop();
	    std::cout << "entries: " << entries << std::endl;
	    double tcpu = timer.CpuTime(), treal = timer.RealTime();
	    report(tcpu, treal, entries, in, out);
	}

    if(format == "rntuple"){
        TStopwatch timer;
        unsigned long entries = 0;
        
        uint64_t header, data[255];
        auto submodel = ROOT::Experimental::RNTupleModel::Create();
        auto p_pt = submodel->MakeField<float>("pt");
        auto p_eta = submodel->MakeField<float>("eta");
        auto p_phi = submodel->MakeField<float>("phi");
        auto p_pdgid = submodel->MakeField<short int>("pdgId");
        auto p_z0 = submodel->MakeField<float>("z0");
        auto p_dxy = submodel->MakeField<float>("dxy");
        auto p_wpuppi = submodel->MakeField<float>("wpuppi");
        auto p_quality = submodel->MakeField<uint16_t>("quality");

        auto model = ROOT::Experimental::RNTupleModel::Create();
        auto p_run = model->MakeField<uint16_t>("run");
        auto p_orbit = model->MakeField<uint32_t>("orbit");
        auto p_bx = model->MakeField<uint16_t>("bx");
        auto p_good = model->MakeField<bool>("good");
        auto c_puppi = model->MakeCollection("Puppi", std::move(submodel));
        std::unique_ptr<ROOT::Experimental::RNTupleWriter> writer;
        if (foutname) {
            int compressionLevel = 0;
            int compression = 0;
            //compression = ROOT::CompressionSettings("", compressionLevel);
            std::cout << "opening " << foutname << std::endl;
            ROOT::Experimental::RNTupleWriteOptions options;
            options.SetCompression(compression);
            writer = ROOT::Experimental::RNTupleWriter::Recreate(std::move(model), "Events", foutname, options);
        }
        uint16_t npuppi;
        while (fin.good()) {
            readheader(fin, header, *p_run, *p_bx, *p_orbit, *p_good, npuppi);
            if(header != 0){
                if (npuppi)
                    fin.read(reinterpret_cast<char *>(&data[0]), npuppi * sizeof(uint64_t));
                for (unsigned int i = 0, n = npuppi; i < n; ++i) {
                    readshared(data[i], *p_pt, *p_eta, *p_phi);
                    if (readpid(data[i], *p_pdgid)) {
                        readcharged(data[i], *p_z0, *p_dxy, *p_quality);
                        *p_wpuppi = 0;
                    } else {
                        readneutral(data[i], *p_wpuppi, *p_quality);
                        *p_z0 = 0;
                        *p_dxy = 0;
                    }
                    if (writer)
                        c_puppi->Fill();
                }
                if (writer)
                    writer->Fill();
                	entries++;
            }
            else continue;
        }
        timer.Stop();
        double tcpu = timer.CpuTime(), treal = timer.RealTime();
	    report(tcpu, treal, entries, in, out);
    }
}

int main(int argc, char **argv){
	
    std::string format = argv[3];
    un(argv[1], argv[2], format);	

    return 0;	
}


