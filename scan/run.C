{
    gSystem->Exec("mkdir -p plots");

    gROOT->ProcessLine(".L ../Software/dataMCplotMaker/dataMCplotMaker.cc+");
    gSystem->Load("../CORE/CMS3_CORE.so");
    gROOT->ProcessLine(".L scan.C+");

    TChain *ch = new TChain("Events");
    ch->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/V08-00-05/merged_ntuple_1.root");

    scan(ch);

}
