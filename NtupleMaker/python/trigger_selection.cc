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
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include "trigger_tree.h"

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root

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
    int j2_loc; //other intermediate variables
    int t1_loc;
    int t2_loc;
    int vecSizeVBFOne;
    int vecSizeVBFTwo;
    int vecSizeHpsTau;
    
    float j1_pt; // branch variables (eta, phi, energy are necessary for mjj calculation)
    float j1_eta;
    float j1_phi;
    float j1_energy;
    float j2_pt;
    float j2_eta;
    float j2_phi;
    float j2_energy;
    float t1_pt;
    float t1_eta;
    float t1_phi;
    float t1_energy;
    float t2_pt;
    float t2_eta;
    float t2_phi;
    float t2_energy;
    float mjj;
    
    int vecSizeAODJet;
    int vecSizeAODTau;

    float j1_pt_A; //A is for MiniAOD
    float j1_eta_A;
    float j1_phi_A;
    float j1_energy_A;
    float j2_pt_A;
    float j2_eta_A;
    float j2_phi_A;
    float j2_energy_A;
    float t1_pt_A;
    float t1_eta_A;
    float t1_phi_A;
    float t1_energy_A;
    float t2_pt_A;
    float t2_eta_A;
    float t2_phi_A;
    float t2_energy_A;
    float mjj_A;

    float j3_pt_A;
    float j4_pt_A;

    float dRj1;
    float dRj2;
    float dRt1;
    float dRt2;

    int passSel;
    int passTrig;
    int passNewTrig;
    int passSelAndTrig;
    int passSelAndNewTrig;
    int matched;

    outTree->Branch("j1_pt", &j1_pt);
    outTree->Branch("j2_pt", &j2_pt);
    outTree->Branch("j1_eta", &j1_eta);
    outTree->Branch("j2_eta", &j2_eta);
    outTree->Branch("j1_phi", &j1_phi);
    outTree->Branch("j2_phi", &j2_phi);
    outTree->Branch("t1_pt", &t1_pt);
    outTree->Branch("t2_pt", &t2_pt);
    outTree->Branch("t1_eta", &t1_eta);
    outTree->Branch("t2_eta", &t2_eta);
    outTree->Branch("t1_phi", &t1_phi);
    outTree->Branch("t2_phi", &t2_phi);
    outTree->Branch("mjj", &mjj);

    outTree->Branch("j1_pt_A", &j1_pt_A);
    outTree->Branch("j2_pt_A", &j2_pt_A);
    outTree->Branch("j1_eta_A", &j1_eta_A);
    outTree->Branch("j2_eta_A", &j2_eta_A);
    outTree->Branch("j1_phi_A", &j1_phi_A);
    outTree->Branch("j2_phi_A", &j2_phi_A);
    outTree->Branch("t1_pt_A", &t1_pt_A);
    outTree->Branch("t2_pt_A", &t2_pt_A);
    outTree->Branch("t1_eta_A", &t1_eta_A);
    outTree->Branch("t2_eta_A", &t2_eta_A);
    outTree->Branch("t1_phi_A", &t1_phi_A);
    outTree->Branch("t2_phi_A", &t2_phi_A);
    outTree->Branch("mjj_A", &mjj_A);

    outTree->Branch("j3_pt_A", &j3_pt_A);
    outTree->Branch("j4_pt_A", &j4_pt_A);

    outTree->Branch("dRj1", &dRj1);
    outTree->Branch("dRj2", &dRj2);
    outTree->Branch("dRt1", &dRt1);
    outTree->Branch("dRt2", &dRt2);

    outTree->Branch("passSel", &passSel);
    outTree->Branch("passTrig", &passTrig);
    outTree->Branch("passNewTrig", &passNewTrig);
    outTree->Branch("passSelAndTrig", &passSelAndTrig);
    outTree->Branch("passSelAndNewTrig", &passSelAndNewTrig);
    outTree->Branch("matched", &matched);

    TH1F *h_cutflow = new TH1F("","",8,0,8);

    // Event Loop
    for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000 == 0) { std::cout << std::to_string(iEntry) << std::endl;}
	dRj1 = 999; //do something better, initializing like this can lead to errors
	dRj2 = 999; //maybe make a list of all dR for all pairs and select minim dR event
	dRt1 = 999;
	dRt2 = 999;

	passSel = 0;
	passTrig = 0;
	passSelAndTrig = 0;
	matched = 0;

	//tau selection:
	//2 taus
	//pt > 25 for both
	//fabs(eta) < 2.1 for both
	
	//fill cutflow before any selection
	h_cutflow->Fill(0.0,1.0);

	vecSizeAODTau = inTree->tauPt->size();
	if (vecSizeAODTau <= 1) continue;

	h_cutflow->Fill(1.0,1.0);

	t1_pt_A = inTree->tauPt->front();
	t2_pt_A = inTree->tauPt->at(1);
	if (t1_pt_A < 25 || t2_pt_A < 25) continue;

	h_cutflow->Fill(2.0,1.0);

	t1_eta_A = inTree->tauEta->front();
	t2_eta_A = inTree->tauEta->at(1);
	if (fabs(t1_eta_A) > 2.1 || fabs(t2_eta_A) > 2.1) continue;

	h_cutflow->Fill(3.0,1.0);

	//jet selection:
	//2 jets
	//leading pt > 120, subleading > 45
	//fabs(eta) < 4.7 for both
	vecSizeAODJet = inTree->jetPt->size();
	if (vecSizeAODJet <= 1) continue;

	h_cutflow->Fill(4.0,1.0);

	j1_pt_A = inTree->jetPt->front();
	j2_pt_A = inTree->jetPt->at(1);
	if (j1_pt_A < 120 || j2_pt_A < 45) continue;

	h_cutflow->Fill(5.0,1.0);

	j1_eta_A = inTree->jetEta->front();
	j2_eta_A = inTree->jetEta->at(1);
	if (fabs(j1_eta_A) > 4.7 || fabs(j2_eta_A) > 4.7) continue;

	h_cutflow->Fill(6.0,1.0);

	//if an event passes all selection, save its info in a TLorentzVector
	TLorentzVector tau1_A, tau2_A;
	tau1_A.SetPtEtaPhiE(t1_pt_A, t1_eta_A, inTree->tauPhi->front(), inTree->tauEnergy->front());
	tau2_A.SetPtEtaPhiE(t2_pt_A, t2_eta_A, inTree->tauPhi->at(1), inTree->tauEnergy->at(1));
	TLorentzVector jet1_A, jet2_A;
	jet1_A.SetPtEtaPhiE(j1_pt_A, j1_eta_A, inTree->jetPhi->front(), inTree->jetEn->front());
	jet2_A.SetPtEtaPhiE(j2_pt_A, j2_eta_A, inTree->jetPhi->at(1), inTree->jetEn->front());
	
	//final cut on mjj
	mjj_A = (jet1_A + jet2_A).M();
	if (mjj_A < 700) continue;

	h_cutflow->Fill(7.0,1.0);

	//filling additional jets to see how soft they are
	if (vecSizeAODJet > 2) j3_pt_A = inTree->jetPt->at(2);
	if (vecSizeAODJet > 3) j4_pt_A = inTree->jetPt->at(3);

	//if an event passes selection, check to see if it passed the trigger as well
	passSel = 1;

	passTrig = inTree->passTrigBranch->front();
	//passNewTrig = inTree->passNewTrigBranch->front(); //uncomment when new trigger dataset is available

	if (passSel == 1 && passTrig == 1) passSelAndTrig = 1;
	//if (passSel == 1 && passNewTrig == 1) passSelAndNewTrig = 1;
	
	outTree->Fill();
