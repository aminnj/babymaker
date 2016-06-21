# Template babymaker
- AutoTwopler integration

# Instructions
0. Check out contents of this repo somewhere

1. `. setup.sh` to check out some repos (and should also do this when developing to pick up cmsenv and LDLIBRARY`

2. Compile with `make -j10`, and as it is right now, syntax to run `main.exe` is 
```./main.exe <input rootfile> <output name> [<max nevents>]```

3. When done developing, do `. make_tar.sh` to copy the package file and executable into a folder.

4. Paste AutoTwopler instructions.txt line from `make_tar.sh` output into the `instructions.txt` file of the `NtupleTools/AutoTwopler` dir.

5. Inside the `AutoTwopler` directory, run `. setup.sh` and `./run.py` to submit jobs to condor.

6. A simple script to merge output files is `merge.sh`
