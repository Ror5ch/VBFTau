#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility> 	//?
#include <map> 		//?
#include <string>
//#include <vector>

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

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root new

// simpleMatching
// inputs:
// vector of TLorentzVectors, representing objects passing trigger
// TLorentzVector, representing aod object to be matched
// output:
// integer representing location of object with lowest dR between trigger objs in container and given aod object
int simpleMatching(std::vector<TLorentzVector> trigContainer, TLorentzVector aodObj){
    int bestObjIndex = -1;
    float dRObj = 999;
    float dRObj_ = 999;
    for (int iTrigObj = 0; iTrigObj < trigContainer.size(); iTrigObj++){
	dRObj_ = aodObj.DeltaR(trigContainer.at(iTrigObj));
	if (dRObj_ < dRObj) {dRObj = dRObj_; bestObjIndex = iTrigObj;}
    }
    return bestObjIndex;
}

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

    // vars for AOD selection, which change depending on the trigger being studied
    float t1_pt_cut, t2_pt_cut;
    float j1_pt_cut, j2_pt_cut;
    float mjj_cut;

    std::string whichTrigger = *(argv + 3);
    std::string oldTrigString = "old";
    std::string newTrigString = "new";
/***
    int triggerFlag = 2;
    if (whichTrigger.find(oldTrigString) == std::string::npos && 
	whichTrigger.find(newTrigString) == std::string::npos) {
	std::cout << "specify whether this is the new trigger or the old trigger or htt selection with \"old\" or \"new\" or \"and\" as the 3rd argument" << std::endl;
	return 0; //prevents rest of code from running
    }
    // offline selection should be consistently 5 GeV above HLT thresholds
    if ( whichTrigger.find(oldTrigString) != std::string::npos){
	t1_pt_cut = 80;//25;
	t2_pt_cut = 25;
	j1_pt_cut = 120;
	j2_pt_cut = 45;
	mjj_cut = 700;
	std::cout << "trigger: " << oldTrigString << std::endl;
	triggerFlag = 0;
    }
    if ( whichTrigger.find(newTrigString) != std::string::npos){
	t1_pt_cut = 80;//55;
	t2_pt_cut = 25;
	j1_pt_cut = 120;//45;
	j2_pt_cut = 45;
	mjj_cut = 700;//550;
	std::cout << "trigger: " << newTrigString << std::endl;
	triggerFlag = 1;
    }
***/
    float minimal_tau_pt_cut = 20;
    float minimal_jet_pt_cut = 35;

    // hlt vars
    int vecSizeHpsTau;
    int vecSizeVBFOne;
    int vecSizeVBFTwo;
    int vecSizeVBFIsoTauTwo;
    int vecSizeHpsTau50;
    
    float j1_pt, j1_eta, j1_phi, j1_energy; 
    float j2_pt, j2_eta, j2_phi, j2_energy; 
    float mjj;

    float t1_pt, t1_eta, t1_phi, t1_energy;
    float t2_pt, t2_eta, t2_phi, t2_energy;
   
    // AOD vars 
    int vecSizeAODJet;
    int vecSizeAODTau;

    // A is for AOD
    float j1_pt_A, j1_eta_A, j1_phi_A, j1_energy_A; 
    float j2_pt_A, j2_eta_A, j2_phi_A, j2_energy_A; 
    float mjj_A;

    float t1_pt_A, t1_eta_A, t1_phi_A, t1_energy_A;
    float t2_pt_A, t2_eta_A, t2_phi_A, t2_energy_A;

    int deepTauVSjet, deepTauVSmu, deepTauVSele;
    int jetID;

    // vars for matching
    float dRj1, dRj2, dRt1, dRt2;

    std::vector<TLorentzVector> tauCandidates, jetCandidates;
    std::vector<TLorentzVector> tauTempCandidates, jetTempCandidates;
    std::vector<TLorentzVector> triggerTauCandidates, triggerJetCandidates;
    std::vector<TLorentzVector> triggerJetTempCandidates;

    std::vector<float> mjjCandidates;
    std::vector<std::pair<int,int>> jetMjjPairs;

    float mjjCandidatePair;
    std::vector<std::pair<int,int>> jetCandsLocs; // jet candidate locations

    // offline filter eff cutflow flag vars
    int nEvents; 
    
    int passL1Old;
    int passhltHpsPFTauTrackOld;
    int passhltHpsDoublePFTauTightOld;
    int passhltHpsDoublePFTauAgainstMuonTightOld;
    int passhltMatchedVBFTwoTight;
    int passhltMatchedVBFOneTight;

    int passL1New;
    int passhltHpsPFTauTrackNew;
    int passhltHpsDoublePFTauTightNew;
    int passhltHpsDoublePFTauAgainstMuonTightNew;
    int passhltHpsPFTau50Tight;
    int passhltMatchedVBFIsoTauTwoTight;

    // normal offline flag vars
    int passBase;
    int passBaseAndOldTrig;
    int passBaseOldTrigAndMatchedTaus;
    int passBaseOldTrigAndMatchedJets;
    int passBaseOldTrigAndMatchedBoth;
    int passBaseAndNewTrig;
    int passBaseNewTrigAndMatchedTaus;
    int passBaseNewTrigAndMatchedJets;
    int passBaseNewTrigAndMatchedBoth;

    int passSel;
    int passOldTrig;
    int passNewTrig;
    int passSelAndOldTrig;
    int passSelAndNewTrig;
    int matchedTaus;
    int matchedJets;
    int matchedBoth;
    int passSelOldTrigAndMatchedTaus;
    int passSelOldTrigAndMatchedJets;
    int passSelOldTrigAndMatchedBoth;
    int passSelNewTrigAndMatchedTaus;
    int passSelNewTrigAndMatchedJets;
    int passSelNewTrigAndMatchedBoth;

    int overlapped;
    
    // filled data branches
    // hlt vars
    outTree->Branch("j1_pt", &j1_pt);
    outTree->Branch("j1_eta", &j1_eta);
    outTree->Branch("j1_phi", &j1_phi);
    outTree->Branch("j2_pt", &j2_pt);
    outTree->Branch("j2_eta", &j2_eta);
    outTree->Branch("j2_phi", &j2_phi);
    outTree->Branch("mjj", &mjj);
    outTree->Branch("t1_pt", &t1_pt);
    outTree->Branch("t1_eta", &t1_eta);
    outTree->Branch("t1_phi", &t1_phi);
    outTree->Branch("t2_pt", &t2_pt);
    outTree->Branch("t2_eta", &t2_eta);
    outTree->Branch("t2_phi", &t2_phi);
    // AOD vars
    outTree->Branch("j1_pt_A", &j1_pt_A);
    outTree->Branch("j1_eta_A", &j1_eta_A);
    outTree->Branch("j1_phi_A", &j1_phi_A);
    outTree->Branch("j2_pt_A", &j2_pt_A);
    outTree->Branch("j2_eta_A", &j2_eta_A);
    outTree->Branch("j2_phi_A", &j2_phi_A);
    outTree->Branch("mjj_A", &mjj_A);
    outTree->Branch("t1_pt_A", &t1_pt_A);
    outTree->Branch("t1_eta_A", &t1_eta_A);
    outTree->Branch("t1_phi_A", &t1_phi_A);
    outTree->Branch("t2_pt_A", &t2_pt_A);
    outTree->Branch("t2_eta_A", &t2_eta_A);
    outTree->Branch("t2_phi_A", &t2_phi_A);
    outTree->Branch("deepTauVSjet", &deepTauVSjet);
    outTree->Branch("deepTauVSmu", &deepTauVSmu);
    outTree->Branch("deepTauVSele", &deepTauVSele);
    // matched vars
    outTree->Branch("dRj1", &dRj1);
    outTree->Branch("dRj2", &dRj2);
    outTree->Branch("dRt1", &dRt1);
    outTree->Branch("dRt2", &dRt2);
    outTree->Branch("matchedTaus", &matchedTaus);
    outTree->Branch("matchedJets", &matchedJets);
    outTree->Branch("matchedBoth", &matchedBoth);
    // offline filter eff cutflow vars
    outTree->Branch("nEvents", &nEvents);
    // path for old trigger
    outTree->Branch("passL1Old", &passL1Old);
    outTree->Branch("passhltHpsPFTauTrackOld", &passhltHpsPFTauTrackOld);
    outTree->Branch("passhltHpsDoublePFTauTightOld", &passhltHpsDoublePFTauTightOld);
    outTree->Branch("passhltHpsDoublePFTauAgainstMuonTightOld", &passhltHpsDoublePFTauAgainstMuonTightOld);
    outTree->Branch("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    outTree->Branch("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);
    // path for new trigger
    outTree->Branch("passL1New", &passL1New);
    outTree->Branch("passhltHpsPFTauTrackNew", &passhltHpsPFTauTrackNew);
    outTree->Branch("passhltHpsDoublePFTauTightNew", &passhltHpsDoublePFTauTightNew);
    outTree->Branch("passhltHpsDoublePFTauAgainstMuonTightNew", &passhltHpsDoublePFTauAgainstMuonTightNew);
    outTree->Branch("passhltHpsPFTau50Tight", &passhltHpsPFTau50Tight);
    outTree->Branch("passhltMatchedVBFIsoTauTwoTight", &passhltMatchedVBFIsoTauTwoTight);

    // flag vars
    outTree->Branch("passBase", &passBase);
    outTree->Branch("passBaseAndOldTrig", &passBaseAndOldTrig);
    outTree->Branch("passBaseOldTrigAndMatchedTaus", &passBaseOldTrigAndMatchedTaus);
    outTree->Branch("passBaseOldTrigAndMatchedJets", &passBaseOldTrigAndMatchedJets);
    outTree->Branch("passBaseOldTrigAndMatchedBoth", &passBaseOldTrigAndMatchedBoth);
    outTree->Branch("passBaseAndNewTrig", &passBaseAndNewTrig);
    outTree->Branch("passBaseNewTrigAndMatchedTaus", &passBaseNewTrigAndMatchedTaus);
    outTree->Branch("passBaseNewTrigAndMatchedJets", &passBaseNewTrigAndMatchedJets);
    outTree->Branch("passBaseNewTrigAndMatchedBoth", &passBaseNewTrigAndMatchedBoth);
    outTree->Branch("passSel", &passSel);
    outTree->Branch("passOldTrig", &passOldTrig);
    outTree->Branch("passNewTrig", &passNewTrig);
    outTree->Branch("passSelAndOldTrig", &passSelAndOldTrig);
    outTree->Branch("passSelAndNewTrig", &passSelAndNewTrig);
    outTree->Branch("passSelOldTrigAndMatchedTaus", &passSelOldTrigAndMatchedTaus);
    outTree->Branch("passSelOldTrigAndMatchedJets", &passSelOldTrigAndMatchedJets);
    outTree->Branch("passSelOldTrigAndMatchedBoth", &passSelOldTrigAndMatchedBoth);
    outTree->Branch("passSelNewTrigAndMatchedTaus", &passSelNewTrigAndMatchedTaus);
    outTree->Branch("passSelNewTrigAndMatchedJets", &passSelNewTrigAndMatchedJets);
    outTree->Branch("passSelNewTrigAndMatchedBoth", &passSelNewTrigAndMatchedBoth);

    TH1F *min_cutflow = new TH1F("","",5,0,5);
    TH1F *sel_cutflow = new TH1F("","",7,0,7);

    nEvents = inTree->GetEntries();

    // Event Loop
    // for-loop of just 2000 events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 200000; iEntry++) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	// initialize all flags to zero
	// offline trigger filter cutflow efficiency flags	
	// old trigger path
	passL1Old = 0;
	passhltHpsPFTauTrackOld = 0;
        passhltHpsDoublePFTauTightOld = 0;
	passhltHpsDoublePFTauAgainstMuonTightOld = 0;
    	passhltMatchedVBFTwoTight = 0;
 	passhltMatchedVBFOneTight = 0;
	// new trigger path
	passL1New = 0;
	passhltHpsPFTauTrackNew = 0;
	passhltHpsDoublePFTauTightNew = 0;
	passhltHpsDoublePFTauAgainstMuonTightNew = 0;
	passhltHpsPFTau50Tight = 0;
	passhltMatchedVBFIsoTauTwoTight = 0; 
	
	// full selection + trigger firing + matching flags
	passOldTrig = 0;
	passNewTrig = 0;

	passOldTrig = inTree->passOldTrigTight->at(0);
	passNewTrig = inTree->passNewTrigTight->at(0);

