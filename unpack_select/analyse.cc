#include "analyse.h"


int analyse(const char* file_in, const char* file_out, std::string input_format,std::string output_format){

    std::string c_pt, c_eta, c_phi, c_pdgId;
    bool isRNtuple = (input_format=="rntuple");
    std::vector<std::string> rows_to_save;

    if(isRNtuple){
        c_pt  = "Puppi.pt";
        c_eta = "Puppi.eta";
        c_phi = "Puppi.phi";
        c_pdgId = "Puppi.pdgId";
        rows_to_save={"run","orbit","bx","good","nPuppi","Puppi.pt","Puppi.eta","Puppi.phi","Puppi.pdgId","Puppi.z0","Puppi.dxy","Puppi.wpuppi","Puppi.quality","Triplet_Index","Triplet_invmass"};

    }
    else{
        c_pt  = "Puppi_pt";
        c_eta = "Puppi_eta";
        c_phi = "Puppi_phi";
        c_pdgId = "Puppi_pdgId";
        rows_to_save = {"run","orbit","bx","good","nPuppi","Puppi_pt","Puppi_eta","Puppi_phi","Puppi_pdgId","Puppi_z0","Puppi_dxy","Puppi_wpuppi","Puppi_quality","Triplet_Index","Triplet_invmass"};

    }

    TStopwatch timer;
    ROOT::RDataFrame df = isRNtuple ? ROOT::RDF::Experimental::FromRNTuple("Events", file_in) : ROOT::RDataFrame("Events", file_in);
    auto df0 = df.Filter(initptcut, {c_pt, c_pdgId});
    auto df1 = df0.Define("Triplet_Index", triplet_index, {c_pdgId, c_pt, c_eta, c_phi})
            .Filter(notempty,{"Triplet_Index"})
            .Define("Triplet_invmass",tripletmass,{"Triplet_Index", c_pt, c_eta, c_phi});
    auto n0 = *df.Count();
    auto n00 = *df0.Count();
    // auto n1 = *df1.Count();
    auto masshist = df1.Histo1D<float>({"masshist", "W Boson mass from selected pions; mass (GeV/c^2)", 100, 40, 120}, "Triplet_invmass");
    unsigned int n1 = masshist->GetEntries();
    
    if(output_format=="snapshot"){
        df1.Snapshot<UShort_t,  //run
                    UInt_t,     //orbit
                    UShort_t,   //bx
                    bool,       //good
                    UShort_t,   //npuppi
                    ROOT::RVec<Float_t>,    // pt
                    ROOT::RVec<Float_t>,    // eta
                    ROOT::RVec<Float_t>,    // phi
                    ROOT::RVec<Short_t>,    // pid
                    ROOT::RVec<float>,      // z0
                    ROOT::RVec<Float_t>,    // dxy
                    ROOT::RVec<Float_t>,    // wpuppi
                    ROOT::RVec<float>,      // quality
                    ROOT::RVec<float>,      // triplet index
                    float       // invarian mass
                    >("Events", file_out, rows_to_save);
    }
    else if(output_format=="histo"){
        TFile *Fout = TFile::Open(file_out, "RECREATE", "", 0);
        Fout -> WriteTObject(masshist->Clone());
        Fout -> Close();
    }
    else printf("ERROR: Wrong output format.\n output = snapshot or histo");
    

    timer.Stop();
    printf("Run on tree.root, %9u events, preselected %8u events, selected %8u events (%.6f) in %7.3f s (%7.1f kHz)\n",
        n0, n00, n1, n1 / float(n0), timer.RealTime(), n0 * .001 / timer.RealTime());

    return 0;
}

int main(int argc, char** argv){
    if (argc <= 4) {
        std::cout << "Usage: inputFile.root (format)" << std::endl;
	    return 1;
    }
    std::string in_format  = argv[3];
    std::string out_format = argv[4];
    analyse(argv[1], argv[2], in_format, out_format);

    return 0;
}


