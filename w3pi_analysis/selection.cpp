#include <vector>
#include <cstdlib>
#include <cstdio>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>
#include <stdlib.h>
#include <math.h>
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include <ROOT/RLogger.hxx>
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "Math/Vector4D.h"

template <typename T> using Vec = ROOT::RVec<T>; 


//          Combine function        //

template <typename T> using Vec = ROOT::RVec<T>; 
auto Combine_func(Vec<std::size_t> high, 
                  Vec<std::size_t> inter, 
                  Vec<std::size_t> low,
                  Vec<Float_t> pt){
    Vec<Vec<size_t>> triplets;
    
    auto c1 = ROOT::VecOps::Combinations(high, inter);
    auto c2 = ROOT::VecOps::Combinations(c1[0].size(),low.size());

    for (int i=0; i<c2[0].size(); i++){
        Vec<std::size_t> tr{high[c1[0][c2[0][i]]], inter[c1[1][c2[0][i]]], low[c2[1][i]] }; //temporary array for the triplet
        if (tr[0]!=tr[1] and tr[1]!=tr[2] and tr[0]!=tr[2]){ //check they are not the same pion
            auto pt_tr = ROOT::VecOps::Take(pt, tr);
            if(pt_tr[1]<pt_tr[0] || ( pt_tr[1]==pt_tr[0] && tr[1]>tr[0] )){
                if(pt_tr[2]<pt_tr[1] || ( pt_tr[2]==pt_tr[1] && tr[2]>tr[1] )){
                    triplets.push_back(tr);
                    
                }
            }            
        } 
    }
    return triplets;
}

//          Delta R function        //

bool DR_test(Vec<Float_t> eta,
             Vec<Float_t> phi){
    Vec<Vec<std::size_t>> idx = ROOT::VecOps::Combinations(eta, 2);
    ROOT::RVec<float> deltar_vec;
    for (int k = 0; k<3; k++){
           auto dr = ROOT::VecOps::DeltaR(eta[idx[0][k]], eta[idx[1][k]], phi[idx[0][k]], phi[idx[1][k]]);
           deltar_vec.push_back(ROOT::VecOps::DeltaR(eta[idx[0][k]], eta[idx[1][k]], phi[idx[0][k]], phi[idx[1][k]]));
       }
    return ROOT::VecOps::All(ROOT::VecOps::Map(deltar_vec, [](float x){return (x>0.5); }));
}

//          isolation function          //

auto isolation_function(Vec<Float_t> eta, //vector of all the particles features
                        Vec<Float_t> phi,
                        Vec<Float_t> pt,
                        Vec<std::size_t> idx){ //indeces of that triplet (t_idx[0] e.g {0,3,6})
    Vec<bool> iso_bool;
    for(int pion : idx){ //nel for generale si scorre su quel indice 0 che è l'indice della tripletta
        double pt_sum=0.;
        
        for(int l=0; l<pt.size();++l){ //ciclo sulle altre particelle e seleziono quelle che sono nel cono, per tali calcolo la ptsum
            auto dr_part = ROOT::VecOps::DeltaR(eta[pion], eta[l], phi[pion], phi[l]);
            if (dr_part >= 0.01 && dr_part <= 0.25) pt_sum += pt[l];
         }

        iso_bool.push_back(pt_sum/pt[pion] <= 0.45); //containing bool=true if that pion is isolated
    }
    return ROOT::VecOps::All(iso_bool);
}


//          ISOLATION FUNCTION          //

