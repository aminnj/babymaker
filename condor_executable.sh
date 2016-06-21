if [ -z "$DATASET" ]; then 
    DATASET=/SinglePhoton/Run2016B-PromptReco-v2/MINIAOD
    FILENAME=/home/users/namin/X750/SinglePhoton.root
fi

OUTNAME="output.root"
NEVENTS=0
if [ -z "$EXTRA1" ]; then NEVENTS=$EXTRA1; fi

# Set CMSSW environment
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /cvmfs/cms.cern.ch/slc6_amd64_gcc530/cms/cmssw/CMSSW_8_0_6/
eval `scramv1 runtime -sh`
cd -

# Need this for .so files
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD

tar -xzf package.tar.gz

echo "executing ./main.exe $FILENAME $OUTNAME $NEVENTS"
./main.exe $FILENAME $OUTNAME $NEVENTS
