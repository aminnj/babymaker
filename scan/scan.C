#pragma GCC diagnostic ignored "-Wsign-compare"
#include "../Software/dataMCplotMaker/dataMCplotMaker.h"

//Regular includes
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TH1.h"
#include "TChain.h"

#include "../CORE/JetSelections.h"

using namespace std;
using namespace tas;

int scan(TChain *ch){

    TH1F * h_met = new TH1F("met", "met", 50, 0, 300);

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();

    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);

    // File Loop
    while ( (currentFile = (TFile*)fileIter.Next()) ) { 

        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        cms3.Init(tree);

        TString filename(currentFile->GetTitle());

        // Loop over Events in current file
        for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event) {

            // Get Event Content
            cms3.GetEntry(event);
            nEventsTotal++;

            //Progress
            CMS3::progress(nEventsTotal, nEventsChain);

            h_met->Fill(evt_pfmet());

        }//event loop

        delete file;
    }//file loop

    TString comt = " --outOfFrame --lumi 1.0 --type Simulation --darkColorLines --legendCounts --legendRight -0.05  --outputName plots/";
    std::string com = comt.Data();
    TH1F * empty = new TH1F("","",1,0,1);

    dataMCplotMaker(empty,{h_met} ,{"t#bar{t}"},"MET","",com+"h_met.pdf --isLinear");

    return 0;
}
