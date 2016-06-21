#include "babymaker.h"

using namespace tas;
using namespace std;

//Main functions
void babyMaker::MakeBabyNtuple(TString input_name, TString output_name) {

    input_filename = input_name;
    output_filename = output_name;

    //Create Baby
    BabyFile = new TFile(output_name, "RECREATE");
    BabyFile->cd();
    BabyTree = new TTree("t", "X750 Baby Ntuple");

    //Define Branches
    BabyTree->Branch("filename" , &filename ) ;
    BabyTree->Branch("is_real_data"   , &is_real_data ) ;
    BabyTree->Branch("event"    , &event    ) ;
    BabyTree->Branch("lumi"     , &lumi     ) ;
    BabyTree->Branch("run"      , &run      ) ;

    BabyTree->Branch("met"      , &met      ) ;
    BabyTree->Branch("metPhi"   , &metPhi   ) ;

    BabyTree->Branch("rho"   , &rho   ) ;

    BabyTree->Branch("pass_golden_json", &pass_golden_json );

    BabyTree->Branch("pass_double_photon_trigger", &pass_double_photon_trigger );
    BabyTree->Branch("pass_single_photon_trigger", &pass_single_photon_trigger );

    BabyTree->Branch("jets", &jets );

    BabyTree->Branch("photons", &photons );

    set_goodrun_file("goldenJson_2015_2p26fb_2016_2p6fb.txt");

  // std::vector<std::string> jetcorr_filenames_25ns_DATA_pfL1;
  // std::vector<std::string> jetcorr_filenames_25ns_DATA_pfL1L2L3;
  // std::vector<std::string> jetcorr_filenames_25ns_DATA_pfL2L3;

  // jetcorr_filenames_25ns_DATA_pfL1.push_back    ("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV3_DATA_L1FastJet_AK4PFchs.txt");
  // jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV3_DATA_L1FastJet_AK4PFchs.txt");
  // jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV3_DATA_L2Relative_AK4PFchs.txt");
  // jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV3_DATA_L3Absolute_AK4PFchs.txt");
  // jetcorr_filenames_25ns_DATA_pfL1L2L3.push_back("CORE/Tools/jetcorr/data/run2_25ns/Spring16_25nsV3_DATA_L2L3Residual_AK4PFchs.txt");

  // FactorizedJetCorrector *jet_corrector_25ns_DATA_pfL1; 
  // FactorizedJetCorrector *jet_corrector_25ns_DATA_pfL1L2L3; 

  // jet_corrector_25ns_DATA_pfL1 = makeJetCorrector(jetcorr_filenames_25ns_DATA_pfL1); 
  // jet_corrector_25ns_DATA_pfL1L2L3 = makeJetCorrector(jetcorr_filenames_25ns_DATA_pfL1L2L3); 

}

void babyMaker::InitBabyNtuple(){

    filename = "";
    is_real_data = false;
    event = -1;
    lumi = -1;
    run = -1;

    met = -1;
    metPhi = -1;

    rho = -1;

    pass_golden_json = false;

    pass_double_photon_trigger = false;
    pass_single_photon_trigger = false;

    jets.clear();

    photons.clear();

} 

//Main function
int babyMaker::ProcessBaby() {
    //Initialize variables
    InitBabyNtuple();

    //Fill Easy Variables
    filename = input_filename;
    is_real_data = input_filename.Contains("Run201");
    event = evt_event();
    lumi = evt_lumiBlock();
    run = evt_run();

    met = evt_pfmet();
    metPhi = evt_pfmetPhi();
    rho = evt_fixgrid_all_rho();
    if(is_real_data) {
        pass_golden_json = goodrun(run,lumi);
    }

    // Event is a dud if doesn't fire a photon trigger
    pass_double_photon_trigger = passHLTTriggerPattern("HLT_DoublePhoton60_v");
    pass_single_photon_trigger = passHLTTriggerPattern("HLT_Photon165_HE10_v");
    if(is_real_data && !pass_single_photon_trigger && !pass_double_photon_trigger) return 1;

    // Event is a dud if less than 2 "good" jets
    for(int ijet = 0; ijet < (int)(pfjets_p4().size()); ijet++) {
        LorentzVector jet = pfjets_p4()[ijet];
        jet *= pfjets_undoJEC()[ijet];
        float emfrac = (pfjets_chargedEmE()[ijet]+pfjets_neutralEmE()[ijet])/jet.E();
        if(jet.pt() < 50) continue;
        if(emfrac < 0.9) continue;
        jets.push_back(jet);
    }

    // Now start filling useful stuff


    for(int iphot = 0; iphot < (int)(photons_p4().size()); iphot++) {
        LorentzVector photon = photons_p4()[iphot];
        if(photon.pt() < 50) continue;
        photons.push_back(photon);
    }

    BabyTree->Fill();

    return 0; 

}
