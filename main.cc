#include "babymaker.h"

// #include "./CORE/CMS3.h"
// #include "./CORE/Tools/goodrun.h"
// #include "TTree.h"
// #include "TFile.h"
// #include "TString.h"
// #include <string>

int main(int argc, char *argv[]){

    TString input_filename, output_filename;
    unsigned int max_nevents = 0;
    
    if (argc > 2) {
        input_filename = TString(argv[1]);
        output_filename = TString(argv[2]);

        if(argc > 3) {
            max_nevents = atoi(argv[3]);
            if(max_nevents > 0) std::cout << "will only run over " << max_nevents << " events" << std::endl;
            else std::cout << "will run over all events" << std::endl;
        }
    } 
    else { 
        std::cout << "not enough arguments! ./main.exe <inputname> <outputname> [max_nevents=-1]" << std::endl;  
        return 2;
    }

    babyMaker *mylooper = new babyMaker();

    //Set up file and tree
    mylooper->MakeBabyNtuple(input_filename, output_filename);

    TFile *f = TFile::Open(input_filename);

    if(!f) {
        std::cout << "ERROR: opening file " << input_filename << std::endl;
        return 3;
    }

    std::cout << "Successfully opened file " << input_filename << std::endl;
    TTree *tree = (TTree*)f->Get("Events");
    cms3.Init(tree);

    //Event Counting
    unsigned int nEvents = tree->GetEntries();
    unsigned int nEventsTotal = 0;
    std::cout << "nEvents: " << tree->GetEntries() << std::endl;

    //Event Loop
    int processed_events = 0;
    for(unsigned int ievent=0; ievent < nEvents; ievent++){

        if(max_nevents > 0 && ievent >= max_nevents) break;

        //Get Event Content
        cms3.GetEntry(ievent);
        nEventsTotal++;

        //Progress bar
        CMS3::progress(nEventsTotal, nEvents);

        // tally up return code 0 ("good") events -- up to user to return 0 or not
        int ret = mylooper->ProcessBaby(); 
        if(ret == 0) processed_events++;

    }//event loop 

    //Delete Chain
    mylooper->CloseBabyNtuple();

    std::cout << "done! we processed " << processed_events << " good events" << std::endl;

    return 0;

}
/* vim: set ft=cpp: */
