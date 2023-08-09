#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include <ROOT/RLogger.hxx>
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLegend.h"
#include "Math/Vector4D.h"
#include <TStopwatch.h>

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
#include <TH1.h>

template <typename T> using Vec = ROOT::RVec<T>; 


class TripletMaker{
    //class to make candidate triplets filtering on pt and invariant mass
    public:
        // constructor -> fix the parameters of mass and pts
        TripletMaker(float minMass=60, float maxMass=100, float hpt=0, float ipt=0, float lpt=0, bool electron=true, bool invmass=true, bool makeiso=false, bool choose_best=true, std::string PiIso="All", float drMin=0.01, float drMax=0.25, float MaxIso=0.45) :
            minMass_(minMass), maxMass_(maxMass), hpt_(hpt), ipt_(ipt), lpt_(lpt), electron_(electron), make_iso_(makeiso), invmass_(invmass), drMin_(drMin), drMax_(drMax), MaxIso_(MaxIso), choose_best_(choose_best), PiIso_(PiIso){}

        //function making triplets filtering on pdg_id, loose pt, invariant mass,
        Vec<Vec<std::size_t>> operator()(Vec<short int> & pdg,Vec<float> & pt, Vec<float> & eta, Vec<float> & phi, Vec<float> & mass, Vec<int> & charge) const {
            
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


void saveplot(float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best, std::string PiIso="All"){
// float saveplot(float hpt, float ipt, float lpt, bool el, bool m, bool iso, bool best){
    // return a vector containing N passed and N matched

    // ROOT::RDataFrame df("Events","capture_data/l1Nano_WTo3Pion_PU200_iso.root");
    // auto df1   = df.Define("Triplet_idxs", TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso, 0.01, 0.25, 0.45), {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});
    ROOT::RDataFrame df("Events","stream2.root");
    auto df1   = df.Define("Triplet_idxs", TripletMaker(60.,100.,hpt,ipt,lpt, el, m, iso, best, PiIso, 0.01, 0.25, 0.45), {"pid", "pt", "eta", "phi", "mass", "charge"}).Filter(notempty, {"Triplet_idxs"}).Define("Triplet_invmass", triplet_mass, {"Triplet_idxs", "pt", "eta", "phi", "mass"});

    // HISTOGRAMS //
    auto c1 = new TCanvas("c1", "c1", 800,600);
    auto hist = df1.Histo1D({"L1Triplet_mass", "InvMass ;mass (GeV);N_{Triplets}", 200, 0, 200}, "Triplet_invmass").GetValue();

    // hist.SetLineColor(kAzure+2);
    // hist.SetLineWidth(2);

    // std::ostringstream hist_title;
    // hist_title << std::boolalpha << "Invariant Mass   pt:(" << hpt << "," << ipt << "," << lpt << "), Mass: " << m << ", iso : "<< iso;
    // std::string histname_s = hist_title.str();
    // const char* histname = histname_s.c_str();
    // hist.SetTitle(histname);

    // //  LEGEND  //
    // auto legend = new TLegend(0.1,0.75,0.3,0.9); // (x1, y1, x2, y2)
    // legend->SetHeader("Invariant mass", "C"); // option "C" allows to center the header
    // legend->AddEntry(&hist, "Selected", "f"); 

    // //       DRAW       //
    hist.Draw();
    // legend->Draw();

    // FILE NAME SETTINGS
    c1 -> SaveAs("plots/online_scouting.pdf");
    //SNAPSHOT
    // df1.Snapshot("SelectedEvents", "snapshot.root", {"Triplet_invmass"});

}


///////////////////////////////////////////////////////////
                    // MAIN //
///////////////////////////////////////////////////////////

int main(){

    TStopwatch timer;
    timer.Start();
    saveplot(18,15,12, true,true,true,false, "All");
    timer.Stop();
    double tcpu = timer.CpuTime(), treal = timer.RealTime();
    std::cout << "timer: " << tcpu << ", real: " << treal << std::endl;
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