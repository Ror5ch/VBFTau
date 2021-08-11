#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <iomanip>
#include <tuple>

#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include "trigger_tree.h"
#include "trigger_selection.h"

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root new


int main(int argc, char** argv)	{

    // Open input file and make new output file, also declare necessary variables
    std::string inName = *(argv + 1);
    std::string outName = *(argv + 2);

    TFile *fIn = TFile::Open(inName.c_str());
    TTree* treePtr = (TTree*) fIn->Get("demo/vbf");
    trigger_tree* inTree = new trigger_tree (treePtr);

    TTree *outTree = new TTree("outTree", "outTree");
    outTree->SetDirectory(0);

    if (argc < 4) {
	std::cout << "specify trigger cuts in third argument (old, new, tight, or)" << std::endl;
	return 0; // prevents rest of code from running
    }

    std::string whichTrigger = *(argv + 3);
    std::string oldTrigString = "old";
    std::string newTrigString = "new";
    std::string tightTrigString = "tight";
    std::string orTrigString = "or";

    int triggerFlag = -1;
    if ((whichTrigger.find(oldTrigString) == std::string::npos && 
	whichTrigger.find(newTrigString) == std::string::npos &&
	whichTrigger.find(tightTrigString) == std::string::npos &&
	whichTrigger.find(orTrigString) == std::string::npos) || argc < 4) {
	std::cout << "specify trigger cuts in third argument (old, new, tight, or)" << std::endl;
	return 0;
    }

    // vars for AOD selection, which change depending on the trigger being studied
    float t1_pt_cut, t2_pt_cut, j1_pt_cut, j2_pt_cut, mjj_cut;
    // offline selection should be consistently 5 GeV above HLT thresholds
    if (whichTrigger.find(oldTrigString) != std::string::npos){
	t1_pt_cut = 25;
	t2_pt_cut = 25;
	j1_pt_cut = 120;
	j2_pt_cut = 45;
	mjj_cut = 700;
	triggerFlag = 0;
    }
    if (whichTrigger.find(newTrigString) != std::string::npos){
	t1_pt_cut = 50;
	t2_pt_cut = 25;
	j1_pt_cut = 45;
	j2_pt_cut = 45;
	mjj_cut = 550;
	triggerFlag = 1;
    }
    if (whichTrigger.find(tightTrigString) != std::string::npos){
	t1_pt_cut = 80;
	t2_pt_cut = 40;
	j1_pt_cut = 120;
	j2_pt_cut = 45;
	mjj_cut = 700;
	triggerFlag = 2;
    }
    if (whichTrigger.find(orTrigString) != std::string::npos){
	t1_pt_cut = 25;
	t2_pt_cut = 25;
	j1_pt_cut = 45;
	j2_pt_cut = 45;
	mjj_cut = 550;
	triggerFlag = 3;
    }

    float minimal_tau_pt_cut = 20;
    float minimal_jet_pt_cut = 35;

    // run variables
    int nEvents, runNumber, lumiBlock, eventNumberID;

    // hlt variables
    float j1_pt, j1_eta, j1_phi, j1_energy; 
    float j2_pt, j2_eta, j2_phi, j2_energy; 
    float mjj;
    float t1_pt, t1_eta, t1_phi, t1_energy;
    float t2_pt, t2_eta, t2_phi, t2_energy;
   
    // AOD variables, A is for AOD
    float j1_pt_A, j1_eta_A, j1_phi_A, j1_energy_A; 
    float j2_pt_A, j2_eta_A, j2_phi_A, j2_energy_A; 
    float mjj_A;
    float t1_pt_A, t1_eta_A, t1_phi_A, t1_energy_A;
    float t2_pt_A, t2_eta_A, t2_phi_A, t2_energy_A;

    int deepTauVSjet, deepTauVSmu, deepTauVSele, jetID;

    // variables for matching
    float dRj1, dRj2, dRt1, dRt2;

    // offline filter eff cutflow flag variables
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

    // flag variables for selection and trigger
    int passBase;

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
    outTree->Branch("jetID", &jetID);
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

    // branch variables that are incremented so you don't have to check the ttree
    int numPassSel = 0;
    int numPassSelAndOldTrig = 0;
    int numPassSelAndNewTrig = 0;
    int numPassSelAndTight = 0;
    int numPassSelAndOR = 0;

    int numMatchedJets = 0;
    int numMatchedTaus = 0;
    int numMatchedBoth = 0;

    // ad hoc variables for testing
    int passL1 = 0;
    int failNewL1PassDiTau = 0;
    int matchedL1Jets = 0;
    int matchedL1Taus = 0;
    int matchedL1Both = 0;

    int matchedL1CCJets = 0;
    int matchedL1RemTaus = 0;
    int matchedL1CCBoth = 0;

    int passSize = 0;
    int passCCSize = 0;
    int passMjj = 0;
    int passJetAODs = 0;
    int passTauAODs = 0;
    int passAllAODs = 0;

    bool printOldL1 = false; 
    bool printNewL1 = false;
    bool printPrimL1 = false;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    for (int iEntry = 0; iEntry < 60001; ++iEntry) {
    //for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	if (iEntry % 10000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

	//---------------------apply base selection and fill AOD objects------------------------------//
	// base selection flag (cuts are arbitrary so they're not physically meaningful)
	// artifact of trying to decouple matching and selection steps.
	passBase = 0;
	min_cutflow->Fill(0.0,1.0); // fill cutflow before any selection

	int vecSizeAODTau = inTree->tauPt->size(); // number of taus in event
	int vecSizeAODJet = inTree->jetPt->size(); // number of jets in event
	//minimal selection common to both triggers//
	// check the number of objects in the event, need at least two of each
	if (vecSizeAODTau < 2) continue;
	min_cutflow->Fill(1.0,1.0);
	if (vecSizeAODJet < 2) continue;
	min_cutflow->Fill(2.0,1.0); // fill cutflow with events that have 2 taus and 2 jets
	// check kinematics and ID of tau objects, store good taus
	std::vector<TLorentzVector> tauCandidates;	
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
	//
	// check that we have at least 2 good taus to work with
	if (tauCandidates.size() < 2) continue;

	// take first two AOD taus that aren't overlapped
	// tauCandidates are already ordered by pt (this was checked with simple cout statements)
	TLorentzVector aodTau1, aodTau2;
	aodTau1.SetPtEtaPhiE(tauCandidates.at(0).Pt(), tauCandidates.at(0).Eta(), tauCandidates.at(0).Phi(), tauCandidates.at(0).Energy());
	for (std::vector<TLorentzVector>::const_iterator iTau = tauCandidates.begin()+1; iTau != tauCandidates.end(); ++iTau) {
	    aodTau2.SetPtEtaPhiE(iTau->Pt(), iTau->Eta(), iTau->Phi(), iTau->Energy());
	    if (aodTau2.DeltaR(aodTau1) > 0.5) break; // if taus are not overlapped, leave the for-loop
	}
	// check that the tau didn't make it all the way through the loop without breaking
	// I think this is unlikely but it's good to be redundant
	if (aodTau1.DeltaR(aodTau2) < 0.5) continue; 

	min_cutflow->Fill(3.0,1.0); // fill cutflow with events that have 2 or more good taus
	sel_cutflow->Fill(0.0,1.0); // start of smaller cutflow graph (using two for scaling purposes)

	// check kinematics and ID of jet objects, store good jets
	std::vector<TLorentzVector> jetCandidates;
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

	// fill aod jets with pair of jets that produced the largest mjj value
	// from cout statements, aodJet1 was verified to be leading jet
	TLorentzVector aodJet1, aodJet2;
        std::tie(aodJet1, aodJet2) = highestMjjPair(jetCandidates);

	// calculate mjj of AOD jets, if an mjj pair wasn't found, mjj of the "aod" jets will be zero
	// the function highestMjjPair could be improved so this ad hoc test of mjj is avoided...
	mjj_A = (aodJet1 + aodJet2).M();
	if (mjj_A == 0) continue;

	min_cutflow->Fill(4.0,1.0);
	sel_cutflow->Fill(1.0,1.0);

	passBase = 1;

        std::vector<TLorentzVector> AODObjs;
	AODObjs.insert(end(AODObjs), {aodJet1, aodJet2, aodTau1, aodTau2});

	//-----------------------tighter selection guided by trigger specific cutoffs---------------//

	passSel = 1;

	if (aodTau1.Pt() < t2_pt_cut || aodTau2.Pt() < t2_pt_cut) passSel = 0;
	else{sel_cutflow->Fill(2.0,1.0);}
	
	if (aodTau1.Pt() < t1_pt_cut) passSel = 0;
	else{sel_cutflow->Fill(3.0,1.0);}

	if (aodJet1.Pt() < j2_pt_cut || aodJet2.Pt() < j2_pt_cut) passSel = 0;
	else{sel_cutflow->Fill(4.0,1.0);}

	if (aodJet1.Pt() < j1_pt_cut) passSel = 0;
	else{sel_cutflow->Fill(5.0,1.0);}

	if (mjj_A < mjj_cut) passSel = 0;
	else{sel_cutflow->Fill(6.0,1.0);}

	if (passSel) numPassSel += 1;

	//-----------------------try to match AOD and HLT objects-----------------------------------//
	// not performed for "tight" or "or" selections because it's not clear which filter to use 
	// for jets in those cases
	
	// get number of objects in tau and jet trigger filters
	int vecSizeHpsTau = inTree->hltHpsDoublePFTauTight_pt->size(); // at least two taus > 20 GeV filter, common to both
	int vecSizeVBFTwo = inTree->hltMatchedVBFTwoTight_pt->size();  // at least two jets > 45 GeV filter, old trigger only
	int vecSizeVBFOne = inTree->hltMatchedVBFOneTight_pt->size();  // one jet > 115 GeV filter, old trigger only
	int vecSizeVBFIsoTauTwo = inTree->hltMatchedVBFIsoTauTwoTight_pt->size(); // at least two jets > 45 GeV filter and iso tau present, new trigger only
	int vecSizeHpsTau50 = inTree->hltHpsPFTau50Tight_pt->size(); // at least one tau > 50 GeV filter, new trigger only

	// if enough objects are in the correct HLT filters, then match to AOD and compute dRs
	TLorentzVector trigTau1, trigTau2, trigJet1, trigJet2;
	if (vecSizeHpsTau >= 2 && ((vecSizeVBFTwo >= 2 && vecSizeVBFOne >= 1 && triggerFlag == 0) 
				|| (vecSizeVBFIsoTauTwo >= 2 && vecSizeHpsTau50 >= 1 && triggerFlag == 1))  ){

	    std::vector<TLorentzVector> triggerTauCandidates, triggerJetCandidates;
	    // fill trigger tau candidates for either trigger from 20 GeV tau filter
	    triggerTauCandidates = hltFillWithCands(inTree, "hltHpsDoublePFTauTight", vecSizeHpsTau, 0);

	    // fill trigger jet candidates for old trigger
	    if (vecSizeVBFTwo >= 2 && vecSizeVBFOne >= 1 && triggerFlag == 0) \
		triggerJetCandidates = hltFillWithCands(inTree, "hltMatchedVBFTwoTight", vecSizeVBFTwo, 0);  

	    // fill trigger jet candidates for new trigger
	    if (vecSizeVBFIsoTauTwo >= 2 && vecSizeHpsTau50 >= 1 && triggerFlag == 1) \
		triggerJetCandidates = hltFillWithCands(inTree, "hltMatchedVBFIsoTauTwoTight", vecSizeVBFIsoTauTwo, 0);

	    // match AOD and HLT jets and taus
	    dRj1 = 999;
	    dRj2 = 999;
	    // tie is a handy method for assigning tuple output
            std::tie(trigJet1, trigJet2) = matchTwoObjs(triggerJetCandidates, aodJet1, aodJet2);
            dRj1 = trigJet1.DeltaR(aodJet1);
            dRj2 = trigJet2.DeltaR(aodJet2);

	    dRt1 = 999;
	    dRt2 = 999;
	    std::tie(trigTau1, trigTau2) = matchTwoObjs(triggerTauCandidates, aodTau1, aodTau2);
	    dRt1 = trigTau1.DeltaR(aodTau1);
	    dRt2 = trigTau2.DeltaR(aodTau2);

	    mjj = (trigJet1 + trigJet2).M();

	    int overlapped = 0;
	    // check that same type objects are not overlapped
	    if (trigTau1.DeltaR(trigTau2) < 0.5 || trigJet1.DeltaR(trigJet2) < 0.5 ) overlapped = 1;
	    // check that different objects are not overlapped
	    if (trigTau1.DeltaR(trigJet1) < 0.5 || trigTau1.DeltaR(trigJet2) < 0.5 ||
		trigTau2.DeltaR(trigJet1) < 0.5 || trigTau2.DeltaR(trigJet2) < 0.5) overlapped = 1;

	    // matchedObj variables initialization
	    matchedTaus = matchedJets = matchedBoth = 0;	
	    // if all the dRs are less than 0.5, then we've matched AOD to reco HLT
	    if (dRt1 < 0.5 && dRt2 < 0.5 && !overlapped) {matchedTaus = 1; numMatchedTaus += 1;}
	    if (dRj1 < 0.5 && dRj2 < 0.5 && !overlapped) {matchedJets = 1; numMatchedJets += 1;}
	    if (matchedTaus && matchedJets) {matchedBoth = 1; numMatchedBoth += 1;}
	}

	//------------------------------fill flags and output tree-----------------------------------//

	// initialize trigger variables before getting new ones from tree
	passOldTrig = passNewTrig = 0;
	passOldTrig = inTree->passOldTrigTight->at(0);
	passNewTrig = inTree->passNewTrigTight->at(0);

	// filling offline selection and pass trigger flags
	// variables starting with "num" are couted to terminal 
	// the other variable is a flag that is stored in the output tree
	passSelAndOldTrig = passSelAndNewTrig = 0;
	if (passSel && passOldTrig ) {passSelAndOldTrig = 1; numPassSelAndOldTrig += 1;}
	if (passSel && passNewTrig ) {passSelAndNewTrig = 1; numPassSelAndNewTrig += 1;}

	// further subdivisions of matched objects and passed selection+trigger
	passSelOldTrigAndMatchedTaus = passSelOldTrigAndMatchedJets = passSelOldTrigAndMatchedBoth = 0;
	if (matchedTaus && passSelAndOldTrig) passSelOldTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndOldTrig) passSelOldTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndOldTrig) passSelOldTrigAndMatchedBoth = 1;

	passSelNewTrigAndMatchedTaus = passSelNewTrigAndMatchedJets = passSelNewTrigAndMatchedBoth = 0;
	if (matchedTaus && passSelAndNewTrig) passSelNewTrigAndMatchedTaus = 1;
	if (matchedJets && passSelAndNewTrig) passSelNewTrigAndMatchedJets = 1;
	if (matchedBoth && passSelAndNewTrig) passSelNewTrigAndMatchedBoth = 1;

	// tight pass
	if (passSel && (passOldTrig && passNewTrig) && triggerFlag == 2) numPassSelAndTight += 1;
	// OR pass
	if (passSel && (passOldTrig || passNewTrig) && (triggerFlag == 0 || triggerFlag == 1)) numPassSelAndOR += 1;

	// -----------------------------------------L1 object investigation -----------------------------//
	int oldL1JetSize = inTree->hltL1VBFDiJetOR_pt->size();
	int newL1JetSize = inTree->hltL1VBFDiJetIsoTau_jetPt->size();
	int newL1TauSize = inTree->hltL1VBFDiJetIsoTau_tauPt->size();
	int diTauL1TauSize = inTree->hltL1sDoubleTauBigOR_pt->size();
	int primL1TauSize = inTree->tauL1PrimitivesPt->size();
	int primL1JetSize = inTree->jetL1PrimitivesPt->size();

	printPrimL1 = true;
	if (passSel && printPrimL1) {
	    std::vector<TLorentzVector> jetL1Primitives = hltFillWithCands(inTree, "jetL1Primitives", primL1JetSize, 35);
	    int jetPrimSize = jetL1Primitives.size();
	    std::vector<TLorentzVector> tauL1Primitives = hltFillWithCands(inTree, "tauL1Primitives", primL1TauSize, 45);
	    int tauPrimSize = tauL1Primitives.size();

	    if (jetPrimSize >= 2 && tauPrimSize >= 1) {
		passL1 += 1;
		// increment counters
		incIfTrue(matchedL1Jets, matchedL1Taus, matchedL1Both, jetL1Primitives, tauL1Primitives, AODObjs.at(0));

		bool withCC = true;
		if (withCC) {
		    //perform cross cleaning and check matching again
		    std::vector<TLorentzVector> crossCleanedL1PrimJets = crossCleanJets(jetL1Primitives, tauL1Primitives);
		    int ccL1PrimSize = crossCleanedL1PrimJets.size();

		    if (ccL1PrimSize >= 2 && ccL1PrimSize <= 5) {
		        passCCSize += 1;
		        // increment counters
		        incIfTrue(matchedL1CCJets, matchedL1RemTaus, matchedL1CCBoth, crossCleanedL1PrimJets, tauL1Primitives, AODObjs.at(0));

                        // calculate mjj of two highest mjj cleaned jets
                        TLorentzVector ccPrimJet1, ccPrimJet2;
                        std::tie(ccPrimJet1, ccPrimJet2) = highestMjjPair(crossCleanedL1PrimJets);
                        if ((ccPrimJet1 + ccPrimJet2).M() > 450) passMjj +=1;
			// see if all 4 AOD objects are present
			bool passJets, passTaus, passBoth;
			passJets = passTaus = passBoth = false;
			if (AODObjInContainer(crossCleanedL1PrimJets, AODObjs.at(0)) &&
			    AODObjInContainer(crossCleanedL1PrimJets, AODObjs.at(1))) {passJets = true; passJetAODs += 1;}
			if (AODObjInContainer(tauL1Primitives, AODObjs.at(2)) &&
			    AODObjInContainer(tauL1Primitives, AODObjs.at(3))) {passTaus = true; passTauAODs += 1;}
			if (passJets && passTaus) {passBoth = true; passAllAODs +=1;}

		    }
		} // end CC if statement

	    } // end jetPrimSize if statement
	} // end if statement for L1 prim

	printNewL1 = false;
	// passes offline selection passes new L1
	if (printNewL1 && passSel && newL1TauSize >=1 && newL1JetSize >= 2) {
	    passL1 += 1;
    	    // get L1Jets from new VBF trigger
    	    std::vector<TLorentzVector> passL1JetCands = hltFillWithCands(inTree, "hltL1VBFDiJetIsoTau_jets", newL1JetSize);

    	    // get L1Taus from new VBF trigger
    	    std::vector<TLorentzVector> passL1TauCands = hltFillWithCands(inTree, "hltL1VBFDiJetIsoTau_taus", newL1TauSize);

	    incIfTrue(matchedL1Jets, matchedL1Taus, matchedL1Both, passL1JetCands, passL1TauCands, AODObjs.at(0));
	    //dumpEventKinemInfo(iEntry, "passed new L1", AODObjs, passL1JetCands, passL1TauCands);
	   
	    TLorentzVector newL1Jet1, newL1Jet2;
	    std::tie(newL1Jet1, newL1Jet2) = highestMjjPair(passL1JetCands); 
	    if ((newL1Jet1 + newL1Jet2).M() > 450) passMjj += 1;
	    

	} // end if statement for pass new L1

	printOldL1 = false;	
	// passes offline selection, passes Old L1
	if (printOldL1 && passSel && oldL1JetSize >= 2) {
	    passL1 += 1;
	    // doesn't pass new L1
	    if (newL1TauSize < 1 || newL1JetSize < 2) { 
	    // passes Old L1 and DiTau L1
	    if (diTauL1TauSize >= 1) {
		failNewL1PassDiTau += 1;

		// get L1Jets from old VBF trigger
		// if their pT is < 35 don't store them bc they wouldn't pass new VBF L1
		std::vector<TLorentzVector> L1JetCands = hltFillWithCands(inTree, "hltL1VBFDiJetOR", oldL1JetSize, 35);
		int L1JetCandsSize = L1JetCands.size();
		// get L1Taus from ditau trigger
		// if their pT is < 45 don't store them bc they wouldn't pass new VBF L1
		std::vector<TLorentzVector> L1TauCands = hltFillWithCands(inTree, "hltL1sDoubleTauBigOR", diTauL1TauSize, 45);
		int L1TauCandsSize = L1TauCands.size();

		// see if leading AOD jet is in L1 Jet and Tau containers before overlap removal
		// if we have at least 2 jets and at least 1 tau passing new VBF L1 kinem requirements, event may be viable 
		if (L1JetCandsSize >= 2 && L1TauCandsSize >= 1) {
		    passSize += 1;
		    incIfTrue(matchedL1Jets, matchedL1Taus, matchedL1Both, L1JetCands, L1TauCands, AODObjs.at(0));

		    // cross clean jets wrt taus, give taus priority
		    std::vector<TLorentzVector> crossCleanedL1Jets = crossCleanJets(L1JetCands, L1TauCands);
		    // if there are enough cross-cleaned (CC) jets, check for matched objects and check Mjj  
		    if (crossCleanedL1Jets.size() >= 2 && L1TauCandsSize >= 1) {
			passCCSize += 1;
			incIfTrue(matchedL1CCJets, matchedL1RemTaus, matchedL1CCBoth, crossCleanedL1Jets, L1TauCands, AODObjs.at(0));

			TLorentzVector cleanedJet1, cleanedJet2;
        		std::tie(cleanedJet1, cleanedJet2) = highestMjjPair(crossCleanedL1Jets);

			// calculate mjj of two highest mjj cleaned jets
			if ((cleanedJet1 + cleanedJet2).M() > 450) passMjj += 1;
			
		    }
		}// end if statement for pass Old L1 and pass DiTau L1
	    }// end if statement for pass Sel., pass Old L1, pass DiTau L1, fail New L1
	}// end if statement for pass Old VBF L1 fail New VBF L1
	}

	//----------------------filling filter flags-------------------------------//
	// at the Ntuple level, it's possible some filters are filled by both trigger paths,
	// so filling them manually by chaining together if statements gives us a more accurate 
	// picture of which filters were filled by which paths.
	
	// old trigger filter flags initialization
	passL1Old = 0;
	passhltHpsDoublePFTau20Old = 0;
        passhltHpsDoublePFTauTightOld = 0;
	passhltHpsDoublePFTauAgainstMuonTightOld = 0;
    	passhltMatchedVBFTwoTight = 0;
 	passhltMatchedVBFOneTight = 0;

	// filling old trigger filter flags
	if (passSel && triggerFlag == 0 && inTree->hltL1VBFDiJetOR_pt->size() >= 2) passL1Old = inTree->passhltL1VBFDiJetOR;

	if (passL1Old && inTree->hltHpsDoublePFTau20_pt->size() >= 2) passhltHpsDoublePFTau20Old = inTree->passhltHpsDoublePFTau20;

	if (passhltHpsDoublePFTau20Old && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) passhltHpsDoublePFTauTightOld = inTree->passhltHpsDoublePFTauTight;

	if (passhltHpsDoublePFTauTightOld && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) passhltHpsDoublePFTauAgainstMuonTightOld = inTree->passhltHpsDoublePFTauAgainstMuonTight;

	if (passhltHpsDoublePFTauAgainstMuonTightOld && inTree->hltMatchedVBFTwoTight_pt->size() >= 2) passhltMatchedVBFTwoTight = inTree->passhltMatchedVBFTwoTight;

	if (passhltMatchedVBFTwoTight && inTree->hltMatchedVBFOneTight_pt->size() >= 1) passhltMatchedVBFOneTight = inTree->passhltMatchedVBFOneTight;

	// new trigger filter flags initialization
	passL1New = 0;
	passhltHpsDoublePFTau20New = 0;
	passhltHpsDoublePFTauTightNew = 0;
	passhltHpsDoublePFTauAgainstMuonTightNew = 0;
	passhltHpsPFTau50Tight = 0;
	passhltMatchedVBFIsoTauTwoTight = 0; 

	// filling new trigger filter flags
	if (passSel && triggerFlag == 1 && inTree->hltL1VBFDiJetIsoTau_tauPt->size() >= 1
					&& inTree->hltL1VBFDiJetIsoTau_jetPt->size() >= 2) passL1New = inTree->passhltL1VBFDiJetIsoTau;

	if (passL1New && inTree->hltHpsDoublePFTau20_pt->size() >= 2) passhltHpsDoublePFTau20New = inTree->passhltHpsDoublePFTau20;

	if (passhltHpsDoublePFTau20New && inTree->hltHpsDoublePFTauTight_pt->size() >= 2) passhltHpsDoublePFTauTightNew = inTree->passhltHpsDoublePFTauTight;

	if (passhltHpsDoublePFTauTightNew && inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size() >= 2) passhltHpsDoublePFTauAgainstMuonTightNew = inTree->passhltHpsDoublePFTauAgainstMuonTight;

	if (passhltHpsDoublePFTauAgainstMuonTightNew && inTree->hltHpsPFTau50Tight_pt->size() >= 1) passhltHpsPFTau50Tight = inTree->passhltHpsPFTau50Tight;

	if (passhltHpsPFTau50Tight && inTree->hltMatchedVBFIsoTauTwoTight_pt->size() >= 2) passhltMatchedVBFIsoTauTwoTight = inTree->passhltMatchedVBFIsoTauTwoTight;
	
        // fill kine branches with matched AOD
        if (passSel) {
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

	    if (matchedJets) {
		j1_pt = trigJet1.Pt();
		j1_eta = trigJet1.Eta();
		j1_phi = trigJet1.Phi();
		j1_energy = trigJet1.Energy();	
		j2_pt = trigJet2.Pt();
		j2_eta = trigJet2.Eta();
		j2_phi = trigJet2.Phi();
		j2_energy = trigJet2.Energy();
	    }
	    if (matchedTaus) {
		t1_pt = trigTau1.Pt();
		t1_eta = trigTau1.Eta();
		t1_phi = trigTau1.Phi();
		t1_energy = trigTau1.Energy();
		t2_pt = trigTau2.Pt();
		t2_eta = trigTau2.Eta();
		t2_phi = trigTau2.Phi();
		t2_energy = trigTau2.Energy();
	    }
	} // end if statement to fill kinem variables

        outTree->Fill();
    }// end event loop

    std::cout << "Selection: " << std::endl;
    std::cout <<"t1 pt" << '\t' << "t2 pt" << '\t' << "j1 pt" << '\t' << "j2 pt" << '\t' << "mjj" << std::endl << \
		t1_pt_cut << '\t' << t2_pt_cut << '\t' << j1_pt_cut << '\t' << j2_pt_cut << '\t' << mjj_cut << std::endl;
    std::cout << numPassSel << '\t' << "Passed Sel." << std::endl;

    int numPassSelAndTrig;
    if (triggerFlag == 0) numPassSelAndTrig = numPassSelAndOldTrig;
    if (triggerFlag == 1) numPassSelAndTrig = numPassSelAndNewTrig;
    if (triggerFlag == 2) numPassSelAndTrig = numPassSelAndTight;
    if (triggerFlag == 3) numPassSelAndTrig = numPassSelAndOR;

    if (printOldL1 || printNewL1 || printPrimL1) { 
	std::cout << numPassSelAndTrig << '\t' << "Passed Sel. and Trigger Decision" << std::endl \
		  << passL1 << '\t' << "Passed Sel. and Passed L1" << std::endl;

	if (printOldL1) {
		std::cout << failNewL1PassDiTau << '\t' << "Failed New VBF L1 and Passed Di Tau L1" << std::endl;
		std::cout << passSize << '\t' << "Passed Size Req. after New L1 Kinematic Restrictions" << std::endl;
	}

	std::cout << matchedL1Jets << '\t' << "Leading AOD Jet Matched in L1 Jet Container" << std::endl << \
		matchedL1Taus << '\t' << "Leading AOD Jet Matched in L1 Tau Container" << std::endl << \
		matchedL1Both << '\t' << "Leading AOD Jet Matched in both L1 Containers" << std::endl;

	if (printOldL1 || printPrimL1) {
	    std::cout << "Cross Cleaning (CC) Performed" << std::endl \
		<< passCCSize << '\t' << "Passed Size Req. after Cross Cleaning" << std::endl \
		<< matchedL1CCJets << '\t' << "Leading AOD Jet Matching in CC L1 Jet Container" << std::endl \
		<< matchedL1RemTaus << '\t' << "Leading AOD Jet Matching in Remaining L1 Tau Container" << std::endl \
		<< matchedL1CCBoth << '\t' << "Leading AOD Jet Matched in Both L1 Containers after CC" << std::endl;
	}
	std::cout << passMjj << '\t' << "Passing Mjj Requirement of 450 GeV" << std::endl;

	if (printPrimL1) {
	    std::cout << passJetAODs << '\t' << "Jets Matched in L1 to AOD" << std::endl;
	    std::cout << passTauAODs << '\t' << "Taus Matched in L1 to AOD" << std::endl;
	    std::cout << passAllAODs << '\t' << "All Matched in L1 to AOD" << std::endl;
	}
    }

    bool printMatching = false;
    if (printMatching) {
    	std::cout << numMatchedJets << '\t' << "matched jets" << std::endl << \
		numMatchedTaus << '\t' << "matched taus" << std::endl << \
		numMatchedBoth << '\t' << "matched both" << std::endl;
    }

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
