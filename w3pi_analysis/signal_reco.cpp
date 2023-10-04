#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include <ROOT/RLogger.hxx>
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
//cpp
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>
#include <stdlib.h>
#include <math.h>
#include <TH1.h>

template <typename T> using Vec = ROOT::RVec<T>; 

auto RecoTriplet(Vec<float> gen_pt, Vec<float> gen_eta, Vec<float> gen_phi, Vec<int> gen_charge,
                 Vec<float> puppi_pt, Vec<float> puppi_eta, Vec<float> puppi_phi, Vec<int> puppi_charge, Vec<int> puppi_pdg){
    Vec<int> puppi_pdg_idx;
    Vec<size_t> PG_idx;
    Vec<size_t> G_idx;
    //          PGD             //
    for(int i = 0; i < puppi_pdg.size(); ++i) { //make list of pions or electron
            if (abs(puppi_pdg[i]) == 211 || abs(puppi_pdg[i]) == 11) puppi_pdg_idx.push_back(i);
    }
    //          DELTA R             //
    for(std::size_t i=0; i<3; i++){
        Vec<float> dr_vec;
        for(size_t j : puppi_pdg_idx){
            float DR = ROOT::VecOps::DeltaR(gen_eta[i], puppi_eta[j], gen_phi[i], puppi_phi[j]);
            dr_vec.push_back(DR);
        }
        auto min_it = std::min_element(dr_vec.begin(), dr_vec.end());  // iteratore all'elemento minimo
        int min_idx = std::distance(dr_vec.begin(), min_it);      // indice dell'elemento minimo
        if(dr_vec[min_idx]<0.1) {
            PG_idx.push_back(puppi_pdg_idx[min_idx]);
            G_idx.push_back(i);
        }
    }

    //          PT             //
    for(std::size_t k=0; k<PG_idx.size(); k++){
        if(puppi_pt[PG_idx[k]] <= gen_pt[G_idx[k]]/2 || puppi_pt[PG_idx[k]] >= 2*gen_pt[G_idx[k]]){
            PG_idx.erase(std::remove(PG_idx.begin(), PG_idx.end(), PG_idx[k]), PG_idx.end());
            G_idx.erase(std::remove(G_idx.begin(), G_idx.end(), G_idx[k]), G_idx.end());
        }
    }
    //          CHARGE          //

    // for(std::size_t l=0; l<PG_idx.size(); l++){
    //         if(gen_charge[G_idx[l]] != puppi_charge[PG_idx[l]]){
    //             G_idx.erase(std::remove(G_idx.begin(), G_idx.end(), G_idx[l]), G_idx.end());
    //             PG_idx.erase(std::remove(PG_idx.begin(), PG_idx.end(), PG_idx[l]), PG_idx.end());
    //         }
    // }
    return PG_idx;
}


