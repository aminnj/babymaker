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

    BabyTree->Branch("npu"     , &npu     ) ;
    BabyTree->Branch("truenumint"      , &truenumint      ) ;

    BabyTree->Branch("met"      , &met      ) ;
    BabyTree->Branch("metPhi"   , &metPhi   ) ;

    BabyTree->Branch("rho"   , &rho   ) ;

    BabyTree->Branch("pass_golden_json", &pass_golden_json );

    BabyTree->Branch("fail_filter", &fail_filter );
    BabyTree->Branch("failing_jet", &failing_jet );


    BabyTree->Branch("jets", &jets );
    BabyTree->Branch("genjets", &genjets );
    BabyTree->Branch("failing_jets", &failing_jets );

    BabyTree->Branch("htall", &htall );
    BabyTree->Branch("ht40", &ht40 );
    BabyTree->Branch("ht30", &ht30 );
    BabyTree->Branch("ht20", &ht20 );

    BabyTree->Branch("mhtall", &mhtall );
    BabyTree->Branch("mht40", &mht40 );
    BabyTree->Branch("mht30", &mht30 );
    BabyTree->Branch("mht20", &mht20 );

    BabyTree->Branch("nlepsW", &nlepsW );

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

    npu = -1;
    truenumint = -1;

    met = -1;
    metPhi = -1;

    rho = -1;

    pass_golden_json = false;

    fail_filter = false;
    failing_jet = LorentzVector(0,0,0,0);

    jets.clear();
    genjets.clear();
    failing_jets.clear();

    htall = -1;
    ht40 = -1;
    ht30 = -1;
    ht20 = -1;
    mhtall = -1;
    mht40 = -1;
    mht30 = -1;
    mht20 = -1;

    nlepsW = 0;

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

    truenumint = puInfo_trueNumInteractions()[0];
    npu = puInfo_nPUvertices()[0];

    met = evt_pfmet();
    metPhi = evt_pfmetPhi();
    rho = evt_fixgrid_all_rho();
    if(is_real_data) {
        pass_golden_json = goodrun(run,lumi);
    }


    // Now start filling useful stuff

    for(unsigned int ijet = 0; ijet < pfjets_p4().size(); ijet++) {
        LorentzVector jet = pfjets_p4()[ijet]*pfjets_undoJEC()[ijet];
        int best_igen = -1;
        float best_dR = 0.1;
        for(unsigned int igen = 0; igen < genjets_p4NoMuNoNu().size(); igen++) {
            LorentzVector genjet = genjets_p4NoMuNoNu()[igen];
            float dR = ROOT::Math::VectorUtil::DeltaR(jet,genjet);
            if(dR < best_dR) {
                best_igen = igen;
                best_dR = dR;
            }
        }
        if(best_igen >= 0) {
            jets.push_back(jet);
            genjets.push_back(genjets_p4NoMuNoNu()[best_igen]);
        }
    }

    ht20 = 0;
    ht30 = 0;
    ht40 = 0;
    htall = 0;
    LorentzVector mht_vec20 = LorentzVector(0,0,0,0);
    LorentzVector mht_vec30 = LorentzVector(0,0,0,0);
    LorentzVector mht_vec40 = LorentzVector(0,0,0,0);
    LorentzVector mht_vecall = LorentzVector(0,0,0,0);
    for(unsigned int ijet = 0; ijet < pfjets_p4().size(); ijet++) {
        LorentzVector jet = pfjets_p4()[ijet]*pfjets_undoJEC()[ijet];
        float pt = jet.Pt();
        
        htall += pt;
        mht_vecall -= jet;

        if(pt < 20) continue;
        ht20 += pt;
        mht_vec20 -= jet;

        if(pt < 30) continue;
        ht30 += pt;
        mht_vec30 -= jet;

        if(pt < 40) continue;
        ht40 += pt;
        mht_vec40 -= jet;

    }
    mhtall = mht_vecall.Pt();
    mht40 = mht_vec40.Pt();
    mht30 = mht_vec30.Pt();
    mht20 = mht_vec20.Pt();


    fail_filter = false;
    for(unsigned int ijet = 0; ijet<pfjets_p4().size();ijet++){
        LorentzVector jet = pfjets_p4()[ijet]*pfjets_undoJEC()[ijet];
        if(jet.Pt()<20) continue;
        if(fabs(jet.Eta())>2.5) continue;
        bool isgenmatch = false;
        for(unsigned int igen = 0; igen<genjets_p4NoMuNoNu().size();igen++){
            LorentzVector genjet = genjets_p4NoMuNoNu()[igen];
            if(ROOT::Math::VectorUtil::DeltaR(jet,genjet)<0.3) { isgenmatch = true; break; }
        }
        if(isgenmatch) continue;
        float chf = pfjets_chargedHadronE()[ijet] / (jet.energy());
        if(chf>0.1) continue;
        if(!fail_filter) failing_jet = jet;
        fail_filter = true;
        failing_jets.push_back(jet);
        // break;
    }

    // nleps
    for(unsigned int i = 0; i < genps_id().size(); i++) {
        nlepsW += genps_id().at(i) >= 11 && genps_id().at(i) <= 16 && abs(genps_id_simplemother().at(i))==24;
    }

    BabyTree->Fill();

    return 0; 

}
