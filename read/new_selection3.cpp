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
#include <TStopwatch.h>


template <typename T> using Vec = ROOT::RVec<T>; 

float max_iso = 0.45;
float min_mass = 60;
float max_mass = 100;

bool pt_cut(const Vec<float> &pt, const Vec<short> &pid){
    int high_pt=0, int_pt=0, low_pt=0;
    float H_pt=20., I_pt = 15., L_pt=12.;
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
    return ROOT::VecOps::All(ROOT::VecOps::Map(deltar_vec, [](float x){return (x>0.25); }));
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
                if (dr_part >= (0.01) && dr_part <= (0.25)) pt_sum += pt[l];
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
                        std::size_t idx/*,//indeces of that pion
                        Vec<int> &iso_yet*/){
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
    Vec<float> triplets_invmass;
    Vec<float> triplets_ptsum;
    // Vec<unsigned int> triplet;
    float hpt = 20.;
    float ipt = 15.;
    float lpt = 12.; 
    // triplet.clear(); pdg_idx.clear(); triplets_invmass.clear(); triplets_ptsum.clear(); triplets_index.clear();
    // Vec<unsigned int> iso_yet(pdg.size(), 0);

    for(unsigned int i = 0; i < pdg.size(); ++i) { //make list of pions or electron
        if (abs(pdg[i]) == 211 or abs(pdg[i]) == 11) {
            pdg_idx.push_back(i);
            charge.push_back(abs(pdg[i]) == 11 ? (pdg[i] > 0 ? -1 : +1) : (pdg[i] > 0 ? +1 : -1));
        }
    }

    if(pdg_idx.size() >= 3){ //check if there is at least one possible triplet passing pt test
        for (unsigned int i=0; i < pdg_idx.size(); i++){
            if(pt[pdg_idx[i]] < hpt) continue;
            if(isolation_single(eta, phi, pt, pdg_idx[i]) == false) continue; //SI PUO AGGIORNARE ISO_YET QUA!!
            for(unsigned int j=0; j<pdg_idx.size(); j++){
                if (j==i || pt[pdg_idx[j]] < lpt) continue;
                if (pt[pdg_idx[j]] > pt[pdg_idx[i]] || (pt[pdg_idx[j]] == pt[pdg_idx[i]] and j < i)) continue; //order the pt
                if (ROOT::VecOps::DeltaR(eta[pdg_idx[i]], eta[pdg_idx[j]], phi[pdg_idx[i]], phi[pdg_idx[j]]) < 0.5) continue;
                // if (DR_test2(eta[pdg_idx[i]], eta[pdg_idx[j]], phi[pdg_idx[i]], phi[pdg_idx[j]], 0.5)==false) continue;
                if (isolation_single(eta, phi, pt, pdg_idx[j]) == false) continue;
                for( unsigned int k=0; k<pdg_idx.size(); k++){
                    
                    if(k==i || k==j || pt[pdg_idx[k]] < lpt) continue;
                    if (pt[pdg_idx[k]] > pt[pdg_idx[i]] || pt[pdg_idx[k]]==pt[pdg_idx[i]] && k<i ) continue;
                    if (pt[pdg_idx[k]] > pt[pdg_idx[j]] || pt[pdg_idx[k]]==pt[pdg_idx[j]] && k<j ) continue; //order the pt
                    if(ROOT::VecOps::DeltaR(eta[pdg_idx[k]], eta[pdg_idx[i]], phi[pdg_idx[k]], phi[pdg_idx[i]]) < 0.5 &&
                       ROOT::VecOps::DeltaR(eta[pdg_idx[k]], eta[pdg_idx[j]], phi[pdg_idx[k]], phi[pdg_idx[j]]) < 0.5)
                            continue; //DR test
                    if (isolation_single(eta, phi, pt, pdg_idx[k]) == false) continue;

                    // triplet = {pdg_idx[i], pdg_idx[j], pdg_idx[k]};

                    if( abs( charge[pdg_idx[i]] + charge[pdg_idx[j]] + charge[pdg_idx[k]]) == 1 ){ //charge test
                        ROOT::Math::PtEtaPhiMVector p1(pt[pdg_idx[i]], eta[pdg_idx[i]], phi[pdg_idx[i]], 0.1396);
                        ROOT::Math::PtEtaPhiMVector p2(pt[pdg_idx[j]], eta[pdg_idx[j]], phi[pdg_idx[j]], 0.1396);
                        ROOT::Math::PtEtaPhiMVector p3(pt[pdg_idx[k]], eta[pdg_idx[k]], phi[pdg_idx[k]], 0.1396);
                        float inv_mass = (p1 + p2 + p3).M();
                        if(inv_mass >= min_mass && inv_mass <= max_mass){//mass test

                            Vec<unsigned int> triplet = {pdg_idx[i], pdg_idx[j], pdg_idx[k]};
                            triplets_index.push_back(triplet); //save triplet
                            triplets_ptsum.push_back(pt[triplet[0]] + pt[triplet[1]] + pt[triplet[2]]);
                            // triplets_invmass.push_back(inv_mass);

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
    // else{
    //     Vec<double> invmass_pt;
    //     int is_best;
    //     for(int k=0; k<triplets_index.size(); k++){
    //         double m_dot_p = triplets_invmass[k] * triplets_ptsum[k];
    //         invmass_pt.push_back(m_dot_p);
    //         if(m_dot_p > invmass_pt[k-1]) is_best = k;
    //     }
    //     return triplets_index[is_best]; //return only one triplet
    // }    
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
      if (pts[i] >= 12.) {
        lowcut++;
        if (pts[i] >= 15.) {
          intermediatecut++;
          if (pts[i] >= 20.)
            highcut++;
        }
      }
    }
  }
  return (lowcut > 2 and intermediatecut > 1 and highcut > 0);
}

int main(){

    auto file_path = "Tree.root";
    auto tree_name = "Events";
    
    TStopwatch timer;
    ROOT::RDataFrame df(tree_name,file_path);
    // df.Describe().Print();

    auto df0 = df.Filter(initptcut, {"L1Puppi_pt", "L1Puppi_pid"});/*.Define("L1Puppi_mass", give_mass_vec, {"Puppi_pid"}).Define("L1Puppi_charge", give_charge_vec, {"Puppi_pid"})*/
    auto df1 = df0.Define("Triplet_Index", triplet_index, {"L1Puppi_pid", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi"/*, "L1Puppi_mass", "L1Puppi_charge"*/})
            .Filter(notempty,{"Triplet_Index"})
            .Define("Triplet_invmass",tripletmass,{"Triplet_Index","L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi"});
    auto n0 = *df.Count();
    auto n00 = *df0.Count();
    // auto n1 = *df1.Count();
    auto masshist = df1.Histo1D<float>({"masshist", "W Boson mass from selected pions; mass (GeV/c^2)", 100, 0, 100}, "Triplet_invmass");
    unsigned int n1 = masshist->GetEntries();
    timer.Stop();
    std::cout << "Count before: " << n0 << std::endl;
    std::cout << "Count preselected: " << n00 << std::endl;
    std::cout << "Count after:" << n1 << std::endl;

    std::cout << "timer: " << timer.RealTime() << std::endl;
    return 0;
}


// int main(int argc, char **argv){
//     if (argc <= 1) {
//         std::cout << "Usage: inputFile.root (format)" << std::endl;
// 	return 1;
//     }
//     // auto verbosity = ROOT::Experimental::RLogScopedVerbosity(ROOT::Detail::RDF::RDFLogChannel(), ROOT::Experimental::ELogLevel::kInfo);
//     std::string c_pt, c_eta, c_phi, c_pdgId;
//     bool isRNtuple = (std::string(argv[2]).find("rntuple")==0);
//     if(isRNtuple){
//         c_pt  = "Puppi.pt";
//         c_eta = "Puppi.eta";
//         c_phi = "Puppi.phi";
//         c_pdgId = "Puppi.pdgId";
//     }
//     else{
//         c_pt  = "pt";
//         c_eta = "eta";
//         c_phi = "phi";
//         c_pdgId = "pid";
//     }

//     TStopwatch timer;
//     timer.Start();

//     ROOT::RDataFrame df = isRNtuple ? ROOT::RDF::Experimental::FromRNTuple("Events", argv[1]) : ROOT::RDataFrame("Events", argv[1]);
//     // ROOT::RDataFrame df0 = ROOT::RDataFrame("Events", argv[1]);
//     auto df0 = df.Filter(pt_cut, {"L1Puppi_pt", "L1Puppi_pid"});/*.Define("L1Puppi_mass", give_mass_vec, {"Puppi_pid"}).Define("L1Puppi_charge", give_charge_vec, {"Puppi_pid"})*/
//     auto df1 = df0.Define("Triplet_Index", triplet_index, {"L1Puppi_pid", "L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi"/*, "L1Puppi_mass", "L1Puppi_charge"*/})
//             .Filter(notempty,{"Triplet_Index"})
//             .Define("Triplet_invmass",tripletmass,{"Triplet_Index","L1Puppi_pt", "L1Puppi_eta", "L1Puppi_phi"});
//     auto hist = df1.Histo1D({"L1Triplet_mass", "InvMass ;mass (GeV);N_{Triplets}", 200, 0, 200}, "Triplet_invmass").GetValue(); 
//     unsigned int ntot = *df.Count();
//     unsigned int npass = hist.GetEntries();
//     timer.Stop();

//     double treal = timer.RealTime();
//     printf("Run on %s, %9u events, selected %8u events (%.6f) in %7.3f s (%7.1f kHz)\n", argv[1], ntot, npass, npass / float(ntot), timer.RealTime(), ntot * .001 / timer.RealTime());
//     return 0;
// }