/***
	vecSizeHpsTau = inTree->hltHpsDoublePFTau_pt->size();
	vecSizeVBFOne = inTree->hltMatchedVBFOne_pt->size();
	vecSizeVBFTwo = inTree->hltMatchedVBFTwo_pt->size(); 

	// if there aren't two taus, skip the event
	if (vecSizeHpsTau != 2) continue;
	
	t1_pt = inTree->hltHpsDoublePFTau_pt->at(0);
	t2_pt = inTree->hltHpsDoublePFTau_pt->at(1);
	t1_loc = 0;
	t2_loc = 1;

	if (t2_pt > t1_pt){
	     t1_pt = inTree->hltHpsDoublePFTau_pt->at(1);
	     t2_pt = inTree->hltHpsDoublePFTau_pt->at(0);
	     t1_loc = 1;
	     t2_loc = 0;
	}
	t1_eta = inTree->hltHpsDoublePFTau_eta->at(t1_loc);
	t1_phi = inTree->hltHpsDoublePFTau_phi->at(t1_loc);
	t1_energy = inTree->hltHpsDoublePFTau_energy->at(t1_loc);
	t2_eta = inTree->hltHpsDoublePFTau_eta->at(t2_loc);
	t2_phi = inTree->hltHpsDoublePFTau_phi->at(t2_loc);
	t2_energy = inTree->hltHpsDoublePFTau_energy->at(t2_loc);

	TLorentzVector tau1, tau2; //build these for later use in matching to AOD objects
	tau1.SetPtEtaPhiE(t1_pt, t1_eta, t1_phi, t1_energy);
	tau2.SetPtEtaPhiE(t2_pt, t2_eta, t2_phi, t2_energy);

	// if last filter is empty or second to last filter doesn't have 2 jets, skip event
	if (vecSizeVBFOne == 0 || vecSizeVBFTwo != 2) continue;

	// if there are 2 jets with pt > 115, make the greater pt jet j1_pt
	if (vecSizeVBFOne == 2){
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
	     j1_phi = inTree->hltMatchedVBFOne_phi->at(j1_loc);
	     j2_phi = inTree->hltMatchedVBFOne_phi->at(j2_loc);
	     j1_energy = inTree->hltMatchedVBFOne_energy->at(j1_loc);
	     j2_energy = inTree->hltMatchedVBFOne_energy->at(j2_loc);
	}
	// if there's 1 jet with pt > 115, make it the leading one. Subleading is in prior filter.
	if (vecSizeVBFOne == 1){
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
	     j1_phi = inTree->hltMatchedVBFOne_phi->at(j1_loc);
	     j2_phi = inTree->hltMatchedVBFTwo_phi->at(j2_loc);
	     j1_energy = inTree->hltMatchedVBFOne_energy->at(j1_loc);
	     j2_energy = inTree->hltMatchedVBFTwo_energy->at(j2_loc);
	}

	TLorentzVector jet1, jet2;
	jet1.SetPtEtaPhiE(j1_pt,j1_eta,j1_phi,j1_energy);
	jet2.SetPtEtaPhiE(j2_pt,j2_eta,j2_phi,j2_energy);
	
	//now try to match to MiniAOD object


	outTree->Fill();
***/
    } // end event loop

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();
    h_cutflow->SetName("Cutflow");
    h_cutflow->Write();
    outTree->Write();
    fOut->Close();
    return 0;
}
