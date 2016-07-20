CMSSWVER=CMSSW_8_0_6
[[ -d $CMSSWVER ]] || cmsrel $CMSSWVER
cd $CMSSWVER/
cmsenv
cd ../
[[ -d CORE/ ]] || git clone https://github.com/cmstas/CORE
[[ -d NtupleTools/ ]] || git clone https://github.com/cmstas/NtupleTools
[[ -d Software/ ]] || git clone https://github.com/cmstas/Software
export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
