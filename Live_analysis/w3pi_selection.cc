//implementation of the main function used for the selection
#include "w3pi_selection.h"

#include "ROOT/RNTupleDS.hxx"
#include <ROOT/RSnapshotOptions.hxx>
#include <chrono>

//extension for the class w3pi_selection
    // implementation of analyze function

w3pi_selection::w3pi_selection(const std::string &cutChoice, bool verbose) : verbose_(verbose){
    if (cutChoice == "loose"){
        cuts.max_iso = 0.8;
        cuts.min_mass = 40;
        cuts.max_mass = 120;
        cuts.min_dr = 0.5;
        cuts.min_dr_iso = 0.01;
        cuts.max_dr_iso = 0.25;
        cuts.H_pt = 15.;
        cuts.I_pt = 12.; 
        cuts.L_pt = 8.;
    }
    if (cutChoice == "tight"){
        cuts.max_iso = 0.8;
        cuts.min_mass = 40;
        cuts.max_mass = 120;
        cuts.min_dr = 0.5;
        cuts.min_dr_iso = 0.01;
        cuts.max_dr_iso = 0.25;
        cuts.H_pt = 15.;
        cuts.I_pt = 12.; 
        cuts.L_pt = 8.;
    }
}

void w3pi_selection::analyze(ROOT::RDataFrame &df,
                            const std::string &format,
                            unsigned long int &ntot,
                            unsigned long int &npre,
                            unsigned long int &npass,
                            const std::string &outFormat,
                            const std::string &outFile) const {
    
    float H_pt = cuts.H_pt, I_pt = cuts.I_pt, L_pt = cuts.L_pt;
    
    //define as lambda functions!
    auto initptcut = [H_pt, I_pt, L_pt](const ROOT::RVec<float> &pts, const ROOT::RVec<short> &pdgids) -> bool {
        int lowcut = 0;
        int intermediatecut = 0;
        int highcut = 0;
        for (int i = 0, n = pts.size(); i < n; ++i) {
            if (std::abs(pdgids[i]) == 11 or std::abs(pdgids[i]) == 211) {
                if (pts[i] >= L_pt) {
                    lowcut++;
                    if (pts[i] >= I_pt) {
                    intermediatecut++;
                    if (pts[i] >= H_pt)
                        highcut++;
                    }
                }
            }
        }
        return (lowcut > 2 and intermediatecut > 1 and highcut > 0);
    };

    auto triplet_index = [&](ROOT::RVec<short> pdg,ROOT::RVec<float> pt, ROOT::RVec<float> eta, ROOT::RVec<float> phi){
        ROOT::RVec<Vec<short>> triplets_index;
        ROOT::RVec<int> charge;
        ROOT::RVec<unsigned int> pdg_idx;
        ROOT::RVec<float> triplets_ptsum;
        // ROOT::RVec<float> triplets_invmass;
        ROOT::RVec<unsigned int> iso_yet(pdg.size(), 0);
        
        for(unsigned int i = 0; i < pdg.size(); ++i) { //make list of pions or electron
            if (abs(pdg[i]) == 211 or abs(pdg[i]) == 11) {
                pdg_idx.push_back(i);
                charge.push_back(pdg[i] > 0 ? +1 : -1);
            }
        }

        if(pdg_idx.size() >= 3){ //check if there is at least one possible triplet passing pt test
            for (unsigned int i=0; i < pdg_idx.size(); i++){
                if(pt[pdg_idx[i]] < cuts.H_pt) continue;
                if(isolation_single(eta, phi, pt, pdg_idx[i]) == false) continue;
                for(unsigned int j=0; j<pdg_idx.size(); j++){
                    if (j==i || pt[pdg_idx[j]] < cuts.L_pt) continue;
                    if (pt[pdg_idx[j]] > pt[pdg_idx[i]] || (pt[pdg_idx[j]] == pt[pdg_idx[i]] and j < i)) continue; //order the pt
                    if (ROOT::VecOps::DeltaR(eta[pdg_idx[i]], eta[pdg_idx[j]], phi[pdg_idx[i]], phi[pdg_idx[j]]) < min_dr) continue;

                    for( unsigned int k=0; k<pdg_idx.size(); k++){
                        if(k==i || k==j || pt[pdg_idx[k]] < cuts.I_pt) continue;
                        if (pt[pdg_idx[k]] > pt[pdg_idx[i]] || pt[pdg_idx[k]]==pt[pdg_idx[i]] && k<i ) continue;
                        if (pt[pdg_idx[k]] > pt[pdg_idx[j]] || pt[pdg_idx[k]]==pt[pdg_idx[j]] && k<j ) continue; //order the pt

                        Vec<unsigned int> triplet = {pdg_idx[i], pdg_idx[j], pdg_idx[k]};
                        if( std::abs( charge[i] + charge[j] + charge[k]) == 1 ){ //charge test
                            //Vec<float> mass_triplet = {0.1396, 0.1396, 0.1396};
                            //auto inv_mass = ROOT::VecOps::InvariantMass(ROOT::VecOps::Take(pt, triplet), ROOT::VecOps::Take(eta,triplet),ROOT::VecOps::Take(phi,triplet), mass_triplet);
                            ROOT::Math::PtEtaPhiMVector p1(pt[pdg_idx[i]], eta[pdg_idx[i]], phi[pdg_idx[i]], 0.1396);
                            ROOT::Math::PtEtaPhiMVector p2(pt[pdg_idx[j]], eta[pdg_idx[j]], phi[pdg_idx[j]], 0.1396);
                            ROOT::Math::PtEtaPhiMVector p3(pt[pdg_idx[k]], eta[pdg_idx[k]], phi[pdg_idx[k]], 0.1396);
                            float inv_mass = (p1 + p2 + p3).M();

                            if(inv_mass >= min_mass && inv_mass <= max_mass){//mass test
                                if(ROOT::VecOps::DeltaR(eta[pdg_idx[k]], eta[pdg_idx[i]], phi[pdg_idx[k]], phi[pdg_idx[i]]) >= min_dr &&
                                ROOT::VecOps::DeltaR(eta[pdg_idx[k]], eta[pdg_idx[j]], phi[pdg_idx[k]], phi[pdg_idx[j]]) >= min_dr){
                                    bool are_iso = true;
                                    for(int t=1; t<3; t++){
                                        if(iso_yet[triplet[t]] == 0){//not calc
                                            if(isolation_single(eta, phi, pt, triplet[t])==false){
                                                iso_yet[triplet[t]] == 2;
                                                are_iso=false;
                                                break;
                                            }
                                            else iso_yet[triplet[t]] = 1;
                                        }
                                        else if(iso_yet[triplet[t]] ==2){//altready calc and not iso
                                            are_iso=false;
                                            break;
                                        }//calc
                                        else if (iso_yet[triplet[t]]==1) continue; //altredy calc and iso
                                    }
                                    if(are_iso){
                                        triplets_index.push_back(triplet); //save triplet
                                        triplets_ptsum.push_back(pt[triplet[0]] + pt[triplet[1]] + pt[triplet[2]]);
                                    }
                                }//DR test
                            }//mass test
                        } //charge test
                    }//thirs pi
                }//second pi
            }//pi loop
        }//if 3 pions

        if(triplets_index.empty())
            triplets_index.emplace_back(); //fill when no triplets passing
        if(triplets_index.size()==1)
            return triplets_index[0];
        // if there is more than one triplet per event
        float bestscore = 0;
        unsigned int best = 0;  //index of best triplet in triplet array
        for (unsigned int i = 0, n = triplets_index.size(); i < n; ++i) {
            float score = triplets_ptsum[i];
        if (score > bestscore) {
            bestscore = score;
            best = i;
            }
        }
        return triplets_index[best];
    };

    std::string c_pt, c_eta, c_phi, c_pdgId;
    std::vector<std::string> rows_to_save;

    if(format == "rntupla"){
        c_pt  = "Puppi.pt";
        c_eta = "Puppi.eta";
        c_phi = "Puppi.phi";
        c_pdgId = "Puppi.pdgId";
        rows_to_save={"run","orbit","bx","good","nPuppi","Puppi.pt","Puppi.eta","Puppi.phi","Puppi.pdgId","Puppi.z0","Puppi.dxy","Puppi.wpuppi","Puppi.quality","Triplet_Index","Triplet_invmass"};
    } else if(format== "tree"){
        c_pt  = "Puppi_pt";
        c_eta = "Puppi_eta";
        c_phi = "Puppi_phi";
        c_pdgId = "Puppi_pdgId";
        rows_to_save = {"run","orbit","bx","good","nPuppi","Puppi_pt","Puppi_eta","Puppi_phi","Puppi_pdgId","Puppi_z0","Puppi_dxy","Puppi_wpuppi","Puppi_quality","Triplet_Index","Triplet_invmass"};
    }
    
    auto n = *df.Count();
    auto df0 = df.Filter(initptcut, {c_pt, c_pdgId});
    auto n0 = *df0.Count();
    auto df1 = df0.Define("Triplet_Index", triplet_index, {c_pdgId, c_pt, c_eta, c_phi})
            .Filter(notempty,{"Triplet_Index"})
            .Define("Triplet_invmass",tripletmass,{"Triplet_Index", c_pt, c_eta, c_phi});
    auto masshist = df1.Histo1D<float>({"masshist", "W Boson mass from selected pions; mass (GeV/c^2)", 100, 40, 120}, "Triplet_invmass");
    if(outFormat == "snapshot"){
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
                    >("Events", outFile.c_str(), rows_to_save);   
    }
    auto n1 = masshist->GetEntries();
    if(outFormat == "rawhisto"){
        saveRawHisto(masshist.GetPtr(), outFile);
    } else if(outFormat == "histo"){
        saveHisto(masshist.GetPtr(), outFile);
    }
}