auto RecoTriplet_gen(Vec<float> gen_pt, Vec<float> gen_eta, Vec<float> gen_phi, Vec<int> gen_charge,
                 Vec<float> puppi_pt, Vec<float> puppi_eta, Vec<float> puppi_phi, Vec<int> puppi_charge, Vec<int> puppi_pdg){
    Vec<int> puppi_pdg_idx;
    Vec<size_t> PG_idx;
    Vec<size_t> G_idx;
    //          PGD             //
    for(int i = 0; i < puppi_pdg.size(); ++i) { //make list of pions or electron
            if (abs(puppi_pdg[i]) == 211 || abs(puppi_pdg[i]) == 11) puppi_pdg_idx.push_back(i);
    }
    //          DELTA R             //
    for(std::size_t i=0; i<3; i++){
        Vec<float> dr_vec;
        for(size_t j : puppi_pdg_idx){
            float DR = ROOT::VecOps::DeltaR(gen_eta[i], puppi_eta[j], gen_phi[i], puppi_phi[j]);
            dr_vec.push_back(DR);
        }
        auto min_it = std::min_element(dr_vec.begin(), dr_vec.end());  // iteratore all'elemento minimo
        int min_idx = std::distance(dr_vec.begin(), min_it);      // indice dell'elemento minimo
        if(dr_vec[min_idx]<0.1) {
            PG_idx.push_back(puppi_pdg_idx[min_idx]);
            G_idx.push_back(i);
        }
    }

    //          PT             //
    for(std::size_t k=0; k<PG_idx.size(); k++){
        if(puppi_pt[PG_idx[k]] <= gen_pt[G_idx[k]]/2 || puppi_pt[PG_idx[k]] >= 2*gen_pt[G_idx[k]]){
            PG_idx.erase(std::remove(PG_idx.begin(), PG_idx.end(), PG_idx[k]), PG_idx.end());
            G_idx.erase(std::remove(G_idx.begin(), G_idx.end(), G_idx[k]), G_idx.end());
        }
    }
    //          CHARGE          //

    // for(std::size_t l=0; l<PG_idx.size(); l++){
    //         if(gen_charge[G_idx[l]] != puppi_charge[PG_idx[l]]){
    //             G_idx.erase(std::remove(G_idx.begin(), G_idx.end(), G_idx[l]), G_idx.end());
    //             PG_idx.erase(std::remove(PG_idx.begin(), PG_idx.end(), PG_idx[l]), PG_idx.end());
    //         }
    // }
    return G_idx;
}

auto Res_function(Vec<float> reco_pt, Vec<float> gen_pt,Vec<int> reco_charge, Vec<int> gen_charge){
    Vec<float> resolution;
    for(int i=0; i<gen_pt.size();i++){
        resolution.push_back((gen_charge[i]/gen_pt[i] - reco_charge[i]/reco_pt[i]) * gen_pt[i]/gen_charge[i]);
    }
    return resolution;
}

bool notempty(Vec<std::size_t> index) { //used to check if any triplets passed in an event
    return !index.empty();
}


int main(){
    //Import data
    auto file_path = "l1Nano_WTo3Pion_PU200_iso.root";
    auto tree_name = "Events";

    ROOT::RDataFrame df(tree_name,file_path);
    // df.Describe();

    auto df_reco = df.Define("RecoPuppi_idx", RecoTriplet, {"GenPi_pt", "GenPi_eta", "GenPi_phi", "GenPi_charge", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_charge", "L1Puppi_pdgId"})
                    .Define("RecoGen_idx", RecoTriplet_gen, {"GenPi_pt", "GenPi_eta", "GenPi_phi", "GenPi_charge", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi", "L1Puppi_charge", "L1Puppi_pdgId"})
                    .Filter(notempty, {"RecoPuppi_idx"});

    auto rec = df_reco.Take<ROOT::VecOps::RVec<unsigned long>>("RecoPuppi_idx").GetValue()[4];
    std::cout << rec << std::endl;
    std::cout << "rec count: " << *df_reco.Count() << std::endl;
    std::cout << "tot count: " <<*df.Count() << std::endl;

    auto df_reco_pt = df_reco.Define("Reco_pt", "Take(L1Puppi_pt, RecoPuppi_idx)")
                         .Define("Gen_pt", "Take(GenPi_pt, RecoGen_idx)")
                         .Define("Reco_eta", "Take(L1Puppi_eta, RecoPuppi_idx)")
                         .Define("Gen_eta", "Take(GenPi_eta, RecoGen_idx)")
                         .Define("Reco_phi", "Take(L1Puppi_phi, RecoPuppi_idx)")
                         .Define("Gen_phi", "Take(GenPi_phi, RecoGen_idx)")
                         .Define("Reco_mass", "Take(L1Puppi_mass, RecoPuppi_idx)")
                         .Define("Gen_mass", "Take(GenPi_mass, RecoGen_idx)")
                         .Define("Reco_charge", "Take(L1Puppi_charge, RecoPuppi_idx)")
                         .Define("Gen_charge", "Take(GenPi_charge, RecoGen_idx)")
                         .Define("pt_resolution", Res_function, {"Reco_pt", "Gen_pt", "Reco_charge", "Gen_charge"});

    return 0;
}