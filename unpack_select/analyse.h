#include "ROOT/RDataFrame.hxx"
#include "ROOT/RNTupleDS.hxx"
#include "ROOT/RVec.hxx"
#include <ROOT/RLogger.hxx>
#include "TFile.h"
#include "TH1D.h"
#include "Math/Vector4D.h"
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>
#include <stdlib.h>
#include <math.h>
#include <TStopwatch.h>

template <typename T> using Vec = ROOT::RVec<T>; 

float max_iso = 0.8;
float min_mass = 40;
float max_mass = 120;
float min_dr = 0.5;
float min_dr_iso = 0.01, max_dr_iso = 0.25;
float H_pt=15., I_pt = 12., L_pt=8.;

bool pt_cut(const Vec<float> &pt, const Vec<short> &pid){
    int high_pt=0, int_pt=0, low_pt=0;
    for (const float &pt_value : pt) {
        for (const short &pid_value : pid) {
            if (abs(pid_value) == 211 || abs(pid_value) == 11) {
                if (pt_value >= L_pt) {
                    low_pt++;
                    if (pt_value >= I_pt) {
                        int_pt++;
                        if (pt_value >= H_pt) {
                            high_pt++;
                        }
                    }
                }
            }
        }
    }
    return (high_pt >=1 and int_pt >=2 and low_pt>=3);
}

//          Delta R function 2 pions     //
bool DR_test2(float eta1, float eta2, float phi1, float phi2, float mindeltar2) {
  bool flag = true;
  float deta = eta1 - eta2;
  float dphi = ROOT::VecOps::DeltaPhi<float>(phi1, phi2);
  float dr2 = deta * deta + dphi * dphi;
  if (dr2 < mindeltar2) {
    flag = false;
    return flag;
  }
  return flag;
}

//          Delta R function 3 pions       //
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
bool isolation_function(Vec<Float_t> eta, //vector of all the particles features
                        Vec<Float_t> phi,
                        Vec<Float_t> pt,
                        Vec<std::size_t> idx,//indeces of that triplet (t_idx[0] e.g {0,3,6})
                        Vec<int> &iso_yet){
    Vec<bool> iso_bool;
    for(int pion : idx){ //nel for generale si scorre su quel indice 0 che è l'indice della tripletta
        double pt_sum=0.;
        if(iso_yet[pion]==1){ //already calculated but not iso
            iso_bool.push_back(false);
            continue;
        }
        if(iso_yet[pion]==2){ //already calculated iso
            iso_bool.push_back(true);
            continue;
        }
        if(iso_yet[pion]==0){
            for(int l=0; l<pt.size();++l){ //ciclo sulle altre particelle e seleziono quelle che sono nel cono, per tali calcolo la ptsum
                auto dr_part = ROOT::VecOps::DeltaR(eta[pion], eta[l], phi[pion], phi[l]);
                if (dr_part >= (min_dr_iso) && dr_part <= (max_dr_iso)) pt_sum += pt[l];
            }
            if(pt_sum/pt[pion] <= max_iso) {
                iso_bool.push_back(true);
                iso_yet[pion] = 2;
            }
            else {
                iso_bool.push_back(false);
                iso_yet[pion] = 1;
            }
        }
    }
    return ROOT::VecOps::All(iso_bool);
}
//          ISOLATION FUNCTION signle pion         //
bool isolation_single(Vec<Float_t> eta, //vector of all the particles features
                        Vec<Float_t> phi,
                        Vec<Float_t> pt,
                        std::size_t idx//indeces of that pion
                        ){
    bool is_iso;
    float pt_sum = 0;
    for(int l=0; l<pt.size();++l){ //ciclo sulle altre particelle e seleziono quelle che sono nel cono, per tali calcolo la ptsum
        auto dr_part = ROOT::VecOps::DeltaR(eta[idx], eta[l], phi[idx], phi[l]);
        if (dr_part >= (0.01) && dr_part <= (0.25)) pt_sum += pt[l];
    }
    if(pt_sum / pt[idx] <= max_iso) is_iso = true;
    else is_iso = false;
    return is_iso;
}



Vec<unsigned int> triplet_index(Vec<short> pdg,Vec<float> pt, Vec<float> eta,Vec<float> phi/*, Vec<float> mass, Vec<int> charge*/){
    Vec<int> charge;
    Vec<unsigned int> pdg_idx;
    Vec<Vec<short>> triplets_index;
    // Vec<float> triplets_invmass;
    Vec<float> triplets_ptsum;
    // Vec<unsigned int> triplet;
    float hpt = 20.;
    float ipt = 15.;
    float lpt = 12.; 
    // triplet.clear(); pdg_idx.clear(); triplets_invmass.clear(); triplets_ptsum.clear(); triplets_index.clear();
    Vec<unsigned int> iso_yet(pdg.size(), 0);
    
    for(unsigned int i = 0; i < pdg.size(); ++i) { //make list of pions or electron
        if (abs(pdg[i]) == 211 or abs(pdg[i]) == 11) {
            pdg_idx.push_back(i);
            charge.push_back(pdg[i] > 0 ? +1 : -1);
        }
    }

    if(pdg_idx.size() >= 3){ //check if there is at least one possible triplet passing pt test
        for (unsigned int i=0; i < pdg_idx.size(); i++){
            if(pt[pdg_idx[i]] < hpt) continue;
            if(isolation_single(eta, phi, pt, pdg_idx[i]) == false) continue;
            for(unsigned int j=0; j<pdg_idx.size(); j++){
                if (j==i || pt[pdg_idx[j]] < lpt) continue;
                if (pt[pdg_idx[j]] > pt[pdg_idx[i]] || (pt[pdg_idx[j]] == pt[pdg_idx[i]] and j < i)) continue; //order the pt
                if (ROOT::VecOps::DeltaR(eta[pdg_idx[i]], eta[pdg_idx[j]], phi[pdg_idx[i]], phi[pdg_idx[j]]) < min_dr) continue;

                for( unsigned int k=0; k<pdg_idx.size(); k++){
                    if(k==i || k==j || pt[pdg_idx[k]] < lpt) continue;
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
}

bool notempty(const Vec<unsigned int> &index) {  //used to check if any triplets passed in an event
  return !index.empty();
}

auto tripletmass(const Vec<unsigned int> &t, const Vec<float> &pts, const Vec<float> &etas, const Vec<float> &phis) {
  ROOT::Math::PtEtaPhiMVector p1(pts[t[0]], etas[t[0]], phis[t[0]], 0.1396);
  ROOT::Math::PtEtaPhiMVector p2(pts[t[1]], etas[t[1]], phis[t[1]], 0.1396);
  ROOT::Math::PtEtaPhiMVector p3(pts[t[2]], etas[t[2]], phis[t[2]], 0.1396);
  float mass = (p1 + p2 + p3).M();
  return mass;
}

bool initptcut(const Vec<float> &pts, const Vec<short> &pdgids) {
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
}

