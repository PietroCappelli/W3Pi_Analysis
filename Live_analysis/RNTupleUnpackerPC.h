#include <chrono>
#include <TROOT.h>
#include <TFile.h>
#include <ROOT/RNTuple.hxx>
#include <ROOT/RNTupleModel.hxx>
#include <ROOT/RNTupleUtil.hxx>
#include "UnpackerBase.h"
#include "unpack.h"

class RNTupleUnpackPC : public UnpackerBase {

public:
    // set a random compression algo and put compression level = 0 ! we work without compression for now
    RNTupleUnpackPC() : compression_(0) {} 
    ~RNTupleUnpackPC() override {}

protected:
    int compression_;

    Report unpack(const std::vector<std::string> &ins, const std::string &fout) const {
        //working with only one input file
        auto tstart = std::chrono::steady_clock::now();
        std::vector<std::fstream> fins;
        for(auto &in : ins){
            fins.emplace_back(in, std::ios_base::in | std::ios_base::binary);
            if(!fins.back().good()){
                throw std::runtime_error("Error opening " + in + " as input file\n");
            }
        }
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
        
        if (fout.c_str()) {
            std::cout << "opening " << fout << std::endl;
            ROOT::Experimental::RNTupleWriteOptions options;
            options.SetCompression(compression_);
            writer = ROOT::Experimental::RNTupleWriter::Recreate(std::move(model), "Events", fout.c_str(), options);
        }
        uint16_t npuppi;
        unsigned long entries = 0;
        for (int ifile = 0, nfiles = fins.size(); fins[ifile].good(); ifile = (ifile == nfiles - 1 ? 0 : ifile + 1)) {
            std::fstream &fin = fins[ifile];
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
        }
        
        if(writer){
            writer->CommitCluster();
            writer.reset();
        }

        double dt = (std::chrono::duration<double>(std::chrono::steady_clock::now() - tstart)).count();
        return make_report(dt, entries, fin.c_str(), fout.c_str());
    }
};

