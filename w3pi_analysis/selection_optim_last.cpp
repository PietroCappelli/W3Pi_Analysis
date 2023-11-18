#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include <ROOT/RLogger.hxx>
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLegend.h"
#include "Math/Vector4D.h"

//cpp
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>
#include <stdlib.h>
#include <math.h>
#include <TStopwatch.h>
#include <TH1.h>

template <typename T> using Vec = ROOT::RVec<T>; 

class TripletMaker{
    //class to make candidate triplets filtering on pt and invariant mass
    public:
        // constructor -> fix the parameters of mass and pts
        TripletMaker(float minMass=60, float maxMass=100, float hpt=0, float ipt=0, float lpt=0, bool electron=true, bool invmass=true, bool makeiso=false, bool choose_best=true, std::string PiIso="All", float drMin=0.01, float drMax=0.25, float MaxIso=0.5) :
            minMass_(minMass), maxMass_(maxMass), hpt_(hpt), ipt_(ipt), lpt_(lpt), electron_(electron), make_iso_(makeiso), invmass_(invmass), drMin_(drMin), drMax_(drMax), MaxIso_(MaxIso), choose_best_(choose_best), PiIso_(PiIso){}

        //function making triplets filtering on pdg_id, loose pt, invariant mass,
        Vec<Vec<std::size_t>> operator()(Vec<int> & pdg,Vec<float> & pt, Vec<float> & eta, Vec<float> & phi, Vec<float> & mass, Vec<int> & charge) const {
            
            Vec<std::size_t> pdg_indeces;
            Vec<Vec<std::size_t>> triplets_index;
            Vec<float> triplets_invmass;
            Vec<float> triplets_ptsum;

            Vec<std::size_t> high_pt;
            Vec<std::size_t> int_pt;
            Vec<std::size_t> low_pt;

            for(int i = 0; i < pdg.size(); ++i) {
                if(electron_){ //accept electron
                    if (abs(pdg[i]) == 211 or abs(pdg[i]) == 11) pdg_indeces.push_back(i);
                } 
                else { //take only pion
                    if (abs(pdg[i]) == 211) pdg_indeces.push_back(i);
                }
            }
            // pT lower bound
            for(std::size_t j : pdg_indeces){
                if(pt[j] > hpt_) high_pt.push_back(j);
                if(pt[j] > ipt_) int_pt.push_back(j);
                if(pt[j] > lpt_) low_pt.push_back(j);
            }
            
            if(high_pt.size()>0 && int_pt.size()>1 && low_pt.size()>2){ //check if there is at least one possible triplet passing pt test
                Vec<Vec<std::size_t>> t_idx = Combine_func(high_pt, int_pt, low_pt, pt);
                // std::cout << "Running triplets with " << high_pt.size() << ", " << int_pt.size() << ", " << low_pt.size() << std::endl;
                
                for(int id=0; id < t_idx.size(); ++id){ //for loop over the triplets
                    if(std::abs(charge[t_idx[id][0]] * charge[t_idx[id][1]] * charge[t_idx[id][2]] ) == 1){                     
                        auto pt_triplet   = ROOT::VecOps::Take(pt, t_idx[id]);
                        auto eta_triplet  = ROOT::VecOps::Take(eta, t_idx[id]);
                        auto phi_triplet  = ROOT::VecOps::Take(phi, t_idx[id]);
                        auto mass_triplet = ROOT::VecOps::Take(mass, t_idx[id]);
                        auto inv_mass = ROOT::VecOps::InvariantMass(pt_triplet, eta_triplet, phi_triplet, mass_triplet);
                        if(invmass_){ //inv mass filter
                            if(inv_mass>=minMass_ && inv_mass<=maxMass_){ //test invariant mass of the triplet
                                if(DR_test(eta_triplet, phi_triplet)){ //test delta R of the triplet
                                    //include isolation or not
                                    if(make_iso_){
                                        bool is_iso = Isolation(pt, eta, phi, t_idx[id], drMin_, drMax_, MaxIso_,PiIso_);
                                        if(is_iso){
                                            triplets_index.push_back(t_idx[id]);
                                            triplets_invmass.push_back(inv_mass);
                                            triplets_ptsum.push_back(ROOT::VecOps::Sum(pt_triplet));                                            
                                        }
                                    }
                                    else{
                                        triplets_index.push_back(t_idx[id]);
                                        triplets_invmass.push_back(inv_mass);
                                        triplets_ptsum.push_back(ROOT::VecOps::Sum(pt_triplet));
                                    } 
                                }
                            }
                        }
                        else{ //NO mass filter
                            if(DR_test(eta_triplet, phi_triplet)){ //test delta R of the triplet
                                //include isolation or not
                                if(make_iso_){
                                    bool is_iso = Isolation(pt, eta, phi, t_idx[id], drMin_, drMax_, MaxIso_,PiIso_);
                                    if(is_iso){
                                        triplets_index.push_back(t_idx[id]);
                                        triplets_invmass.push_back(inv_mass);
                                        triplets_ptsum.push_back(ROOT::VecOps::Sum(pt_triplet));
                                    } 
                                }
                                else{
                                    triplets_index.push_back(t_idx[id]);
                                    triplets_invmass.push_back(inv_mass);
                                    triplets_ptsum.push_back(ROOT::VecOps::Sum(pt_triplet));
                                }
                            }
                        }
                    }
                }
            }
            if(choose_best_){ //select only one triplet
                Vec<Vec<std::size_t>> best_triplet;
                if(triplets_index.size() > 1){//check if there is more than one triplet per event
                    Vec<double> invmass_pt;
                    int is_best;
                    for(int k=0; k<triplets_index.size(); ++k){
                        double m_dot_p = triplets_invmass[k] * triplets_ptsum[k];
                        invmass_pt.push_back(m_dot_p);
                        if(m_dot_p > invmass_pt[k-1]) {
                            is_best = k;
                        } 
                    }
                    best_triplet = {triplets_index[is_best]};
                    return best_triplet; //return only one triplet
                }
                else return triplets_index;
            }
            else return triplets_index;
        }
            
