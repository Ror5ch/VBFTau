#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <iomanip>

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
int simpleMatching(std::vector<TLorentzVector> trigContainer, TLorentzVector aodObj) {
    int bestObjIndex = -1;
    float dRObj = 999;
    float dRObj_ = 999;
    for (int iTrigObj = 0; iTrigObj < trigContainer.size(); ++iTrigObj){
	dRObj_ = aodObj.DeltaR(trigContainer.at(iTrigObj));
	if (dRObj_ < dRObj) {dRObj = dRObj_; bestObjIndex = iTrigObj;}
    }
    return bestObjIndex;
}

//debugging functions that print kinematic info
void coutAODobjs(TLorentzVector AODobj1, TLorentzVector AODobj2) {
    std::cout << "obj #" << '\t' << "pt" << '\t' << "eta" << '\t' << "phi" << std::endl;
    std::cout << "1      " << std::setprecision(4) << AODobj1.Pt() << '\t' << AODobj1.Eta() << '\t' << AODobj1.Phi() << std::endl;
    std::cout << "2      " << std::setprecision(4) << AODobj2.Pt() << '\t' << AODobj2.Eta() << '\t' << AODobj2.Phi() << std::endl;
}

void coutL1objs(std::vector<TLorentzVector> L1ObjContainer, std::vector<TLorentzVector> AODObjContainer) {
    // assume AODObjContainer is (aodJet1, aodJet2, aodTau1, aodTau2)
    std::cout << "obj #" << '\t' << "pt" << '\t' << "eta" << '\t' << "phi" <<\
    '\t' << "dR AODJet 1" << '\t' << "dR AODJet 2" << '\t' << "dR AODTau 1" << '\t' << "dR AODTau 2" << std::endl;
    TLorentzVector tempL1Obj;
    for (int iObj = 0; iObj < L1ObjContainer.size(); ++iObj) {
	tempL1Obj = L1ObjContainer.at(iObj);
	std::cout << iObj << '\t' << tempL1Obj.Pt() << '\t' << tempL1Obj.Eta() << '\t' << tempL1Obj.Phi() << '\t' \
		  << tempL1Obj.DeltaR(AODObjContainer.at(0)) << '\t' << '\t' << tempL1Obj.DeltaR(AODObjContainer.at(1)) << '\t' << '\t' \
		  << tempL1Obj.DeltaR(AODObjContainer.at(2)) << '\t' << '\t' << tempL1Obj.DeltaR(AODObjContainer.at(3)) << std::endl;
    }
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
	t1_pt_cut = 80;//50;//25;
	t2_pt_cut = 40;//25;
	j1_pt_cut = 120;
	j2_pt_cut = 45;
	mjj_cut = 700;
	std::cout << "trigger: " << oldTrigString << std::endl;
	triggerFlag = 0;
    }
    if ( whichTrigger.find(newTrigString) != std::string::npos){
	t1_pt_cut = 80;//50;//55;
	t2_pt_cut = 40;//25;
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
    int passhltHpsDoublePFTau20Old;
    int passhltHpsDoublePFTauTightOld;
    int passhltHpsDoublePFTauAgainstMuonTightOld;
    int passhltMatchedVBFTwoTight;
    int passhltMatchedVBFOneTight;

    int passL1New;
    int passhltHpsDoublePFTau20New;
    int passhltHpsDoublePFTauTightNew;
    int passhltHpsDoublePFTauAgainstMuonTightNew;
    int passhltHpsPFTau50Tight;
    int passhltMatchedVBFIsoTauTwoTight;

    // normal offline flag vars
    // delete these when you have time
    // basic or "preselection" should never be used as it has no physical meaning.
    // this is kind of like tying your shoes together from an analysis standpoint
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
   
    int nEvents, runNumber, lumiBlock, eventNumberID;
 
    // filled data branches
    //
    outTree->Branch("nEvents", &nEvents);
    outTree->Branch("runNumber", &runNumber);
    outTree->Branch("lumiBlock", &lumiBlock);
    outTree->Branch("eventNumberID", &eventNumberID);
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
    outTree->Branch("passhltHpsDoublePFTau20Old", &passhltHpsDoublePFTau20Old);
    outTree->Branch("passhltHpsDoublePFTauTightOld", &passhltHpsDoublePFTauTightOld);
    outTree->Branch("passhltHpsDoublePFTauAgainstMuonTightOld", &passhltHpsDoublePFTauAgainstMuonTightOld);
    outTree->Branch("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    outTree->Branch("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);
    // path for new trigger
    outTree->Branch("passL1New", &passL1New);
    outTree->Branch("passhltHpsDoublePFTau20New", &passhltHpsDoublePFTau20New);
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
    int passSelL1JetL1Tau = 0;
    int viableBeforeRmvOl=0;
    int viableAfterRmvOl=0;
    int viableAfterMjj=0;
    int jetsMatchedBeforeRmvOl = 0;  
    int tauMatchedBeforeRmvOl = 0;
    int bothJetsMatchedAfterRmvOl = 0;
    int oneJetMatchedAfterRmvOl = 0;
    // Event Loop
    // for-loop of just 2000 events is useful to test code without heavy I/O to terminal from cout statements
    for (int iEntry = 0; iEntry < 60001; ++iEntry) {
    //for (int iEntry = 0; iEntry < inTree->GetEntries(); iEntry++) {
	inTree->GetEntry(iEntry);
	//if (iEntry % 1000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber->at(0); //update to ints in NtupleMaker
	lumiBlock = inTree->lumiBlock->at(0);
	eventNumberID = inTree->eventNumberID->at(0);

	// initialize all flags to zero
	// offline trigger filter cutflow efficiency flags	
	// old trigger path
	passL1Old = 0;
	passhltHpsDoublePFTau20Old = 0;
        passhltHpsDoublePFTauTightOld = 0;
	passhltHpsDoublePFTauAgainstMuonTightOld = 0;
    	passhltMatchedVBFTwoTight = 0;
 	passhltMatchedVBFOneTight = 0;
	// new trigger path
	passL1New = 0;
	passhltHpsDoublePFTau20New = 0;
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
	for (int iTau = 0; iTau < vecSizeAODTau; ++iTau){

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
	for (int iTau = 1; iTau < tauCandidates.size(); ++iTau){
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
	for (int iJet = 0; iJet < vecSizeAODJet; ++iJet){

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
	for (int iJet = 0; iJet < jetCandidates.size(); ++iJet){
	    for (int jJet = 0; jJet < jetCandidates.size(); ++jJet){
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

        std::vector<TLorentzVector> aodObjs;
	aodObjs.push_back(aodJet1);
	aodObjs.push_back(aodJet2);
	aodObjs.push_back(aodTau1);
	aodObjs.push_back(aodTau2);

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

	//passSel = 1;

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
	    for (int iTriggerTau = 0; iTriggerTau < vecSizeHpsTau; ++iTriggerTau){
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
		for (int iTriggerJet = 0; iTriggerJet < vecSizeVBFTwo; ++iTriggerJet){
		    triggerJetCand.SetPtEtaPhiE(inTree->hltMatchedVBFTwoTight_pt->at(iTriggerJet),
						inTree->hltMatchedVBFTwoTight_eta->at(iTriggerJet),
	    					inTree->hltMatchedVBFTwoTight_phi->at(iTriggerJet),
	    					inTree->hltMatchedVBFTwoTight_energy->at(iTriggerJet));
		    triggerJetCandidates.push_back(triggerJetCand);
		}
	    }
	    // fill trigger jet candidates for new trigger
	    if (vecSizeVBFIsoTauTwo >= 2 && vecSizeHpsTau50 >= 1 && triggerFlag == 1) {
		for (int iTriggerJet = 0; iTriggerJet < vecSizeVBFIsoTauTwo; ++iTriggerJet){
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

	// filling offline selection && pass trigger flags
	if (passSel && passOldTrig && triggerFlag == 0) passSelAndOldTrig = 1;
	if (passSel && passNewTrig && triggerFlag == 1) passSelAndNewTrig = 1;


	// if all the dRs are less than 0.5, then we've matched AOD to reco HLT
	if (dRt1 < 0.5 && dRt2 < 0.5 && !overlapped) matchedTaus = 1;
	if (dRj1 < 0.5 && dRj2 < 0.5 && !overlapped) matchedJets = 1;
	if (matchedTaus && matchedJets) matchedBoth = 1;

	if (matchedTaus && passSelAndOldTrig) passSelOldTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndOldTrig) passSelOldTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndOldTrig) passSelOldTrigAndMatchedBoth = 1;

	if (matchedTaus && passSelAndNewTrig) passSelNewTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndNewTrig) passSelNewTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndNewTrig) passSelNewTrigAndMatchedBoth = 1;


	// L1 object investigation in same trigger phase space
	// passes offline selection, passes old L1, passes new L1
	if (passSel && inTree->hltL1VBFDiJetOR_pt->size() >= 2 && (inTree->hltL1VBFDiJetIsoTau_tauPt->size() >=1 && inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2)){
	    //std::cout << "passed old and new L1: " << iEntry << std::endl;

    	    // get L1Jets from old VBF trigger
    	    // if their pT is < 35 don't store them bc they wouldn't pass new VBF L1
    	    std::vector<TLorentzVector> passL1JetCands;
    	    TLorentzVector passL1Jet;
    	    for (int iOldJet = 0; iOldJet < inTree->hltL1VBFDiJetOR_pt->size(); ++iOldJet){
    	    passL1Jet.SetPtEtaPhiE(inTree->hltL1VBFDiJetOR_pt->at(iOldJet),
    			inTree->hltL1VBFDiJetOR_eta->at(iOldJet),
    			inTree->hltL1VBFDiJetOR_phi->at(iOldJet),
    			inTree->hltL1VBFDiJetOR_energy->at(iOldJet));
    	    if (passL1Jet.Pt() > 35) {
    		passL1JetCands.push_back(passL1Jet);
    	    } 
    	    //std::cout << "Jet pT: " << L1Jet.Pt() << std::endl;
    	    }

    	    // get L1Taus from ditau trigger
    	    // if their pT is < 45 don't store them bc they wouldn't pass new VBF L1
    	    std::vector<TLorentzVector> passL1TauCands;
    	    TLorentzVector passL1Tau;
    	    for (int iNewTau = 0; iNewTau < inTree->hltL1VBFDiJetIsoTau_tauPt->size(); ++iNewTau){
    		passL1Tau.SetPtEtaPhiE(inTree->hltL1VBFDiJetIsoTau_tauPt->at(iNewTau),
    				inTree->hltL1VBFDiJetIsoTau_tauEta->at(iNewTau),
    				inTree->hltL1VBFDiJetIsoTau_tauPhi->at(iNewTau),
    				inTree->hltL1VBFDiJetIsoTau_tauEnergy->at(iNewTau));
     	    if (passL1Tau.Pt() > 45){
    		passL1TauCands.push_back(passL1Tau);
	    } 
	    //std::cout << "Tau pT: " << L1Tau.Pt() << std::endl;
	    }
	    if (iEntry == 33 || iEntry == 1339 || iEntry == 1355) {
		    std::cout << "iEntry: " << iEntry << std::endl;
		    std::cout << "-----------------passed old and new L1----------------" << std::endl;
		    //print all aod info as well,,,
		    std::cout << "aod jet  info" << std::endl;
		    coutAODobjs(aodJet1, aodJet2);

		    std::cout << "aod tau info" << std::endl;
		    coutAODobjs(aodTau1, aodTau2);

		    std::cout << "L1 jet info" << std::endl;
		    coutL1objs(passL1JetCands, aodObjs);

		    std::cout << "L1 tau info" << std::endl;
		    coutL1objs(passL1TauCands, aodObjs);

		    std::cout << "----------------------------------------------------" << std::endl;

		    } //end if statement	


	}
	
	// passes offline selection, passes old L1, doesn't pass new L1
	int jetNum, tauNum;
	if (passSel && inTree->hltL1VBFDiJetOR_pt->size() >= 2 && inTree->hltL1sDoubleTauBigOR_pt->size() >= 2 && //passOldTrig &&
		(inTree->hltL1VBFDiJetIsoTau_tauPt->size() < 1 || inTree->hltL1VBFDiJetIsoTau_jetPt->size() < 2)) { 

	    jetNum = inTree->hltL1VBFDiJetOR_pt->size(); 	// # jets from old trigger
	    tauNum = inTree->hltL1sDoubleTauBigOR_pt->size(); 	// # taus from ditau trigger

	    //std::cout << "jetNum: " << jetNum << " tau Num: " << tauNum << std::endl;

	    // if jets and taus present from other triggers, compute dR by hand and see what's going on in new VBF L1...
	    
	    if (jetNum >= 2 && tauNum >= 1) { // only need one tau from ditau trigger, except it won't fire unless there's at least two..
		//std::cout << "-----------------------------" << std::endl;
		//std::cout << "iEntry!: " <<  iEntry << std::endl;

		passSelL1JetL1Tau += 1;

		// get L1Jets from old VBF trigger
		// if their pT is < 35 don't store them bc they wouldn't pass new VBF L1
		std::vector<TLorentzVector> L1JetCands;
		TLorentzVector L1Jet;
		for (int iOldJet = 0; iOldJet < jetNum; ++iOldJet){
		L1Jet.SetPtEtaPhiE(inTree->hltL1VBFDiJetOR_pt->at(iOldJet),
				inTree->hltL1VBFDiJetOR_eta->at(iOldJet),
				inTree->hltL1VBFDiJetOR_phi->at(iOldJet),
				inTree->hltL1VBFDiJetOR_energy->at(iOldJet));
		if (L1Jet.Pt() > 35) {
		L1JetCands.push_back(L1Jet);
		} 
		//std::cout << "Jet pT: " << L1Jet.Pt() << std::endl;
		}

		// get L1Taus from ditau trigger
		// if their pT is < 45 don't store them bc they wouldn't pass new VBF L1
		std::vector<TLorentzVector> L1TauCands;
		TLorentzVector L1Tau;
		for (int iNewTau = 0; iNewTau < tauNum; ++iNewTau){
		L1Tau.SetPtEtaPhiE(inTree->hltL1sDoubleTauBigOR_pt->at(iNewTau),
					inTree->hltL1sDoubleTauBigOR_eta->at(iNewTau),
					inTree->hltL1sDoubleTauBigOR_phi->at(iNewTau),
					inTree->hltL1sDoubleTauBigOR_energy->at(iNewTau));
		if (L1Tau.Pt() > 45){
		L1TauCands.push_back(L1Tau);
		} 
		//std::cout << "Tau pT: " << L1Tau.Pt() << std::endl;
		}

		//std::cout << "Good Jet Num: " << L1JetCands.size() << '\t' << "Good Tau Num: " << L1TauCands.size() << std::endl;

		// if we have at least 2 jets and at least 1 tau passing new VBF L1, event may be viable 
		if (L1JetCands.size() >= 2 && L1TauCands.size() >= 1) {
 		    viableBeforeRmvOl += 1;

		    // see if event obj matches AOD before overlap removal
		    // not as precise at L1, but try anyways
		    int jetMatchIndex1 = -1;
		    double dRAODJet1;
		    TLorentzVector jetMatch1;
		    int jetMatchIndex2 = -1;
		    double dRAODJet2;
		    TLorentzVector jetMatch2;

		    jetMatchIndex1 = simpleMatching(L1JetCands, aodJet1);
		    jetMatchIndex2 = simpleMatching(L1JetCands, aodJet2);
		    jetMatch1 = L1JetCands.at(jetMatchIndex1);
		    dRAODJet1 = jetMatch1.DeltaR(aodJet1);
		    jetMatch2 = L1JetCands.at(jetMatchIndex2);
		    dRAODJet2 = jetMatch2.DeltaR(aodJet2);

		    if (jetMatchIndex1 == jetMatchIndex2) {
			std::vector<TLorentzVector> tempL1Jets;
			tempL1Jets = L1JetCands;
			tempL1Jets.erase(tempL1Jets.begin() + jetMatchIndex1); // indices are equal, so either is fine to use here
		 	if (dRAODJet1 <= dRAODJet2) {// look for jet 2 again, removed jet was jet 1
			    jetMatchIndex2 = simpleMatching(tempL1Jets, aodJet2);
			    jetMatch2 = tempL1Jets.at(jetMatchIndex2);
			    dRAODJet2 = jetMatch2.DeltaR(aodJet2);
			}
			if (dRAODJet2 < dRAODJet1) {// look for jet 1 again, removed jet was jet 2
			    jetMatchIndex1 = simpleMatching(tempL1Jets, aodJet1);
			    jetMatch1 = tempL1Jets.at(jetMatchIndex1);
			    dRAODJet1 = jetMatch1.DeltaR(aodJet1);
			}
		    }

		    //std::cout << "# jets before cleaning: " << L1JetCands.size() << std::endl;		 
		    //std::cout << "dR1 before: " << dRAODJet1 << '\t' << "dR2 before: " << dRAODJet2 << std::endl;
		    //if (dRAODJet1 < 0.5 || dRAODJet2 < 0.5) std::cout << "one matched before cleaning" << std::endl;
		    if (dRAODJet1 < 0.5 && dRAODJet2 < 0.5) jetsMatchedBeforeRmvOl += 1;//std::cout << "both matched before cleaning" << std::endl;
		    TLorentzVector tauMatch;
		    int tauMatchIndex = -1;
		    double dRAODTau1;
		    double dRAODTau2;		
		    tauMatchIndex = simpleMatching(L1TauCands, aodTau1);
		    tauMatch = L1TauCands.at(tauMatchIndex);
		    dRAODTau1 = tauMatch.DeltaR(aodTau1);
		    tauMatchIndex = simpleMatching(L1TauCands, aodTau2);
		    tauMatch = L1TauCands.at(tauMatchIndex);
		    dRAODTau2 = tauMatch.DeltaR(aodTau2);
		    if (dRAODTau1 < 0.5 || dRAODTau2 < 0.5) tauMatchedBeforeRmvOl += 1; 

		}

		// cross-clean L1 jets and taus
		// taus get priority, so if an obj from L1 jets is overlapped with an obj from L1 taus
		// then don't store that L1 jet to the new cross-cleaned container of L1 jets
		std::vector<TLorentzVector> crossCleanedL1Jets;
		for (int iJetCand = 0; iJetCand < L1JetCands.size(); ++iJetCand){
		    bool clean = true;
		    for (int iTauCand = 0; iTauCand < L1TauCands.size(); iTauCand++){
			if (L1TauCands.at(iTauCand).DeltaR(L1JetCands.at(iJetCand)) < 0.5) {//plot dR
			    clean = false;
			}
		    }
		    if (clean) crossCleanedL1Jets.push_back(L1JetCands.at(iJetCand));
		}
		//std::cout << "ccL1Jets Num: " << crossCleanedL1Jets.size() << std::endl;
				
		// if you have at least two jets in the cross-cleaned container, then the event is still viable
		// all that's left to check is the Mjj of the L1 cross-cleaned jets
		if (crossCleanedL1Jets.size() >= 2 && L1TauCands.size() >= 1) {

		    if (iEntry == 930 || iEntry == 1673 || iEntry == 8386) {

		    std::cout << "iEntry: " << iEntry << std::endl;
		    std::cout << "-----------------passed overlap removal----------------" << std::endl;
		    //print all aod info as well,,,
		    std::cout << "aod jet  info" << std::endl;
		    coutAODobjs(aodJet1, aodJet2);

		    std::cout << "aod tau info" << std::endl;
		    coutAODobjs(aodTau1, aodTau2);

		    std::cout << "L1 jet info" << std::endl;
		    std::cout << "number matched to taus " << '\t' << L1JetCands.size() - crossCleanedL1Jets.size() << std::endl;
		    coutL1objs(L1JetCands, aodObjs);

		    std::cout << "L1 tau info" << std::endl;
		    coutL1objs(L1TauCands, aodObjs);

		    std::cout << "----------------------------------------------------" << std::endl;

		    } //end if statement	

		    viableAfterRmvOl += 1;

		    // see if event obj matches AOD even after overlap removal
		    // not as precise at L1, but try anyways
		    int cleanedJetMatchIndex1 = -1;
		    double dRCleanedJetAODJet1;
		    TLorentzVector cleanedJetMatch1;

		    int cleanedJetMatchIndex2 = -1;
		    double dRCleanedJetAODJet2;
		    TLorentzVector cleanedJetMatch2;

		    cleanedJetMatchIndex1 = simpleMatching(crossCleanedL1Jets, aodJet1);
		    cleanedJetMatch1 = crossCleanedL1Jets.at(cleanedJetMatchIndex1);
		    dRCleanedJetAODJet1 = cleanedJetMatch1.DeltaR(aodJet1);
		    cleanedJetMatchIndex2 = simpleMatching(crossCleanedL1Jets, aodJet2);
		    cleanedJetMatch2 = crossCleanedL1Jets.at(cleanedJetMatchIndex2);
		    dRCleanedJetAODJet2 = cleanedJetMatch2.DeltaR(aodJet2);

		    if (cleanedJetMatchIndex1 == cleanedJetMatchIndex2) {
			std::vector<TLorentzVector> tempCleanedL1Jets;
			tempCleanedL1Jets = crossCleanedL1Jets;
			tempCleanedL1Jets.erase(tempCleanedL1Jets.begin() + cleanedJetMatchIndex1); // indices are the same, so either can be used here
			if (dRCleanedJetAODJet1 <= dRCleanedJetAODJet2) { //look for jet 2 obj again, removed obj was jet 1
			    cleanedJetMatchIndex2 = simpleMatching(tempCleanedL1Jets, aodJet2);
			    cleanedJetMatch2 = tempCleanedL1Jets.at(cleanedJetMatchIndex2);
			    dRCleanedJetAODJet2 = cleanedJetMatch2.DeltaR(aodJet2);
			}
			if (dRCleanedJetAODJet2 < dRCleanedJetAODJet1) { //look for jet 1 obj again, removed obj was jet 2
			    cleanedJetMatchIndex1 = simpleMatching(tempCleanedL1Jets, aodJet1);
			    cleanedJetMatch1 = tempCleanedL1Jets.at(cleanedJetMatchIndex1);
			    dRCleanedJetAODJet1 = cleanedJetMatch1.DeltaR(aodJet1);
			}
		    }

		    //std::cout << "# clean jets: " << crossCleanedL1Jets.size() << std::endl;		 
		    //std::cout << "dR1 after: " << dRCleanedJetAODJet1 << '\t' << "dR2 after: " << dRCleanedJetAODJet2 << std::endl;
		    if (dRCleanedJetAODJet1 < 0.5 || dRCleanedJetAODJet2 < 0.5) oneJetMatchedAfterRmvOl += 1;//std::cout << "one matched after cleaning" << std::endl;
		    if (dRCleanedJetAODJet1 < 0.5 && dRCleanedJetAODJet2 < 0.5) bothJetsMatchedAfterRmvOl += 1;//std::cout << "both matched after cleaning" << std::endl;

		    //std::cout << "viable after rmovl" << std::endl;
		
		// store Mjjs and jets pairs if they pass the 450 cut from the new VBF L1
     		    float L1mjj;
    		    std::vector<float> mjjL1Jets;
    		    std::vector<std::pair<int,int>> L1JetMjjPairs;
    		    float prevMjj = -1;
    		    int   highMjjIndex = -1;
    		    for (int iJet = 0; iJet < crossCleanedL1Jets.size(); ++iJet){
    		        for (int jJet = 0; jJet < crossCleanedL1Jets.size(); ++jJet){
    			    if (jJet >= iJet) continue;
    			    if (crossCleanedL1Jets.at(iJet).DeltaR(crossCleanedL1Jets.at(jJet)) > 0.5) {
    			        L1mjj = (crossCleanedL1Jets.at(iJet) + crossCleanedL1Jets.at(jJet)).M();
    			        //std::cout << "L1mjj " << L1mjj << '\t' << iJet << '\t' << jJet << std::endl;
			        if (L1mjj > 450){
			    	    mjjL1Jets.push_back(L1mjj);
			    	    L1JetMjjPairs.push_back(std::make_pair(jJet, iJet));	
				    if (L1mjj > prevMjj){
				        prevMjj = L1mjj;
				        highMjjIndex = mjjL1Jets.size() - 1;
				    }
			        }
			    }
		        }
		    }

		    if (highMjjIndex == -1) continue;//std::cout << "no good mjj pairs " << std::endl;
		    else{   viableAfterMjj += 1;
			//std::cout << "viable after mjj" << std::endl;
		        }
		}

		else{

		    if (iEntry == 694 || iEntry == 6494 || iEntry == 12602) {

		    std::cout << "iEntry: " << iEntry << std::endl;
		    std::cout << "-----------failed after overlap removal-----------" << std::endl;
		    //print all aod info as well,,,
		    std::cout << "aod jet  info" << std::endl;
		    coutAODobjs(aodJet1, aodJet2);
		    std::cout << "aod tau info" << std::endl;
		    coutAODobjs(aodTau1, aodTau2);

		    std::cout << "L1 jet info" << std::endl;
		    std::cout << "number matched to taus " << '\t' << L1JetCands.size() - crossCleanedL1Jets.size() << std::endl;
		    coutL1objs(L1JetCands, aodObjs);

		    std::cout << "L1 tau info" << std::endl;
		    coutL1objs(L1TauCands, aodObjs);

		    std::cout << "----------------------------------------------------" << std::endl;
		}

		}
	    }
	}


	// old trigger filter cutflow eff flags
	if (passSel && triggerFlag == 0 && inTree->hltL1VBFDiJetOR_pt->size() >= 2) {
	    passL1Old = inTree->passhltL1VBFDiJetOR;
	}

	if (passL1Old && inTree->hltHpsDoublePFTau20_pt->size() >= 2) {
	    passhltHpsDoublePFTau20Old = inTree->passhltHpsDoublePFTau20;
	}

	if (passhltHpsDoublePFTau20Old && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauTightOld = inTree->passhltHpsDoublePFTauTight; 
	}

	if (passhltHpsDoublePFTauTightOld && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauAgainstMuonTightOld = inTree->passhltHpsDoublePFTauAgainstMuonTight;
	}

	if (passhltHpsDoublePFTauAgainstMuonTightOld && inTree->hltMatchedVBFTwoTight_pt->size() >= 2) {
	    passhltMatchedVBFTwoTight = inTree->passhltMatchedVBFTwoTight;
	}

	if (passhltMatchedVBFTwoTight && inTree->hltMatchedVBFOneTight_pt->size() >= 1) {
	    passhltMatchedVBFOneTight = inTree->passhltMatchedVBFOneTight;
	}

	// new trigger filter cutflow eff flags
	if (passSel && triggerFlag == 1 && inTree->hltL1VBFDiJetIsoTau_tauPt->size() >= 1
					&& inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2) {
	    passL1New = inTree->passhltL1VBFDiJetIsoTau;
	}

	if (passL1New && inTree->hltHpsDoublePFTau20_pt->size() >= 2) {
	    passhltHpsDoublePFTau20New = inTree->passhltHpsDoublePFTau20;
	}

	if (passhltHpsDoublePFTau20New && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauTightNew = inTree->passhltHpsDoublePFTauTight;
	}

	if (passhltHpsDoublePFTauTightNew && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) {
	    passhltHpsDoublePFTauAgainstMuonTightNew = inTree->passhltHpsDoublePFTauAgainstMuonTight;
	}

	if (passhltHpsDoublePFTauAgainstMuonTightNew && inTree->hltHpsPFTau50Tight_pt->size() >= 1) {
	    passhltHpsPFTau50Tight = inTree->passhltHpsPFTau50Tight;
	}

	if (passhltHpsPFTau50Tight && inTree->hltMatchedVBFIsoTauTwoTight_pt->size() >= 2) {
	    passhltMatchedVBFIsoTauTwoTight = inTree->passhltMatchedVBFIsoTauTwoTight;
	}
	
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

    //formatting for 30 minutes until i realized you could just put the number first...

    std::cout << passSelL1JetL1Tau << '\t' << "Passed Sel. passed old VBF L1, passed ditau L1, failed new VBF L1" << std::endl << \
		viableBeforeRmvOl << '\t' << "Passed double 35 jet pt, 45 tau pt" << std::endl << \
		jetsMatchedBeforeRmvOl << '\t' << "Two jets matched before overlap removal" << std::endl << \
		tauMatchedBeforeRmvOl << '\t' << "Tau matched before overlap removal" << std::endl << \
		viableAfterRmvOl << '\t' << "At least two jets remain after overlap removal" << std::endl << \
		oneJetMatchedAfterRmvOl << '\t' << "At least one jet is matched after overlap removal" << std::endl << \
		bothJetsMatchedAfterRmvOl << '\t' << "Both jets matched after overlap removal" << std::endl << \
		viableAfterMjj << '\t' << "Dijet pair passing Mjj > 450 GeV" << std::endl;

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
