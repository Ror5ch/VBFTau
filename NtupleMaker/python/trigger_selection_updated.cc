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
    std::string httTrigString = "htt";
    int triggerFlag = 3;
    if (whichTrigger.find(oldTrigString) == std::string::npos && 
	whichTrigger.find(newTrigString) == std::string::npos &&
	whichTrigger.find(httTrigString) == std::string::npos) {
	std::cout << "specify whether this is the new trigger or the old trigger or htt selection with \"old\" or \"new\" or \"htt\" as the 3rd argument" << std::endl;
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
    if ( whichTrigger.find(httTrigString) != std::string::npos){
	t1_pt_cut = 20;
	t2_pt_cut = 20;
	j1_pt_cut = 35;
	j2_pt_cut = 35;
	mjj_cut = 350;
	triggerFlag = 2; // not functional currently due to if statements in trigger object filling logic
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

    std::vector<TLorentzVector> triggerTauCandidates;
    std::vector<TLorentzVector> triggerJetCandidates;

    std::vector<TLorentzVector> tauCandidates;
    std::vector<TLorentzVector> tauTempCandidates;
    std::vector<TLorentzVector> jetCandidates;
    std::vector<TLorentzVector> jetTempCandidates;
    float mjjCandidatePair;
    std::vector<std::pair<int,int>> jetCandsLocs; // jet candidate locations
    std::vector<float> dRj1_vec; // container for dR of AOD and HLT j1
    std::vector<float> dRj2_vec;
    std::vector<float> dRjSum;

    // flag vars
    int passMinimalSel;
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
    outTree->Branch("passMinimalSel", &passMinimalSel);
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
    for (int iEntry = 0; iEntry < 50000; iEntry++) {
    //for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000 == 0) { std::cout << std::to_string(iEntry) << std::endl;}
	
	passMinimalSel = 0;
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
	tauTempCandidates.clear();
	jetCandidates.clear(); // all for matching jets later
	jetTempCandidates.clear();
	jetCandsLocs.clear();
	dRt1 = 999;
	dRt2 = 999;
	dRj1 = 999;
	dRj2 = 999;
	dRj1_vec.clear();
	dRj2_vec.clear();
	dRjSum.clear();

	triggerTauCandidates.clear();
	triggerJetCandidates.clear();

	//----------------------------------------------------------//
	h_cutflow->Fill(0.0,1.0); // fill cutflow before any selection

	vecSizeAODTau = inTree->tauPt->size(); // number of taus in event
	vecSizeAODJet = inTree->jetPt->size(); // number of jets in event
	//minimal selection common to both triggers//
	// check the number of objects in the event, need at least two of each
	if (vecSizeAODTau < 2) continue;
	if (vecSizeAODJet < 2) continue;
	h_cutflow->Fill(1.0,1.0); // fill cutflow with events that have 2 taus and 2 jets
	// check kinematics and ID of tau objects, store good taus
	for (int iTau = 0; iTau < vecSizeAODTau; iTau++){

	    deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
	    deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
            deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
	    if (!deepTauVSjet || !deepTauVSmu || !deepTauVSele) continue;

	    if ( inTree->tauPt->at(iTau) < 20 ) continue;
	    if ( inTree->tauEta->at(iTau) > 2.1 ) continue;
	    TLorentzVector tauCandTemp;
	    tauCandTemp.SetPtEtaPhiE(inTree->tauPt->at(iTau),
				     inTree->tauEta->at(iTau), 
				     inTree->tauPhi->at(iTau), 
				     inTree->tauEnergy->at(iTau));

	    tauTempCandidates.push_back(tauCandTemp);
	}
	// continues inside for-loops don't skip the events, so you need to check the size of
	// the container you skipped adding events to and then impose a condition on that instead
	// check that we have at least 2 good taus
	if (tauTempCandidates.size() < 2) continue;
	h_cutflow->Fill(2.0,1.0); // fill cutflow with events that have 2 or more good taus

	// check kinematics and ID of jet objects, store good jets
	for (int iJet = 0; iJet < vecSizeAODJet; iJet++){

	    if (inTree->jetID->at(iJet) < 6) continue; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

	    if (inTree->jetPt->at(iJet) < 35) continue;
	    if (fabs(inTree->jetEta->at(iJet) > 4.7)) continue;
	    TLorentzVector jetCandTemp;
	    jetCandTemp.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
				     inTree->jetEta->at(iJet), 
				     inTree->jetPhi->at(iJet), 
				     inTree->jetEn->at(iJet));
	    // if a jetCandidate looks like it could be a tau, don't store it
	    bool jetCandIsTau = false;
	    for (int iTau = 0; iTau < tauCandidates.size(); iTau++){
		if (tauTempCandidates.at(iTau).DeltaR(jetCandTemp) < 0.5) jetCandIsTau = true;
	    }
	    if (!jetCandIsTau) jetTempCandidates.push_back(jetCandTemp);
	}
	// check taht we have at least two good taus
	if (jetTempCandidates.size() < 2) continue;
	h_cutflow->Fill(3.0,1.0); // fill cutflow with events that have 2 or more good jets

	passMinimalSel = 1;

	
	vecSizeAODTau = inTree->tauPt->size();

	if (vecSizeAODTau < 2) continue;

//	h_cutflow->Fill(1.0,1.0);

	// loop over all taus and store any that pass tauID and minimum kinematic selection
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
	if (tauCandidates.size() < 2) continue;

//	h_cutflow->Fill(2.0,1.0);

	// check leading tau kinematics for new trigger
	// not checked for old trigger because then t1_pt_cut = t2_pt_cut 
	if (triggerFlag == 1) {
	    bool tauOverLC = false; // LC = Leading Cut, 55 in the case of the new trigger leading tau
	    for (int iTau = 0; iTau < tauCandidates.size(); iTau++){
	    	if (tauCandidates.at(iTau).Pt() > t1_pt_cut) tauOverLC = true;
	    }
	    if (!tauOverLC) continue;
	}

//	h_cutflow->Fill(3.0,1.0);

	// need at least two jets in the event	
	vecSizeAODJet = inTree->jetPt->size();
	if (vecSizeAODJet < 2) continue;
	
	h_cutflow->Fill(4.0,1.0);

	// put jets into a vector, and from that vector of jetCandidates, make dijet pairs to cut on dijet mass
	for (int iJet = 0; iJet < vecSizeAODJet; iJet++){
	    // these cuts make it so that a list of 11 jets, of which some have pt < 40,
	    // aren't filled into the jet candidates.
	    if (inTree->jetID->at(iJet) < 6) continue; // jetID is 2 if it passes loose, and 6 if it passes loose and tight
	    if (inTree->jetPt->at(iJet) < j2_pt_cut) continue;
	    if (fabs(inTree->jetEta->at(iJet) > 4.7)) continue;
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
	if (jetCandidates.size() < 2) continue;

	h_cutflow->Fill(5.0,1.0);

	// check leading jet kinematics for old trigger
	// not checked for new trigger because then j1_pt_cut = j2_pt_cut 
	if (triggerFlag == 0){
	    bool jetOverLC = false; // LC = Leading Cut, 120GeV in case of old tau trigger
	    for (int iJet = 0; iJet < jetCandidates.size(); iJet++){
		if (jetCandidates.at(iJet).Pt() > j1_pt_cut) jetOverLC = true;
	    }
	    if (!jetOverLC) continue;
	}

	// mjj cut off for old trigger is 650
	// 	      for new trigger is 500
	// offline mjj cuts are 50GeV higher than trigger/HLT
	/***
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
	***/
	h_cutflow->Fill(6.0,1.0); // prev 2 for-loops serve as the mjj cut

	passSel = 1; 

	// as keti proposed, take leading two AOD taus
	// tauCandidates are already ordered by pt (this was checked with simple cout statements)
	TLorentzVector aodTau1, aodTau2;
	aodTau1.SetPtEtaPhiE(tauCandidates.at(0).Pt(), tauCandidates.at(0).Eta(), tauCandidates.at(0).Phi(), tauCandidates.at(0).Energy());
	aodTau2.SetPtEtaPhiE(tauCandidates.at(1).Pt(), tauCandidates.at(1).Eta(), tauCandidates.at(1).Phi(), tauCandidates.at(1).Energy());

	// any event that makes it here has passed AOD selection
	// next is to check if the event passed the trigger AND if it can be matched to AOD
	
	//--------------------------------------------------------------------------------//
	
	// get number of objects in tau and jet trigger filters
	vecSizeHpsTau = inTree->hltHpsDoublePFTauTight_pt->size(); // at least two taus > 20 GeV filter, common to both
	vecSizeVBFTwo = inTree->hltMatchedVBFTwoTight_pt->size();  // at least two jets > 45 GeV filter, old trigger
	vecSizeVBFOne = inTree->hltMatchedVBFOneTight_pt->size();  // one jet > 115 GeV filter, old trigger
	vecSizeVBFIsoTauTwo = inTree->hltMatchedVBFIsoTauTwoTight_pt->size(); // at least two jets > 45 GeV filter and iso tau present, new trigger
	vecSizeHpsTau50 = inTree->hltHpsPFTau50Tight_pt->size(); // at least one tau > 50 GeV filter, new trigger

	TLorentzVector trigTau1, trigTau2, trigJet1, trigJet2, aodJet1, aodJet2;
	if (vecSizeHpsTau >= 2 && ((vecSizeVBFTwo >= 2 && vecSizeVBFOne >= 1 && triggerFlag == 0) 
				|| (vecSizeVBFIsoTauTwo >= 2 && vecSizeHpsTau50 >= 1 && triggerFlag == 1))  ){
	    // fill trigger tau candidates for either trigger from 20 GeV tau filter
	    for (int iTriggerTau = 0; iTriggerTau < vecSizeHpsTau; iTriggerTau++){
		TLorentzVector triggerTauCand;
		triggerTauCand.SetPtEtaPhiE(inTree->hltHpsDoublePFTauTight_pt->at(iTriggerTau),
					    inTree->hltHpsDoublePFTauTight_eta->at(iTriggerTau),
					    inTree->hltHpsDoublePFTauTight_phi->at(iTriggerTau),
					    inTree->hltHpsDoublePFTauTight_energy->at(iTriggerTau));
		triggerTauCandidates.push_back(triggerTauCand);
	    }
	    TLorentzVector triggerJetCand;
	    // fill trigger jet candidates for old trigger
	    if (vecSizeVBFTwo >= 2 && vecSizeVBFOne >= 1 && triggerFlag == 0) {
		for (int iTriggerJet = 0; iTriggerJet < vecSizeVBFTwo; iTriggerJet++){
		    triggerJetCand.SetPtEtaPhiE(inTree->hltMatchedVBFIsoTauTwoTight_pt->at(iTriggerJet),
						inTree->hltMatchedVBFIsoTauTwoTight_eta->at(iTriggerJet),
	    					inTree->hltMatchedVBFIsoTauTwoTight_phi->at(iTriggerJet),
	    					inTree->hltMatchedVBFIsoTauTwoTight_energy->at(iTriggerJet));
		    triggerJetCandidates.push_back(triggerJetCand);
		}
	    }
	    // fill trigger jet candidates for new trigger
	    if (vecSizeVBFIsoTauTwo >= 2 && vecSizeHpsTau50 >= 1 && triggerFlag == 1) {
		for (int iTriggerJet = 0; iTriggerJet < vecSizeVBFIsoTauTwo; iTriggerJet++){
		    triggerJetCand.SetPtEtaPhiE(inTree->hltMatchedVBFIsoTauTwoTight_pt->at(iTriggerJet),
						inTree->hltMatchedVBFIsoTauTwoTight_eta->at(iTriggerJet),
	    					inTree->hltMatchedVBFIsoTauTwoTight_phi->at(iTriggerJet),
	    					inTree->hltMatchedVBFIsoTauTwoTight_energy->at(iTriggerJet));
		    triggerJetCandidates.push_back(triggerJetCand);
		}
	    }
	    // match AOD and HLT taus
	    int leadingTauIndex = -1;
	    int subleadingTauIndex = -1;
	    float dRt1_ = 999; // temp variables
	    float dRt2_ = 999;
	    //TLorentzVector trigTau1, trigTau2;
   	    // loop over HLT taus once to match to leading tau
	    // save the index, then set trigTau1 to that tau from list of triggerTauCandidates
	    // then erase that tau from the list and loop again to find subleading tau
	    for (int iTriggerTauCand = 0; iTriggerTauCand < triggerTauCandidates.size(); iTriggerTauCand++){
		dRt1_ = aodTau1.DeltaR(triggerTauCandidates.at(iTriggerTauCand));
		if (dRt1_ < dRt1){ dRt1 = dRt1_; leadingTauIndex = iTriggerTauCand;}
	    }
	    trigTau1 = triggerTauCandidates.at(leadingTauIndex); 
	    // have to use .begin() function because .erase() takes an iterator as an argument, not a regular integer
	    triggerTauCandidates.erase(triggerTauCandidates.begin() + leadingTauIndex);
	    for (int iTriggerTauCand = 0; iTriggerTauCand < triggerTauCandidates.size(); iTriggerTauCand++){
		dRt2_ = aodTau2.DeltaR(triggerTauCandidates.at(iTriggerTauCand));
		if (dRt2_ < dRt2){ dRt2 = dRt2_; subleadingTauIndex = iTriggerTauCand;}
	    }
	    trigTau2 = triggerTauCandidates.at(subleadingTauIndex);

	    // match AOD and HLT jets
	    // this could be written more efficiently
	    // we could find all dRs once, and pick the lowest two, then check mjj
	    // we can check mjj after because if the dRs aren't low enough for AOD and HLT to match
	    // then the mjj value doesn't matter
	    // this is related to the check Keti/Kyungwook asked me to perform 
	    // check performance between matching first then enforcing selection and selection first then matching
	    int leadingTrigJetIndex = -1;
	    int subleadingTrigJetIndex = -1;
	    int leadingAODJetIndex = -1;
	    int subleadingAODJetIndex = -1;
	    float dRj1_ = 999;
	    float dRj2_ = 999;
	    //TLorentzVector trigJet1, trigJet2, aodJet1, aodJet2;
	    //std::cout << "start debug" << std::endl;
	    for (int iTriggerJetCand = 0; iTriggerJetCand < triggerJetCandidates.size(); iTriggerJetCand++){
	    	for (int iJetCand = 0; iJetCand < jetCandidates.size(); iJetCand++){
		    //std::cout << "triggerJet: " << iTriggerJetCand << " aodJet: " << iJetCand << std::endl;
		    dRj1_ = jetCandidates.at(iJetCand).DeltaR(triggerJetCandidates.at(iTriggerJetCand));
		    //std::cout << "dRj1_: " << dRj1_ << std::endl;
		    if (dRj1_ < dRj1){ dRj1 = dRj1_; leadingTrigJetIndex = iTriggerJetCand; leadingAODJetIndex = iJetCand;}
		    //std::cout << "triggerJet: " << iTriggerJetCand << " leadingTrigJetIndex: " << leadingTrigJetIndex << std::endl;
		}
	    }
	    trigJet1 = triggerJetCandidates.at(leadingTrigJetIndex);
	    //std::cout << "jetCands size before erase: " << triggerJetCandidates.size() << std::endl;
	    triggerJetCandidates.erase(triggerJetCandidates.begin() + leadingTrigJetIndex);
	    //std::cout << "jetCands size after erase: " << triggerJetCandidates.size() << std::endl;
	    aodJet1 = jetCandidates.at(leadingAODJetIndex);
	    jetCandidates.erase(jetCandidates.begin() + leadingAODJetIndex);
	    for (int iTriggerJetCand = 0; iTriggerJetCand < triggerJetCandidates.size(); iTriggerJetCand++){
		for (int iJetCand = 0; iJetCand < jetCandidates.size(); iJetCand++){
		    //std::cout << "triggerJet: " << iTriggerJetCand << " aodJet: " << iJetCand << std::endl;
		    dRj2_ = jetCandidates.at(iJetCand).DeltaR(triggerJetCandidates.at(iTriggerJetCand));
		    //std::cout << "dRj2_: " << dRj2_ << std::endl;
		    if (dRj2_ < dRj2){ dRj2 = dRj2_; subleadingTrigJetIndex = iTriggerJetCand; subleadingAODJetIndex = iJetCand;}
		    //std::cout << "triggerJet: " << iTriggerJetCand << " subleadingTrigJetIndex: " << subleadingJetIndex << std::endl;
		}
	    }
	    trigJet2 = triggerJetCandidates.at(subleadingTrigJetIndex);
	    aodJet2 = jetCandidates.at(subleadingAODJetIndex);
	    mjj = (trigJet1 + trigJet2).M();
	    mjj_A = (aodJet1 + aodJet2).M();
	    //std::cout << "mjj: " << mjj << std::endl;
	    //std::cout << "end debug" << std::endl;
	}

	passOldTrig = inTree->passOldTrigTight->at(0);
	passNewTrig = inTree->passNewTrigTight->at(0);

	if (passSel == 1 && passOldTrig == 1 && triggerFlag == 0) passSelAndOldTrig = 1; // triggerFlag == 0 indicates old trigger is used
	if (passSel == 1 && passNewTrig == 1 && triggerFlag == 1) passSelAndNewTrig = 1; // triggerFlag == 1 indicates new trigger is used
/***
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
***/
	// if all the dRs are less than 0.5, then we've matched AOD to reco HLT
	// don't use continue because we don't want to lose objects that didn't match but still passed selection
	if (dRt1 < 0.5 && dRt2 < 0.5) matchedTaus = 1;
	if (dRj1 < 0.5 && dRj2 < 0.5) matchedJets = 1;
	if (matchedTaus && matchedJets) matchedBoth = 1;
        // fill kine branches with matched AOD info
        if (matchedBoth){
	    t1_pt_A = aodTau1.Pt();
	    t1_eta_A = aodTau1.Eta();
	    t1_phi_A = aodTau1.Phi();
	    t1_energy_A = aodTau1.Energy();
	    t2_pt_A = aodTau2.Pt();
	    t2_eta_A = aodTau2.Eta();
	    t2_phi_A = aodTau2.Phi();
	    t2_energy_A = aodTau2.Energy();
/***
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
***/
	    j1_pt_A = aodJet1.Pt();
	}

	if (matchedTaus && passSelAndOldTrig) passSelOldTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndOldTrig) passSelOldTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndOldTrig) passSelOldTrigAndMatchedBoth = 1;
	if (matchedTaus && passSelAndNewTrig) passSelNewTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndNewTrig) passSelNewTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndNewTrig) passSelNewTrigAndMatchedBoth = 1;
//	if (savedindex > 0) overOneAfterMatchingCounter += 1;

        outTree->Fill();
    }// end event loop

    std::cout << "overOneCounter: " << overOneCounter <<std::endl;
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