    private:
        float minMass_,  maxMass_,  hpt_,  ipt_,  lpt_, drMin_, drMax_, MaxIso_;
        bool electron_, make_iso_, invmass_, choose_best_;
        std::string PiIso_;

        // filter on dr
        bool DR_test(Vec<Float_t> eta,Vec<Float_t> phi) const {
            Vec<Vec<std::size_t>> idx = ROOT::VecOps::Combinations(eta, 2);
            Vec<float> deltar_vec;
            for (int k = 0; k<3; ++k){
                   auto dr = ROOT::VecOps::DeltaR(eta[idx[0][k]], eta[idx[1][k]], phi[idx[0][k]], phi[idx[1][k]]);
                   deltar_vec.push_back(ROOT::VecOps::DeltaR(eta[idx[0][k]], eta[idx[1][k]], phi[idx[0][k]], phi[idx[1][k]]));
               }
            return ROOT::VecOps::All(ROOT::VecOps::Map(deltar_vec, [](float x){return (x > 0.5); }));
        }
                
        // function to make all the combinations between pions
        Vec<Vec<std::size_t>> Combine_func(Vec<std::size_t> high, Vec<std::size_t> inter, Vec<std::size_t> low, Vec<Float_t> pt) const{
            Vec<Vec<size_t>> triplets;
            auto c1 = ROOT::VecOps::Combinations(high, inter);
            auto c2 = ROOT::VecOps::Combinations(c1[0].size(),low.size());
            for (int i=0; i<c2[0].size(); i++){
                Vec<std::size_t> tr{high[c1[0][c2[0][i]]], inter[c1[1][c2[0][i]]], low[c2[1][i]] }; //temporary array for the triplet
                if (tr[0]!=tr[1] and tr[1]!=tr[2] and tr[0]!=tr[2]){ //check they are not the same pion
                    if(pt[tr[1]]<pt[tr[0]] || ( pt[tr[1]]==pt[tr[0]] && tr[1]>tr[0] )){
                        if(pt[tr[2]]<pt[tr[1]] || ( pt[tr[2]]==pt[tr[1]] && tr[2]>tr[1] )){
                            triplets.push_back(tr);
                        }
                    }            
                } 
            }
            return triplets;
        }

