#include "analysis.h"
#include <cmath>
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RVec.hxx>
#include <Math/Vector4D.h>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>

//definition of w3pi selection class:
    //contains defitions of the functions for the selection maketriplets

class w3pi_selection : public rdfAnalysis {
public:
    w3pi_selection(const std::string &cutChoice, bool verbose);
    ~w3pi_selection() override {}
    Report run(const std::string &informat,
            const std::vector<std::string> &infiles,
            const std::string &outformat,
            const std::string &outfile) const override;

private:
    struct Cuts {
        float H_pt=15., I_pt = 12., L_pt=8.;
        float max_iso = 0.8;
        float min_mass = 40;
        float max_mass = 120;
        float min_dr = 0.5;
        float min_dr_iso = 0.01;
        float max_dr_iso = 0.25;
    };
private:
    Cuts cuts;
    bool verbose_;

    void analyze(ROOT::RDataFrame &d,
                const std::string &format,
                unsigned long int &ntot,
                unsigned long int &npre,
                unsigned long int &npass,
                const std::string &outputformat,
                const std::string &outFile) const;

    inline static bool DR_test_2(float eta1, float eta2, float phi1, float phi2, float mindeltar2) {
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
    inline static bool isolation_single(Vec<Float_t> eta, //vector of all the particles features
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

    inline static bool notempty(const Vec<unsigned int> &index) {  //used to filter events having no triplet
       return !index.empty();
    }

    inline static float tripletmass(const Vec<unsigned int> &t, const Vec<float> &pts, const Vec<float> &etas, const Vec<float> &phis) {
        ROOT::Math::PtEtaPhiMVector p1(pts[t[0]], etas[t[0]], phis[t[0]], 0.1396);
        ROOT::Math::PtEtaPhiMVector p2(pts[t[1]], etas[t[1]], phis[t[1]], 0.1396);
        ROOT::Math::PtEtaPhiMVector p3(pts[t[2]], etas[t[2]], phis[t[2]], 0.1396);
        float mass = (p1 + p2 + p3).M();
        return mass;
    }



}