/***
	if (passOldTrig && inTree->hltL1VBFDiJetOR_pt->size() < 4){
	std::cout << "-----------------------------" << std::endl;
	std::cout << "L1VBFDiJetOR: " << inTree->hltL1VBFDiJetOR_pt->size() << std::endl; // 3
	std::cout << "PFTauTrack: " << inTree->hltHpsPFTauTrack_pt->size() << std::endl; // 2
	std::cout << "DoublePFTauTrack: " << inTree->hltHpsDoublePFTauTight_pt->size() << std::endl; // 2
	std::cout << "DoublePFTauAgainstMuonTight: " << inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() << std::endl; // 2
	std::cout << "MatchedVBFTwoTight: " << inTree->hltMatchedVBFTwoTight_pt->size() << std::endl; // 2
	std::cout << "MatchedVBFOneTight: " << inTree->hltMatchedVBFOneTight_pt->size() << std::endl; // 1
	std::cout << "pass old trig: " << passOldTrig << std::endl;
	std::cout << "-----------------------------" << std::endl;
	}
***/

	// old trigger filter cutflow eff flags
//	if (passSel && triggerFlag == 0 && inTree->hltL1VBFDiJetOR_pt->size() >= 2) {
	if (inTree->hltL1VBFDiJetOR_pt->size() >= 2) { //triggerFlag == 0 && 
	    passL1Old = inTree->passhltL1VBFDiJetOR->at(0);
	}

	if (passL1Old && inTree->hltHpsPFTauTrack_pt->size() >= 2) {
	    passhltHpsPFTauTrackOld = inTree->passhltHpsPFTauTrack->at(0);
	}

	if (passhltHpsPFTauTrackOld && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauTightOld = inTree->passhltHpsDoublePFTauTight->at(0); 
	}

	if (passhltHpsDoublePFTauTightOld && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauAgainstMuonTightOld = inTree->passhltHpsDoublePFTauAgainstMuonTight->at(0);
	}

	if (passhltHpsDoublePFTauAgainstMuonTightOld && inTree->hltMatchedVBFTwoTight_pt->size() >= 2) {
	    passhltMatchedVBFTwoTight = inTree->passhltMatchedVBFTwoTight->at(0);
	}

	if (passhltMatchedVBFTwoTight && inTree->hltMatchedVBFOneTight_pt->size() >= 1) {
	    passhltMatchedVBFOneTight = inTree->passhltMatchedVBFOneTight->at(0);
	}