auto triplet_index(Vec<int> pdg,Vec<float> pt, Vec<float> eta,Vec<float> phi, Vec<float> mass, Vec<int> charge){
    
    Vec<std::size_t> pdg_indeces;
    Vec<Vec<std::size_t>> triplets_index;
    Vec<float> triplets_invmass;
    Vec<float> triplets_ptsum;
    
    float hpt = 20.;
    float ipt = 15.;
    float lpt = 12.; 

    ROOT::RVec<std::size_t> high_pt;
    ROOT::RVec<std::size_t> int_pt;
    ROOT::RVec<std::size_t> low_pt;

    for(int i = 0; i < pdg.size(); ++i) { //make list of pions or electron
            if (abs(pdg[i]) == 211 or abs(pdg[i]) == 11) pdg_indeces.push_back(i);
    }

    for(std::size_t j : pdg_indeces){
        if(pt[j] > hpt) high_pt.push_back(j);
        if(pt[j] > ipt) int_pt.push_back(j);
        if(pt[j] > lpt) low_pt.push_back(j);
    }

    if(high_pt.size()>0 && int_pt.size()>1 && low_pt.size()>2){ //check if there is at least one possible triplet passing pt test
        Vec<Vec<std::size_t>> t_idx = Combine_func(high_pt, int_pt, low_pt, pt);
//         Vec<Vec<std::size_t>> t_idx = Combine_func(high_pt, int_pt, low_pt);

        for(int id=0; id < t_idx.size(); ++id){ //for loop over the triplets

//             auto charge_triplet = ROOT::VecOps::Take(charge, t_idx[id]);
//             if(abs(ROOT::VecOps::Sum(charge_triplet))==1){}
            if(std::abs(charge[t_idx[id][0]] * charge[t_idx[id][1]] * charge[t_idx[id][2]] ) == 1){ //inizio charge test
                auto pt_triplet   = ROOT::VecOps::Take(pt, t_idx[id]);
                auto eta_triplet  = ROOT::VecOps::Take(eta, t_idx[id]);
                auto phi_triplet  = ROOT::VecOps::Take(phi, t_idx[id]);
                auto mass_triplet = ROOT::VecOps::Take(mass, t_idx[id]);

//                 cout << "phi triplet" << phi_triplet << endl;

                auto inv_mass = ROOT::VecOps::InvariantMass(pt_triplet, eta_triplet, phi_triplet, mass_triplet);
                
                if(inv_mass>=60. && inv_mass<=100.){ //test invariant mass of the triplet
                    if(DR_test(eta_triplet, phi_triplet)){ //test delta R of the triplet

                        bool is_iso = isolation_function(eta, phi, pt,
                                                           t_idx[id]); //is true if all the pions are isolated

                        if(is_iso){
                            triplets_index.push_back(t_idx[id]);
                            triplets_invmass.push_back(inv_mass);
                            triplets_ptsum.push_back(ROOT::VecOps::Sum(pt_triplet));
                        } 
                    }
                }                 
            }//fine charge test
        }
    }
//     cout << triplets_index << endl;
    Vec<Vec<std::size_t>> best_triplet;
    if(triplets_index.size() > 1){//check if there is more than one triplet per event
        
        Vec<double> invmass_pt;
        int is_best;
        for(int k=0; k<triplets_index.size(); ++k){
            double m_dot_p = triplets_invmass[k] * triplets_ptsum[k];
            invmass_pt.push_back(m_dot_p);
            if(m_dot_p > invmass_pt[k-1]) {
//                 cout << m_dot_p << " inv mass > " << invmass_pt[k-1] << endl;
                is_best = k;
//                 cout << "score!" << endl;
//                 cout << "is best" <<  << endl;
            } 
        }
        best_triplet = {triplets_index[is_best]};
//         best_triplet = {triplets_index[0]};
        
        return best_triplet; //return only one triplet
    }
    
    else{
        return triplets_index;  
    } 
    
}

bool notempty(Vec<Vec<std::size_t>> index) { //used to check if any triplets passed in an event
    return !index.empty();
}

auto tripletmass(Vec<Vec<std::size_t>> triplets, Vec<float> pts, Vec<float> etas, Vec<float> phis, Vec<float> masses) {
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

int main(){

    const clock_t begin_time = std::clock(); //start counting

    auto file_path = "l1Nano_WTo3Pion_PU200_iso.root";
    auto tree_name = "Events";

    ROOT::RDataFrame df(tree_name,file_path);

    auto df_triplet = df.Define("Triplet_Index", triplet_index, {"L1Puppi_pdgId", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass", "L1Puppi_charge"})
            .Filter(notempty,{"Triplet_Index"})
            .Define("Triplet_invmass",tripletmass,{"Triplet_Index","L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_mass"});

    // auto index = df_t.Take<ROOT::VecOps::RVec<ROOT::VecOps::RVec<unsigned long> >>("Triplet_Index").GetValue();
    // std::cout << index[0] << std::endl;

    std::cout << float( std::clock() - begin_time) / CLOCKS_PER_SEC * 1e-3  << " s"<< std::endl;

    return 0;
}