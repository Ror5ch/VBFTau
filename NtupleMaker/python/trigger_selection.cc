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

// example running ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root

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
    TTree* treePtr = (TTree*) fIn->Get("demo/vbf");
    trigger_tree* inTree = new trigger_tree (treePtr);

    // Open input file and make new output file, also declare necessary variables
    TTree *outTree = new TTree("outTree", "outTree");
    outTree->SetDirectory(0);
    int j1_loc; //jet1 location, either position 0 or 1 in the vector of jets
    int j2_loc;
    float j1_pt;
    float j2_pt;
    float j1_eta;
    float j2_eta;
    float t1_pt;
    float t2_pt;
    float VBFOneTriggerPt;
    float VBFOneTriggerEta;
    //float VBFOneTriggerPhi;
    //float VBFOneTriggerEnergy;
    float VBFTwoTriggerPt;
    float VBFTwoTriggerEta;
    //float VBFTwoTriggerPhi;
    //float VBFTwoTriggerEnergy;
    int vecSizeVBFOne;
    int vecSizeVBFTwo;
    int vecSizeHpsTau;
    //outTree->Branch("VBFOneTriggerPt", &VBFOneTriggerPt);
    //outTree->Branch("VBFOneTriggerEta", &VBFOneTriggerEta);
    //outTree->Branch("VBFTwoTriggerPt", &VBFTwoTriggerPt);
    //outTree->Branch("VBFTwoTriggerEta", &VBFTwoTriggerEta);
    outTree->Branch("j1_pt", &j1_pt);
    outTree->Branch("j2_pt", &j2_pt);
    outTree->Branch("j1_eta", &j1_eta);
    outTree->Branch("j2_eta", &j2_eta);
    outTree->Branch("t1_pt", &t1_pt);
    outTree->Branch("t2_pt", &t2_pt);

    // Event Loop
    for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000 == 0) { std::cout << std::to_string(iEntry) << std::endl;}
	vecSizeHpsTau = inTree->hltHpsDoublePFTau_pt->size();
	vecSizeVBFOne = inTree->hltMatchedVBFOne_pt->size();
	vecSizeVBFTwo = inTree->hltMatchedVBFTwo_pt->size(); 

	if (vecSizeHpsTau != 2) continue;
	t1_pt = inTree->hltHpsDoublePFTau_pt->at(0);
	t2_pt = inTree->hltHpsDoublePFTau_pt->at(1);
	if (t2_pt > t1_pt){
	     t1_pt = inTree->hltHpsDoublePFTau_pt->at(1);
	     t2_pt = inTree->hltHpsDoublePFTau_pt->at(0);
	}

	if (t1_pt < 25) continue;
	if (t2_pt < 25) continue;

	if (vecSizeVBFOne == 0 || vecSizeVBFTwo != 2) continue;
	if (vecSizeVBFOne == 2){// if there are 2 jets with pt > 115, make the greater pt jet j1_pt
	     j1_pt = inTree->hltMatchedVBFOne_pt->at(0);
	     j1_loc = 0;
	     j2_pt = inTree->hltMatchedVBFOne_pt->at(1);
	     j2_loc = 1;
	     if (j2_pt > j1_pt){
	     	j1_pt = inTree->hltMatchedVBFOne_pt->at(1);
		j1_loc = 1;
	     	j2_pt = inTree->hltMatchedVBFOne_pt->at(0);
		j2_loc = 0;
	     }
	     j1_eta = inTree->hltMatchedVBFOne_eta->at(j1_loc);
	     j2_eta = inTree->hltMatchedVBFOne_eta->at(j2_loc);
	}
	if (vecSizeVBFOne == 1){// if there's 1 jet with pt > 115, make it the leading one. Subleading is in prior filter.
	     j1_pt = inTree->hltMatchedVBFOne_pt->at(0);
	     j1_loc = 0;
	     j2_pt = inTree->hltMatchedVBFTwo_pt->at(0);
	     j2_loc = 0; 
	     if (j1_pt == j2_pt) {
		j2_pt = inTree->hltMatchedVBFTwo_pt->at(1);
		j2_loc = 1;
	     }
	     j1_eta = inTree->hltMatchedVBFOne_eta->at(j1_loc);
	     j2_eta = inTree->hltMatchedVBFTwo_eta->at(j2_loc);
	}
	if (fabs(j1_eta) > 2.1 || fabs(j2_eta) > 2.1) continue;
	if (j1_pt < 120) continue;
	if (j2_pt < 45) continue;
	outTree->Fill();

    } // end event loop

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();
    outTree->Write();
    fOut->Close();
    return 0;
}