rdfAnalysis::Report w3piExample2022::run(const std::string &format,
                                         const std::vector<std::string> &infiles,
                                         const std::string &outformat,
                                         const std::string &outfile) const {
    auto tstart = std::chrono::steady_clock::now();
    //increase verbosity to see how long this is taking
    auto verbosity = ROOT::Experimental::RLogScopedVerbosity(
        ROOT::Detail::RDF::RDFLogChannel(),
        verbose_ ? ROOT::Experimental::ELogLevel::kInfo : ROOT::Experimental::ELogLevel::kWarning);
    // and suppress RNTuple verbosity
    auto rntVerbosity =
        ROOT::Experimental::RLogScopedVerbosity(ROOT::Experimental::NTupleLog(), ROOT::Experimental::ELogLevel::kError);

    unsigned long int ntot, npre, npass;
    if (format.find("rntuple") == 0) {
        assert(infiles.size() == 1);
        ROOT::RDataFrame d = ROOT::RDF::Experimental::FromRNTuple("Events", infiles.front());
        //d.Describe().Print();
        analyze(d, format, ntot, npre, npass, outformat, outfile);
    } else {
        ROOT::RDataFrame d("Events", infiles);
        //d.Describe().Print();
        analyze(d, format, ntot, npre, npass, outformat, outfile);
    }

    double dt = (std::chrono::duration<double>(std::chrono::steady_clock::now() - tstart)).count();
    auto ret = makeReport(dt, ntot, infiles, outfile);
    printf("Run on %d files (%s), %lu events, preselected %lu events (%.4f), selected %lu events (%.6f).\n",
            int(infiles.size()),
            infiles.front().c_str(),
            ntot,
            npre,
            npre / float(ntot),
            npass,
            npass / float(ntot));

    return ret;
}

