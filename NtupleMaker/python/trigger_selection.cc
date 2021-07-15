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

    int sameTauPassSel = 0;
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
	
	// base selection flags (usually not checked anymore)
	passBase = 0;
	passBaseAndOldTrig = 0;
	passBaseOldTrigAndMatchedTaus = 0;	
	passBaseOldTrigAndMatchedJets = 0;	
	passBaseOldTrigAndMatchedBoth = 0;	
	passBaseAndNewTrig = 0;
	passBaseNewTrigAndMatchedTaus = 0;	
	passBaseNewTrigAndMatchedJets = 0;	
	passBaseNewTrigAndMatchedBoth = 0;	

	// full selection + trigger firing + matching flags
	passSel = 0;
	passOldTrig = 0;
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

	overlapped = 0;

	mjjCandidates.clear();
	jetMjjPairs.clear();
	tauCandidates.clear();	
	jetCandidates.clear();

	jetCandsLocs.clear();

	triggerTauCandidates.clear();
	triggerJetCandidates.clear();


	//---------------------apply minimal selection------------------------------//
	min_cutflow->Fill(0.0,1.0); // fill cutflow before any selection

	vecSizeAODTau = inTree->tauPt->size(); // number of taus in event
	vecSizeAODJet = inTree->jetPt->size(); // number of jets in event
	//minimal selection common to both triggers//
	// check the number of objects in the event, need at least two of each
	if (vecSizeAODTau < 2) continue;
	min_cutflow->Fill(1.0,1.0);
	if (vecSizeAODJet < 2) continue;
	min_cutflow->Fill(2.0,1.0); // fill cutflow with events that have 2 taus and 2 jets
	// check kinematics and ID of tau objects, store good taus
	for (int iTau = 0; iTau < vecSizeAODTau; iTau++){

	    deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
	    deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
            deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
	    if (!deepTauVSjet || !deepTauVSmu || !deepTauVSele) continue;

	    if ( inTree->tauPt->at(iTau) < minimal_tau_pt_cut ) continue;
	    if ( inTree->tauEta->at(iTau) > 2.1 ) continue;
	    TLorentzVector tauCand;
	    tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau),
				     inTree->tauEta->at(iTau), 
				     inTree->tauPhi->at(iTau), 
				     inTree->tauEnergy->at(iTau));

	    tauCandidates.push_back(tauCand);
	}


	// continues inside for-loops don't skip the events, so you need to check the size of
	// the container you skipped adding events to and then impose a condition on that instead
	// check that we have at least 2 good taus to work with
	if (tauCandidates.size() < 2) continue;

	// as keti proposed, take first two AOD taus that aren't overlapped
	// tauCandidates are already ordered by pt (this was checked with simple cout statements)
	TLorentzVector aodTau1, aodTau2;
	aodTau1.SetPtEtaPhiE(tauCandidates.at(0).Pt(), tauCandidates.at(0).Eta(), tauCandidates.at(0).Phi(), tauCandidates.at(0).Energy());
	for (int iTau = 1; iTau < tauCandidates.size(); iTau++){
	    aodTau2.SetPtEtaPhiE(tauCandidates.at(iTau).Pt(),
				 tauCandidates.at(iTau).Eta(),
				 tauCandidates.at(iTau).Phi(),
				 tauCandidates.at(iTau).Energy());
	    if (aodTau1.DeltaR(aodTau2) > 0.5) break; // if taus are not overlapped, leave the for loop
	}
	// check that the tau didn't make it all the way through the loop without breaking
	// I think this is unlikely but it's good to be redundant
	if (aodTau1.DeltaR(aodTau2) < 0.5) continue; 

	min_cutflow->Fill(3.0,1.0); // fill cutflow with events that have 2 or more good taus
	sel_cutflow->Fill(0.0,1.0); // start of smaller cutflow graph (keep two just for scaling purposes)

	// check kinematics and ID of jet objects, store good jets
	for (int iJet = 0; iJet < vecSizeAODJet; iJet++){

	    if (inTree->jetID->at(iJet) < 6) continue; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

	    if (inTree->jetPt->at(iJet) < minimal_jet_pt_cut) continue;
	    if (fabs(inTree->jetEta->at(iJet) > 4.7)) continue;
	    TLorentzVector jetCand;
	    jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
				     inTree->jetEta->at(iJet), 
				     inTree->jetPhi->at(iJet), 
				     inTree->jetEn->at(iJet));
	    // if a jetCandidate looks like it could be either tau we already selected, don't store it
	    bool jetCandIsTau = false;
	    if (aodTau1.DeltaR(jetCand) < 0.5) jetCandIsTau = true;
	    if (aodTau2.DeltaR(jetCand) < 0.5) jetCandIsTau = true;

	    if (!jetCandIsTau) jetCandidates.push_back(jetCand);
	}
	// check that we have at least two good jets
	if (jetCandidates.size() < 2) continue;

	// find mjj of all pairs of jets passing baseline selection, store the mjj values and pairs of jets that generated them
	// store index of largest mjj to retrieve pair of jets causing it later
	int highestMjjCandIndex = -1;
	float tempMjj = -1;
	for (int iJet = 0; iJet < jetCandidates.size(); iJet++){
	    for (int jJet = 0; jJet < jetCandidates.size(); jJet++){
		if (jJet>=iJet) continue;
		if (jetCandidates.at(iJet).DeltaR(jetCandidates.at(jJet)) > 0.5) {
		    mjj_A = (jetCandidates.at(iJet) + jetCandidates.at(jJet)).M();
		    mjjCandidates.push_back(mjj_A);
		    jetMjjPairs.push_back(std::make_pair(jJet,iJet));
		    if (mjj_A > tempMjj) {
		    	tempMjj = mjj_A; 
		    	highestMjjCandIndex = mjjCandidates.size() - 1; // assign most recent addition of mjjCand vector
		    }
		}
	    }
	}
	if (highestMjjCandIndex == -1) continue;


	// select the pair of jets that produced the largest mjj value
	// Most often the jet indices are 0 and 1, as we might expect
	// but it's not uncommon to see indices of 0 and 3, 1 and 2, or 0 and 2 as well
	std::pair<int,int> jetPair = jetMjjPairs.at(highestMjjCandIndex);

	// fill aodJets with the selected jets
	// from cout statements, aodJet1 was verified to be leading jet
	TLorentzVector aodJet1, aodJet2;
	aodJet1 = jetCandidates.at(jetPair.first);
	aodJet2 = jetCandidates.at(jetPair.second);


	// calculate mjj of AOD jets
	mjj_A = (aodJet1 + aodJet2).M();

	min_cutflow->Fill(4.0,1.0);
	sel_cutflow->Fill(1.0,1.0);

	passBase = 1;

	//-----------------------tighter selection guided by trigger specific cutoffs---------------//


	passSel = 1;

	if (aodTau1.Pt() < t2_pt_cut || aodTau2.Pt() < t2_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(5.0,1.0);}
	sel_cutflow->Fill(2.0,1.0);
	
	if (aodTau1.Pt() < t1_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(6.0,1.0);}
	sel_cutflow->Fill(3.0,1.0);

	if (aodJet1.Pt() < j2_pt_cut || aodJet2.Pt() < j2_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(7.0,1.0);}
	sel_cutflow->Fill(4.0,1.0);

	if (aodJet1.Pt() < j1_pt_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(8.0,1.0);}
	sel_cutflow->Fill(5.0,1.0);

	if (mjj_A < mjj_cut) passSel = 0; //continue;
	//else {sel_cutflow->Fill(9.0,1.0);}
	sel_cutflow->Fill(6.0,1.0);

	passSel = 1;

	//-----------------------try to match AOD and HLT objects-----------------------------------//
	
	// get number of objects in tau and jet trigger filters
	vecSizeHpsTau = inTree->hltHpsDoublePFTauTight_pt->size(); // at least two taus > 20 GeV filter, common to both
	vecSizeVBFTwo = inTree->hltMatchedVBFTwoTight_pt->size();  // at least two jets > 45 GeV filter, old trigger
	vecSizeVBFOne = inTree->hltMatchedVBFOneTight_pt->size();  // one jet > 115 GeV filter, old trigger
	vecSizeVBFIsoTauTwo = inTree->hltMatchedVBFIsoTauTwoTight_pt->size(); // at least two jets > 45 GeV filter and iso tau present, new trigger
	vecSizeHpsTau50 = inTree->hltHpsPFTau50Tight_pt->size(); // at least one tau > 50 GeV filter, new trigger

	TLorentzVector trigTau1, trigTau2, trigJet1, trigJet2;//, aodJet1, aodJet2;
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
		    triggerJetCand.SetPtEtaPhiE(inTree->hltMatchedVBFTwoTight_pt->at(iTriggerJet),
						inTree->hltMatchedVBFTwoTight_eta->at(iTriggerJet),
	    					inTree->hltMatchedVBFTwoTight_phi->at(iTriggerJet),
	    					inTree->hltMatchedVBFTwoTight_energy->at(iTriggerJet));
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

	    dRt1 = 999;
	    dRt2 = 999;
	    int leadingTauIndex = -1;
	    int subleadingTauIndex = -1;
	    // get leading tau index with simple matching
	    leadingTauIndex = simpleMatching(triggerTauCandidates, aodTau1);
	    trigTau1 = triggerTauCandidates.at(leadingTauIndex);
	    dRt1 = trigTau1.DeltaR(aodTau1);
	    // remove matched tau from trigger tau candidates
	    triggerTauCandidates.erase(triggerTauCandidates.begin() + leadingTauIndex);
	    // get subleading tau index with simple matching
	    subleadingTauIndex = simpleMatching(triggerTauCandidates, aodTau2);
	    //if (leadingTauIndex == subleadingTauIndex && passSel) sameTauPassSel += 1;//std::cout << "same tau partner" << std::endl;
	    trigTau2 = triggerTauCandidates.at(subleadingTauIndex);
	    dRt2 = trigTau2.DeltaR(aodTau2);

	    // match AOD and HLT jets	

	    dRj1 = 999;
	    dRj2 = 999;
	    int leadingJetIndex = -1;
	    int subleadingJetIndex = -1;
	    // get leading jet index with simple matching
	    leadingJetIndex = simpleMatching(triggerJetCandidates, aodJet1);
	    trigJet1 = triggerJetCandidates.at(leadingJetIndex);
	    dRj1 = trigJet1.DeltaR(aodJet1);
	    triggerJetTempCandidates = triggerJetCandidates;
	    // remove matched jet from trigger jet candidates
	    triggerJetCandidates.erase(triggerJetCandidates.begin() + leadingJetIndex);
	    // get subleading jet index with simple matching
	    subleadingJetIndex = simpleMatching(triggerJetCandidates, aodJet2);
	    trigJet2 = triggerJetCandidates.at(subleadingJetIndex);
	    dRj2 = trigJet2.DeltaR(aodJet2);

	    mjj = (trigJet1 + trigJet2).M();


	    // check that same type objects are not overlapped
	    if (trigTau1.DeltaR(trigTau2) < 0.5 || trigJet1.DeltaR(trigJet2) < 0.5 ) overlapped = 1;

	    // check that different objecs are not overlapped
	    if (trigTau1.DeltaR(trigJet1) < 0.5 || trigTau1.DeltaR(trigJet2) < 0.5 ||
		trigTau2.DeltaR(trigJet1) < 0.5 || trigTau2.DeltaR(trigJet2) < 0.5) overlapped = 1;
	}

	//------------------------------fill flags and output tree-----------------------------------//
	// passSel 
	// passBase alredy defined near start

	passOldTrig = inTree->passOldTrigTight->at(0);
	passNewTrig = inTree->passNewTrigTight->at(0);


	// old trigger filter cutflow eff flags
	if (passSel && triggerFlag == 0 && inTree->passhltL1VBFDiJetOR->size()>0) {
	    passL1Old = inTree->passhltL1VBFDiJetOR->at(0);
	}

	if (passL1Old && inTree->passhltHpsPFTauTrack->size()>0) {
	    passhltHpsPFTauTrackOld = inTree->passhltHpsPFTauTrack->at(0);
	}

	if (passhltHpsPFTauTrackOld && inTree->passhltHpsDoublePFTauTight->size()>0) {
	    passhltHpsDoublePFTauTightOld = inTree->passhltHpsDoublePFTauTight->at(0); 
	}

	if (passhltHpsDoublePFTauTightOld && inTree->passhltHpsDoublePFTauAgainstMuonTight->size()>0) {
	    passhltHpsDoublePFTauAgainstMuonTightOld = inTree->passhltHpsDoublePFTauAgainstMuonTight->at(0);
	}

	if (passhltHpsDoublePFTauAgainstMuonTightOld && inTree->passhltMatchedVBFTwoTight->size()>0) {
	    passhltMatchedVBFTwoTight = inTree->passhltMatchedVBFTwoTight->at(0);
	}

	if (passhltMatchedVBFTwoTight && inTree->passhltMatchedVBFOneTight->size()>0) {
	    passhltMatchedVBFOneTight = inTree->passhltMatchedVBFOneTight->at(0);
	}

	// new trigger filter cutflow eff flags
	if (passSel && triggerFlag == 1 && inTree->passhltL1VBFDiJetIsoTau->size()>0) {
	    passL1New = inTree->passhltL1VBFDiJetIsoTau->at(0);
	}

	if (passL1New && inTree->passhltHpsPFTauTrack->size()>0) {
	    passhltHpsPFTauTrackNew = inTree->passhltHpsPFTauTrack->at(0);
	}

	if (passhltHpsPFTauTrackNew && inTree->passhltHpsDoublePFTauTight->size()>0) {
	    passhltHpsDoublePFTauTightNew = inTree->passhltHpsDoublePFTauTight->at(0);
	}

	if (passhltHpsDoublePFTauTightNew && inTree->passhltHpsDoublePFTauAgainstMuonTight->size()>0) {
	    passhltHpsDoublePFTauAgainstMuonTightNew = inTree->passhltHpsDoublePFTauAgainstMuonTight->at(0);
	}

	if (passhltHpsDoublePFTauAgainstMuonTightNew && inTree->passhltHpsPFTau50Tight->size()>0) {
	    passhltHpsPFTau50Tight = inTree->passhltHpsPFTau50Tight->at(0);
	}

	if (passhltHpsPFTau50Tight && inTree->passhltMatchedVBFIsoTauTwoTight->size()>0) {
	    passhltMatchedVBFIsoTauTwoTight = inTree->passhltMatchedVBFIsoTauTwoTight->at(0);
	}

	// filling offline selection flags / pass trigger flags
	if (passBase && passOldTrig ) passBaseAndOldTrig = 1; // triggerFlag not necessary for base sel
	if (passBase && passNewTrig ) passBaseAndNewTrig = 1;

	if (passSel && passOldTrig && triggerFlag == 0) passSelAndOldTrig = 1;
	if (passSel && passNewTrig && triggerFlag == 1) passSelAndNewTrig = 1;

	// if all the dRs are less than 0.5, then we've matched AOD to reco HLT
	if (dRt1 < 0.5 && dRt2 < 0.5 && !overlapped) matchedTaus = 1;
	if (dRj1 < 0.5 && dRj2 < 0.5 && !overlapped) matchedJets = 1;
	if (matchedTaus && matchedJets) matchedBoth = 1;

	if (matchedTaus && passBaseAndOldTrig) passBaseOldTrigAndMatchedTaus = 1;
	if (matchedJets && passBaseAndOldTrig) passBaseOldTrigAndMatchedJets = 1;
	if (matchedBoth && passBaseAndOldTrig) passBaseOldTrigAndMatchedBoth = 1;

	if (matchedTaus && passBaseAndNewTrig) passBaseNewTrigAndMatchedTaus = 1;
	if (matchedJets && passBaseAndNewTrig) passBaseNewTrigAndMatchedJets = 1;
	if (matchedBoth && passBaseAndNewTrig) passBaseNewTrigAndMatchedBoth = 1;

	if (matchedTaus && passSelAndOldTrig) passSelOldTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndOldTrig) passSelOldTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndOldTrig) passSelOldTrigAndMatchedBoth = 1;

	if (matchedTaus && passSelAndNewTrig) passSelNewTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndNewTrig) passSelNewTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndNewTrig) passSelNewTrigAndMatchedBoth = 1;


        // fill kine branches with matched AOD
        if (passSel){
	    t1_pt_A = aodTau1.Pt();
	    t1_eta_A = aodTau1.Eta();
	    t1_phi_A = aodTau1.Phi();
	    t1_energy_A = aodTau1.Energy();
	    t2_pt_A = aodTau2.Pt();
	    t2_eta_A = aodTau2.Eta();
	    t2_phi_A = aodTau2.Phi();
	    t2_energy_A = aodTau2.Energy();

	    j1_pt_A = aodJet1.Pt();
	    j1_eta_A = aodJet1.Eta();
	    j1_eta_A = aodJet1.Phi();
	    j1_energy_A = aodJet1.Energy();
	    j2_pt_A = aodJet2.Pt();
	    j2_eta_A = aodJet2.Eta();
	    j2_eta_A = aodJet2.Phi();
	    j2_energy_A = aodJet2.Energy();
	}

        outTree->Fill();
    }// end event loop

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();

    min_cutflow->SetName("MinCutflow");
    min_cutflow->Write();
    sel_cutflow->SetName("SelCutflow");
    sel_cutflow->Write();



    outTree->Write();
    fOut->Close();
    return 0;
}
