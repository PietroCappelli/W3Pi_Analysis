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
#include "translate.h"

template <typename T> using Vec = ROOT::RVec<T>; 

class TripletMaker{
    //class to make candidate triplets filtering on pt and invariant mass
    public:
        // constructor -> fix the parameters of mass and pts
        TripletMaker(float minMass=60, float maxMass=100, float hpt=0, float ipt=0, float lpt=0, bool electron=true, bool invmass=true, bool makeiso=false, std::string PiIso="All", float drMin=0.01, float drMax=0.25, float MaxIso=0.45) :
            minMass_(minMass), maxMass_(maxMass), hpt_(hpt), ipt_(ipt), lpt_(lpt), electron_(electron), make_iso_(makeiso), invmass_(invmass), drMin_(drMin), drMax_(drMax), MaxIso_(MaxIso), PiIso_(PiIso){}

        //function making triplets filtering on pdg_id, loose pt, invariant mass,
        Vec<Vec<std::size_t>> operator()(Vec<short int> & pdg,Vec<float> & pt, Vec<float> & eta, Vec<float> & phi,Vec<float> & mass, Vec<int> & charge) const {
            
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
            //select only one triplet
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
            
    private:
        float minMass_,  maxMass_,  hpt_,  ipt_,  lpt_, drMin_, drMax_, MaxIso_;
        bool electron_, make_iso_, invmass_;
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
        ROOT::Math::PtEtaPhiMVector p1(pts[t[0]],etas[t[0]],phis[t[0]], masses[t[0]]);
        ROOT::Math::PtEtaPhiMVector p2(pts[t[1]],etas[t[1]],phis[t[1]], masses[t[1]]);
        ROOT::Math::PtEtaPhiMVector p3(pts[t[2]],etas[t[2]],phis[t[2]], masses[t[2]]);
        double mass = (p1 + p2 + p3).M();
        massvec.push_back(mass);
    }
    return massvec;
}

bool notempty(Vec<Vec<std::size_t>> index) { //used to check if any triplets passed in an event
    return !index.empty();
}

Vec<float> Return_triplet(Vec<float> &feat, Vec<Vec<size_t>> indices_col){
    ROOT::VecOps::RVec<float> triplets;
    for (size_t i = 0; i < indices_col.size(); ++i) {
        ROOT::VecOps::RVec<int> indices = indices_col[i];
        for (int idx : indices_col[i]) {
            triplets.push_back(feat[idx]);
        }
    }
    return triplets;
}

Vec<float> give_mass_vec(Vec<short> pid){
    Vec<float> mass_vec;
    for (short value : pid) {
        mass_vec.push_back(give_mass(value));
    }
    // ROOT::VecOps::RVec<float> mass_vec = ROOT::VecOps::Map([](int x) { return give_mass(x); }, pid);
    return mass_vec;
}
Vec<int> give_charge_vec(Vec<short> pid){
    Vec<int> charge_vec;
    for (short value : pid) {
        charge_vec.push_back(sign(value));
    }
    // ROOT::VecOps::RVec<float> mass_vec = ROOT::VecOps::Map([](int x) { return sign(x); }, pid);
    return charge_vec;
}

///////////////////////////////////////////////////////////
                    // MAIN //
///////////////////////////////////////////////////////////

int main(int argc, char **argv){
    if (argc <= 1) {
        std::cout << "Usage: inputFile.root (format)" << std::endl;
	return 1;
    }
    // auto verbosity = ROOT::Experimental::RLogScopedVerbosity(ROOT::Detail::RDF::RDFLogChannel(), ROOT::Experimental::ELogLevel::kInfo);
    std::string c_pt, c_eta, c_phi, c_pdgId;
    bool isRNtuple = (std::string(argv[2]).find("rntuple")==0);
    if(isRNtuple){
        c_pt  = "Puppi.pt";
        c_eta = "Puppi.eta";
        c_phi = "Puppi.phi";
        c_pdgId = "Puppi.pdgId";
    }
    else{
        c_pt  = "pt";
        c_eta = "eta";
        c_phi = "phi";
        c_pdgId = "pid";
    }

    TStopwatch timer;
    timer.Start();

    // ROOT::RDataFrame df0 = isRNtuple ? ROOT::RDF::Experimental::FromRNTuple("Events", argv[1]) : ROOT::RDataFrame("Events", argv[1]);
    ROOT::RDataFrame df0 = ROOT::RDataFrame("Events", argv[1]);
    df0.Describe().Print();
    auto df = df0.Define("mass", give_mass_vec, {c_pdgId}).Define("charge", give_charge_vec, {c_pdgId});
    auto df1 = df.Define("Triplet_idxs", TripletMaker(60.,100.,18,15,12, true,true,true, "All", 0.01, 0.25, 0.45), {c_pdgId, c_pt, c_eta, c_phi, "mass", "charge"})
	.Filter(notempty,{"Triplet_idxs"})
	.Define("Triplet_invmass", triplet_mass, {"Triplet_idxs",c_pt, c_eta, c_phi, "mass"});
    //Define is lazy!
    auto hist = df1.Histo1D({"L1Triplet_mass", "InvMass ;mass (GeV);N_{Triplets}", 200, 0, 200}, "Triplet_invmass").GetValue(); 
    unsigned int ntot = *df.Count();
    unsigned int npass = hist.GetEntries();
    timer.Stop();

    double treal = timer.RealTime();
    std::cout << "initial: " << ntot << std::endl;
    std::cout << "Ratio passed events: " << (float)npass /*/ (float)ntot*/ << std::endl;
    std::cout << "timer(tot): " << ", real: " << treal << std::endl;
    return 0;
}