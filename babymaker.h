#ifndef BABYMAKER_H
#define BABYMAKER_H

#include "TChain.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include <string>
#include "TF1.h"
#include "TH2.h"
#include "Math/VectorUtil.h" 
#include "CORE/CMS3.h"
#include "CORE/IsolationTools.h"
#include "CORE/VertexSelections.h"
#include "CORE/TriggerSelections.h"
#include "CORE/PhotonSelections.h"
#include "CORE/MuonSelections.h"
#include "CORE/ElectronSelections.h"
#include "CORE/Tools/goodrun.h"
#include "CORE/Tools/utils.h"
#include "CORE/Tools/jetcorr/Utilities.icc"
#include "CORE/Tools/jetcorr/SimpleJetCorrectionUncertainty.h"
#include "CORE/Tools/jetcorr/JetCorrectionUncertainty.h"
#include "TROOT.h"
#include <vector>
#include "Math/Vector4D.h" 
#include "Math/LorentzVector.h" 

#ifdef __MAKECINT__
#pragma link C++ class ROOT::Math::PxPyPzE4D<float>+;
#pragma link C++ class ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> >+;
#pragma link C++ typedef ROOT::Math::XYZTVectorF;
#endif

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

//Classes
class babyMaker {

    public:
        babyMaker(bool debug = 0) {
            verbose = debug;
        }
        void MakeBabyNtuple(TString input_name, TString output_name);
        void InitBabyNtuple();
        void CloseBabyNtuple () { BabyFile->cd(); BabyTree->Write(); BabyFile->Close(); }
        int ProcessBaby();

    protected:
        TFile* BabyFile;
        TTree* BabyTree;
        TString input_filename;
        TString output_filename;

    private:

        //Switches
        bool verbose;

        //Meta Variables
        TString filename;
        ULong64_t event;
        int lumi;
        int run;

        float met;
        float metPhi;

        float rho;

        bool pass_golden_json;

        bool pass_double_photon_trigger;
        bool pass_single_photon_trigger;

        vector<LorentzVector> jets;

        vector<LorentzVector> photons;


};

#endif