/***
	if (passNewTrig && inTree->hltL1VBFDiJetIsoTau_tauPt->size() >= 1 && inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2){
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "L1VBFDiJetIsoTau Tau#: " << inTree->hltL1VBFDiJetIsoTau_tauPt->size() << std::endl; // 1
	std::cout << "L1VBFDiJetIsoTau Jet#: " << inTree->hltL1VBFDiJetIsoTau_jetPt->size() << std::endl; // 2

	std::cout << "PFTauTrack: " << inTree->hltHpsPFTauTrack_pt->size() << std::endl; // 2
	std::cout << "DoublePFTauTrack: " << inTree->hltHpsDoublePFTauTight_pt->size() << std::endl; // 2
	std::cout << "DoublePFTauAgainstMuonTight: " << inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() << std::endl; // 1
	std::cout << "HpsPFTau50Tight: " << inTree->hltHpsPFTau50Tight_pt->size() << std::endl;
	std::cout << "MatchedVBFIsoTauTwoTight: " << inTree->hltMatchedVBFIsoTauTwoTight_pt->size() << std::endl; // 2
	std::cout << "pass new trig: " << passNewTrig << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;

	}
***/
	// new trigger filter cutflow eff flags
//	if (passSel && triggerFlag == 1 && inTree->hltL1VBFDiJetIsoTau_tauPt->size() >= 1
//					&& inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2) {
	if (inTree->hltL1VBFDiJetIsoTau_tauPt->size() >= 1 //triggerFlag == 1 && 
				&& inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2) {
	    passL1New = inTree->passhltL1VBFDiJetIsoTau->at(0);
	}

	if (passL1New && inTree->hltHpsPFTauTrack_pt->size() >= 2) {
	    passhltHpsPFTauTrackNew = inTree->passhltHpsPFTauTrack->at(0);
	}

	if (passhltHpsPFTauTrackNew && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauTightNew = inTree->passhltHpsDoublePFTauTight->at(0);
	}

	if (passhltHpsDoublePFTauTightNew && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauAgainstMuonTightNew = inTree->passhltHpsDoublePFTauAgainstMuonTight->at(0);
	}

	if (passhltHpsDoublePFTauAgainstMuonTightNew && inTree->hltHpsPFTau50Tight_pt->size() >= 1) {
	    passhltHpsPFTau50Tight = inTree->passhltHpsPFTau50Tight->at(0);
	}

	if (passhltHpsPFTau50Tight && inTree->hltMatchedVBFIsoTauTwoTight_pt->size() >= 2) {
	    passhltMatchedVBFIsoTauTwoTight = inTree->passhltMatchedVBFIsoTauTwoTight->at(0);
	}
/***
	if (passSel && (inTree->passhltMatchedVBFIsoTauTwoTight->size()>0 != inTree->passNewTrigTight->at(0))){
	    std::cout << "mismatch" << std::endl;
	    std::cout << "size MatchedVBFIsoTauTwoTight_pt: " << inTree->hltMatchedVBFIsoTauTwoTight_pt->size() << std::endl;
	}
***/
/***
//	if (passSel && (inTree->passhltMatchedVBFIsoTauTwoTight->size()>0 != inTree->passNewTrigTight->at(0))) {
//	    std::cout << "mismatch" << std::endl;
//	    std::cout << inTree->passhltMatchedVBFIsoTauTwoTight->size()  << std::endl;
// 	}
***/
        outTree->Fill();
    }// end event loop

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();
/***
    sel_cutflow->SetName("SelCutflow");
    sel_cutflow->Write();
***/

    outTree->Write();
    fOut->Close();
    return 0;
}
