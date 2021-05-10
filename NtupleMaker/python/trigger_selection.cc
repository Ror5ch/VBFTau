#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility> 	//?
#include <map> 		//?
#include <string>

#include "TH1F.h"
#include "TH2F.h"	//won't need?
#include "TH3F.h"	//same
#include "TTree.h"
#include "TChain.h"	//?
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include "trigger_tree.h"

int main(int argc, char** argv)	{
    //myMap1 = new map<std::string, TH1F*>(); // i think this is for generalized naming/name fixing of different files
    //////////////////////////////////////
    // Input Arguments			//
    // 1) Input Path			//
    // 2) Output Path			//
    //////////////////////////////////////
    std::string in = *(argv + 1);
    std::string out = *(argv + 2);
    std::string inName = in;
    std::string outName = out;
    TFile *fIn = TFile::Open(inName.c_str());
    //fIn->SetDirectory(0);
    TTree* treePtr = (TTree*) fIn->Get("demo/vbf");
    trigger_tree* inTree = new trigger_tree (treePtr);

    // Open input file and make new output file
    //TTree *inTree = (TTree*)fIn->Get("demo/vbf");
    TTree *outTree = new TTree("outTree", "outTree");
    //outTree->SetDirectory(0);
    //here's where you'd make a header file for that input file i think...
    int VBFTwoTriggerEta;
    outTree->Branch("VBFTwoTriggerEta", &VBFTwoTriggerEta);

    // Event Loop
    for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000 == 0) { std::cout << std::to_string(iEntry) << std::endl;}
        //inTree->GetBranch("hltMatchedVBFTwo_eta");
	VBFTwoTriggerEta = inTree->hltMatchedVBFTwo_eta;
	if (fabs(VBFTwoTriggerEta) > 2.1) continue;
	outTree->Fill();

    } // end event loop

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();
    outTree->Write();
    fOut->Close();
    return 0;
}
