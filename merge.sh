tag="v1.00"
analysis="FA"
merge_dir="merge/"
mkdir -p  $merge_dir

hadd $merge_dir/singlephoton2015_C.root /hadoop/cms/store/user/${USER}/AutoTwopler_babies/${analysis}_${tag}/SinglePhoton_Run2015C_25ns-05Oct2015-v1/*.root