        bool Isolation(Vec<float> pt, Vec<float> eta, Vec<float> phi, Vec<std::size_t> idx,
                        float drMin, float drMax, float MaxIso, std::string iso ="All") const {
            Vec<float> iso_bool;
            for(int p : idx){
                double pt_sum=0.;
                for(int l=0; l<pt.size();++l){
                    auto dr_part = ROOT::VecOps::DeltaR(eta[p], eta[l], phi[p], phi[l]);
                    if (dr_part >= drMin && dr_part <= drMax) pt_sum += pt[l];
                }
                iso_bool.push_back(pt_sum/pt[p] <= MaxIso); //containing bool=true if that pion is isolated
            }
            if(iso =="All") return ROOT::VecOps::All(iso_bool);
            else if(iso =="12") {
                if(iso_bool[0]==true  && iso_bool[1]==true) return true;
                }
            else if(iso =="3" ) {
                if(iso_bool[2]==true)  return true;
                }
            else std::cerr << "input error" << std::endl;
        }
};

Vec<float> triplet_mass(Vec<Vec<std::size_t>> triplets, Vec<float> pts, Vec<float> etas, Vec<float> phis, Vec<float> masses) {
    Vec<float> massvec;
    for (Vec<std::size_t> t : triplets) {
        ROOT::Math::PtEtaPhiMVector p1(pts[t[0]],etas[t[0]],phis[t[0]],masses[t[0]]);
        ROOT::Math::PtEtaPhiMVector p2(pts[t[1]],etas[t[1]],phis[t[1]],masses[t[1]]);
        ROOT::Math::PtEtaPhiMVector p3(pts[t[2]],etas[t[2]],phis[t[2]],masses[t[2]]);
        double mass = (p1 + p2 + p3).M();
        massvec.push_back(mass);
    }
    return massvec;
}

bool notempty(Vec<Vec<std::size_t>> index) { //used to check if any triplets passed in an event
    return !index.empty();
}

bool matchedtriplet(Vec<Vec<std::size_t>> triplet, Vec<Int_t> match) { //checks if a Puppi triplet is matched with truth
    bool flag = true;
   for (std::size_t i=0 ; i < 3; ++i) {
        if (match[triplet[0][i]] == -1) flag = false;
    }
    return flag; 
}


