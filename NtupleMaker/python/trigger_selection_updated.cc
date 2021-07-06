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

    // vars for AOD selection, which change depending on the trigger being studied
    float t1_pt_cut;
    float t2_pt_cut;
    float j1_pt_cut;
    float j2_pt_cut;
    float mjj_cut;
    std::string whichTrigger = *(argv + 3);
    std::string oldTrigString = "old";
    std::string newTrigString = "new";
    int triggerFlag = 2;
    if (whichTrigger.find(oldTrigString) == std::string::npos && whichTrigger.find(newTrigString) == std::string::npos) {
	std::cout << "specify whether this is the new trigger or the old trigger with \"old\" or \"new\" as the 3rd argument" << std::endl;
	return 0; //prevents rest of code from running
    }
    // offline selection should be consistently 5 GeV above HLT thresholds
    if ( whichTrigger.find(oldTrigString) != std::string::npos){
	t1_pt_cut = 25;
	t2_pt_cut = 25;
	j1_pt_cut = 120;
	j2_pt_cut = 45;
	mjj_cut = 700;
	std::cout << "trigger: " << oldTrigString << std::endl;
	triggerFlag = 0;
    }
    if ( whichTrigger.find(newTrigString) != std::string::npos){
	t1_pt_cut = 55;
	t2_pt_cut = 25;
	j1_pt_cut = 45;
	j2_pt_cut = 45;
	mjj_cut = 550;
	triggerFlag = 1;
    }

    // hlt vars
    int j1_loc; //jet1 location, either position 0 or 1 in the vector of jets
    int j2_loc; //other intermediate variables
    int t1_loc;
    int t2_loc;
    int vecSizeVBFOne;
    int vecSizeVBFTwo;
    int vecSizeHpsTau;
    int vecSizeVBFIsoTauTwo;
    int vecSizeHpsTau50;
    
    float j1_pt; // branch variables (eta, phi, energy are necessary for mjj calculation)
    float j1_eta;
    float j1_phi;
    float j1_energy;
    float j2_pt;
    float j2_eta;
    float j2_phi;
    float j2_energy;
    float mjj;

    float t1_pt;
    float t1_eta;
    float t1_phi;
    float t1_energy;
    float t2_pt;
    float t2_eta;
    float t2_phi;
    float t2_energy;
   
    // AOD vars 
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
    float mjj_A;

    float t1_pt_A;
    float t1_eta_A;
    float t1_phi_A;
    float t1_energy_A;
    float t2_pt_A;
    float t2_eta_A;
    float t2_phi_A;
    float t2_energy_A;

    int deepTauVSjet;
    int deepTauVSmu;
    int deepTauVSele;
    int jetID;

    // vars for matching
    float dRj1;
    float dRj2;
    float dRt1;
    float dRt2;

    std::vector<TLorentzVector> tauCandidates;
    std::vector<TLorentzVector> jetCandidates;
    float mjjCandidatePair;
    std::vector<std::pair<int,int>> jetCandsLocs; // jet candidate locations
    std::vector<float> dRj1_vec; // container for dR of AOD and HLT j1
    std::vector<float> dRj2_vec;
    std::vector<float> dRjSum;

    // flag vars
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
    // flag vars
    outTree->Branch("passSel", &passSel);
    outTree->Branch("passOldTrig", &passOldTrig);
    outTree->Branch("passNewTrig", &passNewTrig);
    outTree->Branch("passSelAndOldTrig", &passSelAndOldTrig);
    outTree->Branch("passSelAndNewTrig", &passSelAndNewTrig);
    outTree->Branch("matchedTaus", &matchedTaus);
    outTree->Branch("matchedJets", &matchedJets);
    outTree->Branch("matchedBoth", &matchedBoth);
    outTree->Branch("passSelOldTrigAndMatchedTaus", &passSelOldTrigAndMatchedTaus);
    outTree->Branch("passSelOldTrigAndMatchedJets", &passSelOldTrigAndMatchedJets);
    outTree->Branch("passSelOldTrigAndMatchedBoth", &passSelOldTrigAndMatchedBoth);
    outTree->Branch("passSelNewTrigAndMatchedTaus", &passSelNewTrigAndMatchedTaus);
    outTree->Branch("passSelNewTrigAndMatchedJets", &passSelNewTrigAndMatchedJets);
    outTree->Branch("passSelNewTrigAndMatchedBoth", &passSelNewTrigAndMatchedBoth);

    TH1F *h_cutflow = new TH1F("","",10,0,10);

    // ad hoc testing vars
    // answering how many nonleading jet objects are matched btwn hlt and AOD
    // it's on the order of 0.1%
    int overOneCounter = 0;
    int overOneAfterMatchingCounter = 0;

    // Event Loop
    // for-loop of just 2000 events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 5000; iEntry++) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000 == 0) { std::cout << std::to_string(iEntry) << std::endl;}
	
	passSel = 0;  // ints standing in as booleans for these flag variables
	passOldTrig = 0; // to tell if an event passed selection, trigger, etc.
	passNewTrig = 0;
	passSelAndOldTrig = 0;
	passSelAndNewTrig = 0;
	matchedTaus = 0;
	matchedJets = 0;
	matchedBoth = 0;
	passSelOldTrigAndMatchedTaus = 0;
	passSelOldTrigAndMatchedJets = 0;
	passSelOldTrigAndMatchedBoth = 0;
	passSelNewTrigAndMatchedTaus = 0;
	passSelNewTrigAndMatchedJets = 0;
	passSelNewTrigAndMatchedBoth = 0;

	tauCandidates.clear();	

	jetCandidates.clear(); // all for matching jets later
	jetCandsLocs.clear();
	dRt1 = 999;
	dRt2 = 999;
	dRj1 = 999;
	dRj2 = 999;
	dRj1_vec.clear();
	dRj2_vec.clear();
	dRjSum.clear();

	// tau selection for old trigger:
	// 2 taus
	// pt > 20 for both
	// fabs(eta) < 2.1 for both
	//		for new trigger:
	// 2 taus
	// 1 pt > 50, other pt > 20
	// fabs(eta) < 2.1 for both
	
	// fill cutflow before any selection
	h_cutflow->Fill(0.0,1.0);
	
	vecSizeAODTau = inTree->tauPt->size();

	if (vecSizeAODTau <= 1) continue;

	h_cutflow->Fill(1.0,1.0);

	// how the tauID was previously implemented. Changing this was the main increase in events passing selection

        //for (int iTau = 0; iTau < vecSizeAODTau; iTau++){
	     
	//deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(0) > 0.5 &&  inTree->tauByMediumDeepTau2017v2p1VSjet->at(1) > 0.5;
	//deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(0) > 0.5 &&  inTree->tauByVLooseDeepTau2017v2p1VSmu->at(1) > 0.5;
        //deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(0) > 0.5 &&  inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(1) > 0.5;
	
	//if (!deepTauVSjet || !deepTauVSmu || !deepTauVSele) continue;
	//}

	// loop over all taus and store any that pass tauID and minimum kinematic selection

	// noticed an error in the logic here for the new trigger:
	// there's no condition on t1_pt_cut, so many events pass new trigger selection that
	// actually shouldn't because a real pair of tau AODs should have 1 with leading pt >= 50GeV,
	// but this loop doesn't enforce that requirement.
	for (int iTau = 0; iTau < vecSizeAODTau; iTau++){

	    deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
	    deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
            deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
	    if (!deepTauVSjet || !deepTauVSmu || !deepTauVSele) continue;

	    if ( inTree->tauPt->at(iTau) < t2_pt_cut ) continue;
	    if ( inTree->tauEta->at(iTau) > 2.1 ) continue;
	    TLorentzVector tauCand;
	    tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau), inTree->tauEta->at(iTau), inTree->tauPhi->at(iTau), inTree->tauEnergy->at(iTau));
	    tauCandidates.push_back(tauCand);
	}

	// need two taus for the event to be valid
	// this entry in the cutflow is the same as the next in the case of the old trigger
	// for the new trigger, the next cutflow category should have fewer events due
	// to leading tau selection
	if (tauCandidates.size() <= 1) continue;

	h_cutflow->Fill(2.0,1.0);

	// check leading tau kinematics for new trigger
	if (triggerFlag == 1) {
	    bool tauOverLC = false; // LC = Leading Cut, 55 in the case of the new trigger leading tau
	    for (int iTau = 0; iTau < tauCandidates.size(); iTau++){
	    	if (tauCandidates.at(iTau).Pt() > t1_pt_cut) tauOverLC = true;
	    }
	    if (!tauOverLC) continue;
	}

	h_cutflow->Fill(3.0,1.0);

	// jet selection for old trigger:
	// 2 jets
	// leading pt > 115, subleading > 40
	// fabs(eta) < 4.7 for both
	//		for new trigger:
	// 2 jets
	// both pt > 40
	// fabs(eta) < 4.7 for both
	
	vecSizeAODJet = inTree->jetPt->size();
	if (vecSizeAODJet <= 1) continue;
	
	h_cutflow->Fill(4.0,1.0);

        // I put these cuts together for the leading jet because
	// the subleading jet(s) are also (essentially) together due to the way
	// I've constructed my for-loops and cutflows.
	//
	// put this higher selection after the more general one
	// do a for-loop like was done with taus
	//if (inTree->jetPt->at(0) < j1_pt_cut || fabs(inTree->jetEta->at(0)) > 4.7) continue;

	h_cutflow->Fill(5.0,1.0);
	// put all the jets that passed cuts up to here into a vector of jetCandidates
	// from jetCandidates, make dijet pairs to cut on dijet mass
	for (int iJet = 0; iJet < vecSizeAODJet; iJet++){
	    // these cuts make it so that a list of 11 jets, of which some have pt < 40,
	    // aren't filled into the jet candidates.
	    if (inTree->jetPt->at(iJet) < j2_pt_cut) continue;
	    if (fabs(inTree->jetEta->at(iJet) > 4.7)) continue;
	    if (inTree->jetID->at(iJet) < 6) continue; // jetID is 2 if it passes loose, and 6 if it passes loose and tight
	    TLorentzVector jetCand;
	    jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), inTree->jetEta->at(iJet), inTree->jetPhi->at(iJet), inTree->jetEn->at(iJet));
	    // if a jetCandidate looks like it could be a tau, don't store it
	    bool jetCandIsTau = false;
	    for (int iTau = 0; iTau < tauCandidates.size(); iTau++){
		if (tauCandidates.at(iTau).DeltaR(jetCand) < 0.5) jetCandIsTau = true;
	    }
	    if (!jetCandIsTau) jetCandidates.push_back(jetCand);
	}
	// continues inside for-loops don't skip the events, so you need to check the size of
	// the container you skipped adding events to and then impose a condition on that instead
	// before filling the cutflow	
	if (jetCandidates.size() < 2) continue;

	h_cutflow->Fill(6.0,1.0);

	if (triggerFlag == 0){
	    bool jetOverLC = false; // LC = Leading Cut, 120GeV in case of old tau trigger
	    for (int iJet = 0; iJet < jetCandidates.size(); iJet++){
		if (jetCandidates.at(iJet).Pt() > j1_pt_cut) jetOverLC = true;
	    }
	    if (!jetOverLC) continue;
	}

	// mjj cut off for old trigger is 650
	// 	      for new trigger is 500
	for (int iCand = 0; iCand < jetCandidates.size(); iCand++){
	    for (int jCand = 0; jCand < jetCandidates.size(); jCand++){
		if (iCand >= jCand) continue;

		// makes sure one jet has pt > 115 and the other has pt > 40 if it's the old trigger
		// harmless if it's the new trigger
		if ((jetCandidates.at(iCand).Pt()>j1_pt_cut && jetCandidates.at(jCand).Pt()>j2_pt_cut) || \
		    (jetCandidates.at(iCand).Pt()>j2_pt_cut && jetCandidates.at(jCand).Pt()>j1_pt_cut)){

		    mjjCandidatePair = (jetCandidates.at(iCand) + jetCandidates.at(jCand)).M();
		    if (mjjCandidatePair < mjj_cut) continue;

		    jetCandsLocs.push_back(std::make_pair(iCand,jCand));
		}// end if statement on jet pair pt
	    }// end inner for-loop
	}// end for-loop

	// if there isn't a viable dijet system, skip the event
	if (jetCandsLocs.size() < 1) continue;
        if (jetCandsLocs.size() > 1) overOneCounter += 1;

	h_cutflow->Fill(7.0,1.0); // prev 2 for-loops serve as the mjj cut

	passSel = 1; 
	// any event that makes it here has passed AOD selection
	// next is to check if the event passed the trigger AND if it can be matched to AOD

	// get number of objects in end tau and jet trigger filters
	vecSizeHpsTau = inTree->hltHpsDoublePFTauTight_pt->size();
	vecSizeVBFOne = inTree->hltMatchedVBFOneTight_pt->size();
	vecSizeVBFTwo = inTree->hltMatchedVBFTwoTight_pt->size();

	//std::cout << " OLD TRIGGER FILTER SIZES " << std::endl;
	//std::cout << "vecSizeHPSTau: " << inTree->hltHpsDoublePFTauTight_pt->size() << std::endl;
	//std::cout << "vecSizeVBFOne: " << inTree->hltMatchedVBFOneTight_pt->size() << std::endl;
	//std::cout << "vecSizeVBFTwo: " << inTree->hltMatchedVBFTwoTight_pt->size() << std::endl;

	if (triggerFlag == 0){
	// fill trigger info for taus if it's available
	    if (vecSizeHpsTau >= 2){
	
	        t1_pt = inTree->hltHpsDoublePFTauTight_pt->at(0);
		t1_loc = 0;
	        t2_pt = inTree->hltHpsDoublePFTauTight_pt->at(1);
	        t2_loc = 1;

	        if (t2_pt > t1_pt){
		    t1_pt = inTree->hltHpsDoublePFTauTight_pt->at(1);
		    t2_pt = inTree->hltHpsDoublePFTauTight_pt->at(0);
	     	    t1_loc = 1;
	     	    t2_loc = 0;
	        }

	        t1_eta = inTree->hltHpsDoublePFTauTight_eta->at(t1_loc);
	        t1_phi = inTree->hltHpsDoublePFTauTight_phi->at(t1_loc);
	        t1_energy = inTree->hltHpsDoublePFTauTight_energy->at(t1_loc);
	        t2_eta = inTree->hltHpsDoublePFTauTight_eta->at(t2_loc);
	        t2_phi = inTree->hltHpsDoublePFTauTight_phi->at(t2_loc);
	        t2_energy = inTree->hltHpsDoublePFTauTight_energy->at(t2_loc);
	    }


	// fill trigger info for jets if its available
            // if there are 2 jets, make the greater pt jet j1_pt
            if (vecSizeVBFOne == 2){
                j1_pt = inTree->hltMatchedVBFOneTight_pt->at(0);
                j1_loc = 0;
                j2_pt = inTree->hltMatchedVBFOneTight_pt->at(1);
                j2_loc = 1;
                if (j2_pt > j1_pt){
                    j1_pt = inTree->hltMatchedVBFOneTight_pt->at(1);
                    j1_loc = 1;
                    j2_pt = inTree->hltMatchedVBFOneTight_pt->at(0);
                    j2_loc = 0;
                }
                j1_eta = inTree->hltMatchedVBFOneTight_eta->at(j1_loc);
                j1_phi = inTree->hltMatchedVBFOneTight_phi->at(j1_loc);
                j1_energy = inTree->hltMatchedVBFOneTight_energy->at(j1_loc);
                j2_eta = inTree->hltMatchedVBFOneTight_eta->at(j2_loc);
                j2_phi = inTree->hltMatchedVBFOneTight_phi->at(j2_loc);
                j2_energy = inTree->hltMatchedVBFOneTight_energy->at(j2_loc);
            }
            // if there's 1 jet in VBFOne filter, make it the leading one. Subleading is in prior filter, VBFTwo.
            if (vecSizeVBFOne == 1){
                j1_pt = inTree->hltMatchedVBFOneTight_pt->at(0);
                j1_loc = 0;
                j2_pt = inTree->hltMatchedVBFTwoTight_pt->at(0);
                j2_loc = 0; 
                if (j1_pt == j2_pt) {
            	    j2_pt = inTree->hltMatchedVBFTwoTight_pt->at(1);
            	    j2_loc = 1;
                }
                j1_eta = inTree->hltMatchedVBFOneTight_eta->at(j1_loc);
                j1_phi = inTree->hltMatchedVBFOneTight_phi->at(j1_loc);
                j1_energy = inTree->hltMatchedVBFOneTight_energy->at(j1_loc);
                j2_eta = inTree->hltMatchedVBFTwoTight_eta->at(j2_loc);
                j2_phi = inTree->hltMatchedVBFTwoTight_phi->at(j2_loc);
                j2_energy = inTree->hltMatchedVBFTwoTight_energy->at(j2_loc);
            }
	} // end old trigger ifs

	vecSizeVBFIsoTauTwo = inTree->hltMatchedVBFIsoTauTwoTight_pt->size(); 
	vecSizeHpsTau50 = inTree->hltHpsPFTau50Tight_pt->size();

	//std::cout << " NEW TRIGGER FILTERS " << std::endl;
	//std::cout << "vecSizeVBFIsoTauTwo: " << inTree->hltMatchedVBFIsoTauTwoTight_pt->size() << std::endl;
	//std::cout << "vecSizeHpsTau50: " << inTree->hltHpsPFTau50Tight_pt->size() << std::endl;

	if (triggerFlag == 1){
	    TLorentzVector TrigTauCand;
	    for (int iTrigTau = 0; iTrigTau < vecSizeHpsTau50; iTrigTau++){
		t1_pt = inTree->hltHpsPFTau50Tight_pt->at(iTrigTau);
		t1_eta = inTree->hltHpsPFTau50Tight_eta->at(iTrigTau);
		t1_phi = inTree->hltHpsPFTau50Tight_phi->at(iTrigTau);
		t1_energy = inTree->hltHpsPFTau50Tight_energy->at(iTrigTau);
		TrigTauCand.SetPtEtaPhiE(t1_pt, t1_eta, t1_phi, t1_energy);	
	    } 
	// fill trigger info for taus if its available
	// if two taus pass the final tau filter, store both and
	// make the higher pt one the leader
	    if (vecSizeHpsTau50 >= 2){
		t1_pt = inTree->hltHpsPFTau50Tight_pt->at(0);
		t1_loc = 0;
		t2_pt = inTree->hltHpsPFTau50Tight_pt->at(1);
		t2_loc = 1;
		if (t2_pt > t1_pt){
		    t1_pt = inTree->hltHpsPFTau50Tight_pt->at(1);
		    t1_loc = 1;
		    t2_pt = inTree->hltHpsPFTau50Tight_pt->at(0);
		    t2_loc = 0;
		}
	 	t1_eta = inTree->hltHpsPFTau50Tight_eta->at(t1_loc);
		t1_phi = inTree->hltHpsPFTau50Tight_phi->at(t1_loc);
		t1_energy = inTree->hltHpsPFTau50Tight_energy->at(t1_loc);
	 	t2_eta = inTree->hltHpsPFTau50Tight_eta->at(t2_loc);
		t2_phi = inTree->hltHpsPFTau50Tight_phi->at(t2_loc);
		t2_energy = inTree->hltHpsPFTau50Tight_energy->at(t2_loc);
	    }
	// if one tau passes the final filter, store it and go to
	// the prev tau filter for the other tau. check if they're the
	// same tau (based on pt) and if they are get the next tau
	// from that prev filter
	    if (vecSizeHpsTau50 == 1){
		t1_pt = inTree->hltHpsPFTau50Tight_pt->at(0);
		t1_loc = 0;
		t2_pt = inTree->hltHpsDoublePFTauTight_pt->at(0);
		t2_loc = 0;
		if (t1_pt == t2_pt){
		    t2_pt = inTree->hltHpsDoublePFTauTight_pt->at(1);
		    t2_loc = 1;
		}
		t1_eta = inTree->hltHpsPFTau50Tight_eta->at(t1_loc);
		t1_phi = inTree->hltHpsPFTau50Tight_phi->at(t1_loc);
		t1_energy = inTree->hltHpsPFTau50Tight_energy->at(t1_loc);
		t2_eta = inTree->hltHpsDoublePFTauTight_eta->at(t2_loc);
		t2_phi = inTree->hltHpsDoublePFTauTight_phi->at(t2_loc);
		t2_energy = inTree->hltHpsDoublePFTauTight_energy->at(t2_loc);
	    }
	// if there are two jets in the final jet filter, set them to be the
	// jets we'll compare to AOD
	    if (vecSizeVBFIsoTauTwo == 2){
	    	j1_pt = inTree->hltMatchedVBFIsoTauTwoTight_pt->at(0);
		j1_loc = 0;
		j2_pt = inTree->hltMatchedVBFIsoTauTwoTight_pt->at(1);
		j2_loc = 1;
		if (j2_pt > j1_pt){
		    j1_pt = inTree->hltMatchedVBFIsoTauTwoTight_pt->at(1);
		    j1_loc = 1;
		    j2_pt = inTree->hltMatchedVBFIsoTauTwoTight_pt->at(0);
		    j2_loc = 0;
		}
		j1_eta = inTree->hltMatchedVBFIsoTauTwoTight_eta->at(j1_loc);
		j1_phi = inTree->hltMatchedVBFIsoTauTwoTight_phi->at(j1_loc);
		j1_energy = inTree->hltMatchedVBFIsoTauTwoTight_energy->at(j1_loc);
		j2_eta = inTree->hltMatchedVBFIsoTauTwoTight_eta->at(j2_loc);
		j2_phi = inTree->hltMatchedVBFIsoTauTwoTight_phi->at(j2_loc);
		j2_energy = inTree->hltMatchedVBFIsoTauTwoTight_energy->at(j2_loc);
	    }
	}
	// end new trigger ifs
	// now try to match to MiniAOD object if the event passed the trigger
	

	int leadingTauIndex = -1; // save tau indices for retrieving AOD kinematics later
	int subleadingTauIndex = -1;
        TLorentzVector tau1, tau2; 
	if (((vecSizeVBFOne == 1 || vecSizeVBFOne == 2) && triggerFlag == 0) || (vecSizeVBFIsoTauTwo >= 2 && triggerFlag == 1)){	
            tau1.SetPtEtaPhiE(t1_pt, t1_eta, t1_phi, t1_energy);
            tau2.SetPtEtaPhiE(t2_pt, t2_eta, t2_phi, t2_energy);
	    float dRt1_ = 999; // underscores on the ends of variable names usually indicates those are temp variables
	    float dRt2_ = 999;
	    for (int iTau = 0; iTau < tauCandidates.size(); iTau++){
		dRt1_ = tau1.DeltaR(tauCandidates.at(iTau));
		dRt2_ = tau2.DeltaR(tauCandidates.at(iTau));
		if (dRt1_ < dRt1 ){ dRt1 = dRt1_; leadingTauIndex = iTau;} // saves lower temp dR values to permanent dR variable
		if (dRt2_ < dRt2 ){ dRt2 = dRt2_; subleadingTauIndex = iTau;}
	    }
	}

        // if either of the if statements before triggered, then we have a dijet system from the trigger
	TLorentzVector jet1, jet2;
	if (((vecSizeVBFOne == 1 || vecSizeVBFOne == 2) && triggerFlag == 0) || (vecSizeVBFIsoTauTwo == 2 && triggerFlag == 1)){
	    jet1.SetPtEtaPhiE(j1_pt,j1_eta,j1_phi,j1_energy);
	    jet2.SetPtEtaPhiE(j2_pt,j2_eta,j2_phi,j2_energy);
	    mjj = (jet1 + jet2).M();
	}

	passOldTrig = inTree->passOldTrigTight->at(0);
	passNewTrig = inTree->passNewTrigTight->at(0);

	if (passSel == 1 && passOldTrig == 1 && triggerFlag == 0) passSelAndOldTrig = 1; // triggerFlag == 0 indicates old trigger is used
	if (passSel == 1 && passNewTrig == 1 && triggerFlag == 1) passSelAndNewTrig = 1; // triggerFlag == 1 indicates new trigger is used

	int savedindex = -1;	
	if (passOldTrig || passNewTrig){
	    
	    for (std::vector<std::pair<int,int>>::iterator it = jetCandsLocs.begin(); it != jetCandsLocs.end(); ++it){
	    	dRj1 = jet1.DeltaR(jetCandidates.at(it->first));
		dRj1_vec.push_back(dRj1);
	    	dRj2 = jet2.DeltaR(jetCandidates.at(it->second));
		dRj2_vec.push_back(dRj2);
		dRjSum.push_back(dRj1+dRj2);
	    }// end for-loop, fills possible dRj1s and dRj2s to vectors that are checked in the for-loop below
	
	    if (dRj1_vec.size() != 0 && dRj2_vec.size() != 0){
		int dRjSum_ = 999;
		for (int n = 0; n < dRjSum.size(); n++){
		    if (dRjSum[n] < dRjSum_){
			savedindex = n;
			dRjSum_ = dRjSum[n];
			dRj1 = dRj1_vec.at(n);
			dRj2 = dRj2_vec.at(n);
		    }
		}// end for-loop, finds min dR for both jets
	    }// end if, checks if vectors containing possible dRs are non-zero 	
	}// end if, sets dRj1 and 2

	// if all the dRs are less than 0.5, then we've matched AOD to reco HLT
	// don't use continue because we don't want to lose objects that didn't match but still passed selection
	if (dRt1 < 0.5 && dRt2 < 0.5) matchedTaus = 1;
	if (dRj1 < 0.5 && dRj2 < 0.5) matchedJets = 1;
	if (matchedTaus && matchedJets) matchedBoth = 1;
        // fill kine branches with matched AOD info
        if (matchedBoth){
	    t1_pt_A = tauCandidates.at(leadingTauIndex).Pt();
	    t1_eta_A = tauCandidates.at(leadingTauIndex).Eta();
	    t1_phi_A = tauCandidates.at(leadingTauIndex).Phi();
	    t1_energy_A = tauCandidates.at(leadingTauIndex).Energy();
	    t2_pt_A = tauCandidates.at(subleadingTauIndex).Pt();
	    t2_eta_A = tauCandidates.at(subleadingTauIndex).Eta();
	    t2_phi_A = tauCandidates.at(subleadingTauIndex).Phi();
	    t2_energy_A = tauCandidates.at(subleadingTauIndex).Energy();

	    std::pair<int,int> JPair = jetCandsLocs.at(savedindex);
	    j1_pt_A = jetCandidates.at(JPair.first).Pt();
	    j1_eta_A = jetCandidates.at(JPair.first).Eta();
	    j1_phi_A = jetCandidates.at(JPair.first).Phi();
	    j1_energy_A = jetCandidates.at(JPair.first).Energy();
	    j2_pt_A = jetCandidates.at(JPair.second).Pt();
	    j2_eta_A = jetCandidates.at(JPair.second).Eta();
	    j2_phi_A = jetCandidates.at(JPair.second).Phi();
	    j2_energy_A = jetCandidates.at(JPair.second).Energy();
	    mjj_A = (jetCandidates.at(JPair.first) + jetCandidates.at(JPair.second)).M();
	}

	if (matchedTaus && passSelAndOldTrig) passSelOldTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndOldTrig) passSelOldTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndOldTrig) passSelOldTrigAndMatchedBoth = 1;
	if (matchedTaus && passSelAndNewTrig) passSelNewTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndNewTrig) passSelNewTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndNewTrig) passSelNewTrigAndMatchedBoth = 1;
	if (savedindex > 0) overOneAfterMatchingCounter += 1;

        outTree->Fill();
    }// end event loop

    //std::cout << "overOneCounter: " << overOneCounter <<std::endl;
    //std::cout << "overOneAfterMatchingCounter: " << overOneAfterMatchingCounter << std::endl;

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();
    h_cutflow->SetName("Cutflow");
    h_cutflow->Write();
    outTree->Write();
    fOut->Close();
    return 0;
}
