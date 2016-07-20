tag="v1.01"
analysis="FA"
merge_dir="merge/"
postfix="_new"

mkdir -p  $merge_dir

hadd -k $merge_dir/qcd_full${postfix}.root /hadoop/cms/store/user/namin/AutoTwopler_babies/QCD_${tag}/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8_RunIISpring16MiniAODv2-PUSpring16_magnetOn_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/*.root
# hadd -k $merge_dir/qcd_fast${postfix}.root /hadoop/cms/store/user/namin/AutoTwopler_babies/QCD_${tag}/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8_RunIISpring16MiniAODv2-PUSpring16Fast_ForSUSJECs_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/*.root
# hadd -k $merge_dir/tt_full${postfix}.root /hadoop/cms/store/user/namin/AutoTwopler_babies/QCD_${tag}/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/*.root
# hadd -k $merge_dir/tt_fast${postfix}.root /hadoop/cms/store/user/namin/AutoTwopler_babies/QCD_${tag}/TTJets_13TeV-madgraphMLM_RunIISpring16MiniAODv2-pLHE_PUSpring16Fast_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1//*.root