Vec<float> saveplot(float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best, std::string PiIso="All"){
// float saveplot(float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best){
    // return a vector containing N passed and N matched

    ROOT::RDataFrame df("Events","l1Nano_WTo3Pion_PU200_iso.root");
    ROOT::RDataFrame dfBG("Events","l1Nano_SingleNeutrino_PU200_iso.root");
    auto df1   = df.Define("Triplet_idxs",   TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    auto dfBG1 = dfBG.Define("Triplet_idxs", TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    auto df_match = df1.Filter(matchedtriplet,{"Triplet_idxs","L1Puppi_GenPiIdx"});
    unsigned int Ntot   = *df.Count();
    unsigned int Npass  = *df1.Count();
    unsigned int Nmatch = *df_match.Count();

    unsigned int Ntot_BG  = *dfBG.Count();
    unsigned int Npass_BG = *dfBG1.Count();

    Vec<float> res;
    res.push_back(Npass);
    res.push_back(Nmatch);

    std::cout << "Filters: Take electrons : " << el << ", Iso: " << iso << ", mass filter: " << m << ", pt lower bounds: high " << hpt << ", inter. " << ipt << ", low " << lpt << std::endl;
    std::cout << "Ntot = " << Ntot << ",\t Nselected(S+N) = " << Npass << "\nNmatched (Signal ev) = " << Nmatch << ",\tNunmatched (Noise ev) = " << (Npass - Nmatch) << std::endl;
    std::cout << "Efficiency(pass/tot) = " << (float)Npass / (float)Ntot << std::endl;
    std::cout << "Purity(match/pass) = " << (float)Nmatch / (float)Npass << std::endl;
    std::cout << "Signal(match/sqrt(pass)) = " << (float)Nmatch / sqrt(Npass) << std::endl;
    std::cout << "\nBACKGROUND: " << std::endl;
    std::cout << "Ntot = " << Ntot_BG << ",\t Nselected = " << Npass_BG << std::endl;
    std::cout << "Final estimation: " << (float)Nmatch / sqrt(Npass + Npass_BG) << "\n" << std::endl;

    // HISTOGRAMS //
    auto c1 = new TCanvas("c1", "c1", 800,600);
    auto hist = df1.Histo1D({"L1Triplet_mass", "InvMass ;mass (GeV);N_{Triplets}", 120, 50, 110}, "Triplet_invmass").GetValue();
    auto hist_match = df_match.Histo1D({"masshist", "Matched", 120, 50, 110},"Triplet_invmass").GetValue();

    hist.SetLineColor(kAzure+2);
    hist.SetLineWidth(2);
    hist_match.SetLineColor(kOrange+7);
    hist_match.SetLineWidth(2);

    std::ostringstream hist_title;
    hist_title << std::boolalpha << "Invariant Mass   pt:(" << hpt << "," << ipt << "," << lpt << "), Mass: " << m << ", iso : "<< iso;
    std::string histname_s = hist_title.str();
    const char* histname = histname_s.c_str();
    hist.SetTitle(histname);

    // //  LEGEND  //
    auto legend = new TLegend(0.1,0.75,0.3,0.9); // (x1, y1, x2, y2)
    legend->SetHeader("Invariant mass", "C"); // option "C" allows to center the header
    legend->AddEntry(&hist, "Selected", "f"); 
    legend->AddEntry(&hist_match, "Matched", "f");

    // //       DRAW       //
    hist.Draw();
    hist_match.Draw("SAME");
    legend->Draw();

    // FILE NAME SETTINGS
    // std::ostringstream title;
    // title << "InvMass_h" << hpt << "_i" << ipt << "_l" << lpt << "_MassF" << m << "_iso"<< iso << "_best" << best << ".pdf";
    // std::string filename_s = title.str();
    // const char* filename = filename_s.c_str();
    // c1 -> SaveAs(("plots/" + filename_s).c_str());

    // SAVE HISTO FILE
    std::ostringstream title;
    title << "InvMass(" << hpt << "," << ipt << "," << lpt << ")_MassF(" << m << ")_iso("<< iso << ")_best" << best << ".root";
    std::string filename_s = title.str();
    const char* filename = filename_s.c_str();
    // c1 -> SaveAs(("histograms/" + filename_s).c_str());

    TFile* combineFile = new TFile(("histograms/" + filename_s).c_str(), "RECREATE");
    hist.Write("selected");
    hist_match.Write("matched");
    combineFile->Close();

    c1 -> SaveAs("histograms/figures/sel_vs_match.pdf");
    return res;
}

void SaveOnFile(const std::string& filename , float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best, std::string PiIso="All", float drMax=0.25, float MaxIso=0.45){

    std::ofstream outputFile;
    outputFile.open(filename, std::ios::app);
    std::cout << "Opening file " << filename << std::endl;

    ROOT::RDataFrame df("Events","l1Nano_WTo3Pion_PU200_iso.root");
    ROOT::RDataFrame dfBG("Events","l1Nano_SingleNeutrino_big_PU200.125X_v0.0.root");
    auto df1   = df.Define("Triplet_idxs",   TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso, 0.01, drMax, MaxIso), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    auto dfBG1 = dfBG.Define("Triplet_idxs", TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso, 0.01, drMax, MaxIso), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    auto df_match = df1.Filter(matchedtriplet,{"Triplet_idxs","L1Puppi_GenPiIdx"});
    unsigned int Ntot   = *df.Count();
    unsigned int Npass  = *df1.Count();
    unsigned int Nmatch = *df_match.Count();

    unsigned int Ntot_BG  = *dfBG.Count();
    unsigned int Npass_BG = *dfBG1.Count();

    if(outputFile.is_open()){
        outputFile << "Filters: Take electrons : " << el << ", Iso: " << iso<< ", "<< PiIso << ", mass filter: " << m << ", pt lower bounds: high " << hpt << ", inter. " << ipt << ", low "<< lpt  << ", drMax " << drMax << ", Iso_param " << MaxIso << std::endl;
        outputFile << "Efficiency(pass/tot) = " << (float)Npass  / (float)Ntot  << std::endl;
        outputFile << "Purity(match/pass)   = " << (float)Nmatch / (float)Npass << std::endl;
        outputFile << "SIGNAL: Nselected(S+N) = " << Npass << "\tNmatched (Signal ev) = " << Nmatch << std::endl;
        outputFile << "BACKGROUND:  Nselected = " << Npass_BG << "\n\n"<< std::endl;
        outputFile.close();
        std::cout << "File closed " << std::endl;
    } else{
        std::cerr << "Error in opening file" << filename << std::endl;
    }
    
}

void DrawHist(float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best, std::string PiIso="All"){
    
    ROOT::RDataFrame df("Events","l1Nano_WTo3Pion_PU200_iso.root");
    ROOT::RDataFrame dfBG("Events","l1Nano_SingleNeutrino_big_PU200.125X_v0.0.root");
    auto df1   = df.Define("Triplet_idxs",   TripletMaker(60.,100.,18,15,12, true, true, true, true, "All"), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    auto dfBG1 = dfBG.Define("Triplet_idxs", TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    auto df_match = df1.Filter(matchedtriplet,{"Triplet_idxs","L1Puppi_GenPiIdx"});

    std::cout << "ciao" << std::endl;

    float N_sig = *df.Count();
    float N_bkg = *dfBG.Count();
    float N = N_sig + N_bkg;
    auto c1 = new TCanvas("c1", "c1", 800,600);
    auto hist = df1.Histo1D({"L1Triplet_mass", "InvMass ;mass (GeV);N_{Triplets}", 100, 40, 120}, "Triplet_invmass").GetValue();
    // auto hist_bkg = dfBG1.Histo1D({"L1Triplet_mass", "InvMass ;mass (GeV);N_{Triplets}", 100, 40, 120}, "Triplet_invmass").GetValue();
    // double N_sig_exp = 582.3;
    // double N_bkg_exp = 1.6789e8;
    // double N_sig_exp = 436.3;
    // double N_bkg_exp = 1.045e7;

    // hist.SetLineColor(kAzure+2);
    // hist.SetLineWidth(2);
    // hist_bkg.SetLineColor(kOrange+7);
    // hist_bkg.SetLineWidth(2);

    // //   LEGEND  //
    // auto legend = new TLegend(0.75,0.75,0.9,0.9); // (x1, y1, x2, y2)
    // legend->SetHeader("Invariant mass", "C"); 
    // legend->AddEntry(&hist, "BKG+Sig*1000", "f"); 
    // legend->AddEntry(&hist_bkg, "BKG", "f");

    // hist.Scale(1000 * N_sig_exp/hist.Integral());
    // hist_bkg.Scale(N_bkg_exp/hist_bkg.Integral());

    // //       ADD        //
    // hist.Add(&hist_bkg);
    // //       DRAW       //
    // hist_bkg.Draw("HIST");
    // hist.Draw("SAME");
    // hist.SetStats(kFALSE);
    // hist_bkg.SetStats(kFALSE);
    // legend->Draw();

    // // FILE NAME SETTINGS
    // std::ostringstream title;
    // title << "InvMass_h" << hpt << "_i" << ipt << "_l" << lpt << "_MassF" << m << "_iso"<< iso << "_best" << best << ".pdf";
    // std::string filename_s = title.str();
    // const char* filename = filename_s.c_str();
    // c1 -> SaveAs(("plots/BKG+SIG_" + filename_s).c_str());
    std::cout << "end" << std::endl;

}


void saveplot2(float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best, std::string PiIso="All"){
// float saveplot(float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best){
    // return a vector containing N passed and N matched
    std::cout << "ciao\n";

    ROOT::RDataFrame df("Events","l1Nano_WTo3Pion_PU200_iso.root");
    auto df1   = df.Define("Triplet_idxs", TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso, 0.01, 0.25, 0.5), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"})
                    .Filter(notempty, {"Triplet_idxs"})
                    .Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    std::cout << "ciao\n";

    // HISTOGRAMS //
    auto c1 = new TCanvas("c1", "c1", 800,600);
    auto hist = df1.Histo1D({"L1Triplet_mass", "InvMass ;mass (GeV);N_{Triplets}", 200, 0, 200}, "Triplet_invmass").GetValue();

    // //       DRAW       //
    hist.Draw();
    // legend->Draw();

    // FILE NAME SETTINGS
    c1 -> SaveAs("plots/online_scouting.pdf");
    //SNAPSHOT
    // df1.Snapshot("SelectedEvents", "snapshot.root", {"Triplet_invmass"});
    // std::cout << "ciao\n";

    std::ostringstream title;
    title << "InvMass(" << hpt << "," << ipt << "," << lpt << ")_MassF()" << m << ")_iso("<< iso << ")_best" << best << ".root";
    std::string filename_s = title.str();
    const char* filename = filename_s.c_str();
    // c1 -> SaveAs(("histograms/" + filename_s).c_str());

    TFile* combineFile = new TFile(("histograms/" + filename_s).c_str(), "RECREATE");
    hist.Write("signal");
    combineFile->Close();

}


///////////////////////////////////////////////////////////
                    // MAIN //
///////////////////////////////////////////////////////////

int main(){

    // const clock_t begin_time = std::clock(); //start counting
    // std::string filename = "ptAll_newBKG.txt";
    std::string filename = "final.txt";

    saveplot(20,15,12, true,true,false,true, "All");
    // saveplot(15,12,4,  true,true,true,true, "All");

    // auto file_path = "l1Nano_WTo3Pion_PU200_iso.root";
    // auto tree_name = "Events";
    // ROOT::RDataFrame df(tree_name,file_path);

    // Vec<float> highpts  = {12,15,18,20,22};
    // Vec<float> interpts = {10,12,15,18,20};
    // Vec<float> lowpts   = {4,5,6,7,8,9,10};
    // Vec<float> isopar   = {0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6};
    // Vec<float> drs      = {0.1,0.15, 0.2, 0.225, 0.25, 0.275, 0.3, 0.325, 0.35, 0.375, 0.4};

    // Vec<Vec<unsigned int>> counts;
    // for(int i=0; i<lowpts.size();i++){
        // counts.push_back(saveplot(15,12,10, true,true,true,true, "All"));

    // // }
    // for(int i=0; i<lowpts.size();i++){,

    // test
    // SaveOnFile(filename,18,15,12, true,true,true,true, "All", 0.25, 0.4);
    // SaveOnFile(filename,18,15,2, true,true,true,true, "All", 0.25, 0.45);
    // SaveOnFile(filename,15,14,12, true,true,true,true, "All",0.25, 0.45);
    // SaveOnFile(filename,15,14,2, true,true,true,true, "All", 0.25, 0.45);

    // usage
    // SaveOnFile(filename,20,15,12, true,true,true,true, "All", 0.25, 0.45);
    // SaveOnFile(filename,20,15,2, true,true,true,true, "All", 0.25, 0.45);
    // SaveOnFile(filename,15,14,12, true,true,true,true, "All", 0.25, 0.45);
    // SaveOnFile(filename,15,14,2, true,true,true,true, "All", 0.25, 0.45);

    // //test 
    // SaveOnFile(filename,18,15,12, true,true,true,true, "All", 0.25, 0.45);
    // SaveOnFile(filename,18,15,12, true,true,true,true, "12", 0.25, 0.45);
    // SaveOnFile(filename,18,15,12, true,true,true,true, "3", 0.25, 0.45);
    // SaveOnFile(filename,18,15,12, true,true,false,true, "All", 0.25, 0.45);

    // //usage 
    // SaveOnFile(filename,20,15,12, true,true,true,true, "All", 0.25, 0.45);
    // SaveOnFile(filename,20,15,12, true,true,true,true, "12", 0.25, 0.45);
    // SaveOnFile(filename,20,15,12, true,true,true,true, "3", 0.25, 0.45);
    // SaveOnFile(filename,20,15,12, true,true,false,true, "All", 0.25, 0.45);



    // }
    // std::cout << float( std::clock() - begin_time) / CLOCKS_PER_SEC *1e-3 << " s" << std::endl;
    // TStopwatch timer;
    // timer.Start();
    // saveplot2(20,15,12, true,true,true,false, "All");
    // timer.Stop();
    // double tcpu = timer.CpuTime(), treal = timer.RealTime();
    // std::cout << "timer: " << tcpu << ", real: " << treal << std::endl;

    return 0;
}




    // df.Describe();
    // int event = 0;
    // auto tid_df   = df1.Take<ROOT::VecOps::RVec<ROOT::VecOps::RVec<unsigned long>>>("Triplet_idxs").GetValue();
    // auto tmass_df = df1.Take<ROOT::VecOps::RVec<float>>("Triplet_invmass").GetValue();
    // std::cout << "count: " << *df1.Count() << std::endl;
    // std::cout << tid_df[event] << std::endl;


    // auto hist = df1.Histo1D({"L1Triplet_mass", "InvMass;mass (GeV);N_{Triplets}", 200, 0, 200}, "Triplet_invmass");
    // auto c1 = new TCanvas("c1", "c1", 800,600);
    // hist -> Draw();
    // // c1 -> Draw();

    // std::ostringstream title;
    // title << "InvMass_h" << 15 << "_i" << 10 << "_l" <<"_NoMF_Noiso.pdf";
    // std::string filename = title.str();
    // c1 -> SaveAs("plots/mass_try.pdf");

        // outputFile << "Filters: Take electrons : " << el << ", Iso: " << iso<< ", "<< PiIso << ", mass filter: " << m << ", pt lower bounds: high " << hpt << ", inter. " << ipt << ", low " << lpt << std::endl;
        // outputFile << "Ntot = " << Ntot << ",\t Nselected(S+N) = " << Npass << "\nNmatched (Signal ev) = " << Nmatch << ",\tNunmatched (Noise ev) = " << (Npass - Nmatch) << std::endl;
        // outputFile << "Efficiency(pass/tot) = " << (float)Npass / (float)Ntot << std::endl;
        // outputFile << "Purity(match/pass) = " << (float)Nmatch / (float)Npass << ",\t\tPurity x Efficiency (match/tot) = " << (float)Nmatch/ (float)Ntot << std::endl;
        // outputFile << "Signal(match/sqrt(pass)) = " << (float)Nmatch / sqrt(Npass) << std::endl;
        // outputFile << "\nBACKGROUND: " << std::endl;
        // outputFile << "Ntot = " << Ntot_BG << ",\t Nselected = " << Npass_BG << std::endl;
        // outputFile << "Final estimation: " << (float)Nmatch / sqrt(Npass + Npass_BG) << "\n\n" << std::endl;