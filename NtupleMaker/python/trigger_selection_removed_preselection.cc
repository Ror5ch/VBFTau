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
    std::string L1StudyTrigString = "L1";
    std::string diTauTrigString = "diTau";

    int triggerFlag = -1;
    if ((whichTrigger.find(oldTrigString) == std::string::npos && 
	whichTrigger.find(newTrigString) == std::string::npos &&
	whichTrigger.find(tightTrigString) == std::string::npos &&
	whichTrigger.find(orTrigString) == std::string::npos &&
	whichTrigger.find(L1StudyTrigString) == std::string::npos ) || argc < 4) {
	std::cout << "specify trigger cuts in third argument (old, new, tight, or, L1)" << std::endl;
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
    if (whichTrigger.find(L1StudyTrigString) != std::string::npos) {
	t1_pt_cut = t2_pt_cut = j1_pt_cut = j2_pt_cut = mjj_cut = 0;
	triggerFlag = 4;
    }
    if (whichTrigger.find(diTauTrigString) != std::string::npos) {
        t1_pt_cut = t2_pt_cut = 32;
        j1_pt_cut = j2_pt_cut = mjj_cut = 0;
        triggerFlag = 5;
    }


    float minimal_tau_pt_cut = 32;
    float minimal_jet_pt_cut = 30;

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
    int passTwoObjMass = 0; //consider renaming to DiObjMass? M2O (mass 2 objects) 
    int matchedJetAODs = 0;
    int matchedTauAODs = 0;
    int matchedAllAODs = 0;

    bool printOldL1 = false; 
    bool printNewL1 = false;
    bool printPrimL1 = false;
    bool massL1Testing = false;

    int numMassAnyTwoBothJets = 0;
    int numMassAnyTwoBothTaus = 0;
    int numMassAnyTwoOneJetOneTau = 0;
    int numMassAnyTwoObjOneIsJetAndTau = 0;
    int numMassAnyTwoObjTwoIsJetAndTau = 0;
    int numMassAnyTwoBothObjsAreJetAndTau = 0;

    bool L1SeedCaseZero, L1SeedCaseOne, L1SeedCaseTwo, L1SeedCaseThree;
    L1SeedCaseZero = L1SeedCaseOne = L1SeedCaseTwo = L1SeedCaseThree = false;

    int passHTT = 0;
    int passHTT350 = 0;
    int passHTTCount = 0;
    int passHTT350Count = 0;
    int passDiTauOffORHTT = 0;
    int passDiTauOffORHTT350 = 0;
    int passDiTauOffANDHTT = 0;
    int passDiTauOffANDHTT350 = 0;
    int passDiTauL1ORHTT = 0;
    int passDiTauL1ORHTT350 = 0;
    int passDiTauL1ANDHTT = 0;
    int passDiTauL1ANDHTT350 = 0;



    int passDiTau_Off = 0;
    int passOld_Off = 0;
    int passNew_Off = 0;
    int passNew2_Off = 0;
    int passDiTau_OffCount = 0;
    int passOld_OffCount = 0;
    int passNew_OffCount = 0;
    int passNew2_OffCount = 0;

    int passDiTau_L1 = 0;
    int passOld_L1 = 0;
    int passNew_L1 = 0;
    int passNew2_L1 = 0;
    int passDiTau_L1Count = 0;
    int passOld_L1Count = 0;
    int passNew_L1Count = 0;
    int passNew2_L1Count = 0;

    int passDiTauOROld_Off = 0;
    int passDiTauORNew2_Off = 0;
    int passDiTauOROldORNew2_Off = 0;
    int passDiTauANDOld_Off = 0;
    int passDiTauANDNew2_Off = 0;
    int passDiTauANDOldANDNew2_Off = 0;

    int passDiTauOROld_L1 = 0;
    int passDiTauORNew2_L1 = 0;
    int passDiTauOROldORNew2_L1 = 0;
    int passDiTauANDOld_L1 = 0;
    int passDiTauANDNew2_L1 = 0;
    int passDiTauANDOldANDNew2_L1 = 0;

    int passDiTauL1ANDOff = 0;
    int passOldL1ANDOff = 0;
    int passNewL1ANDOff = 0;
    int passNew2L1ANDOff = 0;

    int passOldNew2L1ANDOff = 0;

    int passOldORNew2_L1 = 0;
    int passOldANDNew2_L1 = 0;
    int passOldORNew2_Off = 0;
    int passOldANDNew2_Off = 0;
    int passDiTauL1ANDOldNew2L1ANDOff = 0;
    int passDiTauOldNew2L1ANDOff = 0;

    int passDiTauL1ANDHTT350ANDOldNew2L1ANDOff = 0;
    int passDiTauL1ANDHTT350ANDNew2L1ANDOff = 0;

    int passDiTauL1ANDNew2L1ANDOff = 0;

    int passOldORNewL1ANDOff = 0;
    int passDiTauANDHTT350ANDOldORNewL1ANDOff = 0;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 60001; ++iEntry) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	if (iEntry % 100000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

        passHTT = 0;
        passHTT350 = 0;

        passDiTau_Off = 0;
        passOld_Off = 0;
        passNew_Off = 0;
        passNew2_Off = 0;

        passDiTau_L1 = 0;
        passOld_L1 = 0;
        passNew_L1 = 0;
        passNew2_L1 = 0;


	//---------------------apply base selection and fill AOD objects------------------------------//
	// base selection flag (cuts are arbitrary so they're not physically meaningful)
	// artifact of trying to decouple matching and selection steps.
	min_cutflow->Fill(0.0,1.0); // fill cutflow before any selection

	int vecSizeAODTau = inTree->tauPt->size(); // number of taus in event
	int vecSizeAODJet = inTree->jetPt->size(); // number of jets in event
	//minimal selection common to both triggers//
	// check the number of objects in the event, need at least two of each
	min_cutflow->Fill(1.0,1.0);
	min_cutflow->Fill(2.0,1.0); 
	// fill cutflow with events that have 2 taus and 2 jets
	// check kinematics and ID of tau objects, store good taus
	std::vector<TLorentzVector> tauCandidates;	
	for (int iTau = 0; iTau < vecSizeAODTau; ++iTau) {
            bool passTauID = false;
	    deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
	    deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
            deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
	    if (deepTauVSjet && deepTauVSmu && deepTauVSele) passTauID = true;

	    if (passTauID && inTree->tauPt->at(iTau) >= minimal_tau_pt_cut && fabs(inTree->tauEta->at(iTau) <= 2.1)) {
	      TLorentzVector tauCand;
	      tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau),
				     inTree->tauEta->at(iTau), 
				     inTree->tauPhi->at(iTau), 
				     inTree->tauEnergy->at(iTau));
	      tauCandidates.push_back(tauCand);
            }
	}
        int tauCandsSize = tauCandidates.size();
        if (tauCandsSize < 2) continue; // need two taus minimum

	// take first two AOD taus that aren't overlapped
	// tauCandidates are already ordered by pt (this was checked with simple cout statements)
	TLorentzVector AODTau1, AODTau2;
	AODTau1.SetPtEtaPhiE(tauCandidates.at(0).Pt(), tauCandidates.at(0).Eta(), tauCandidates.at(0).Phi(), tauCandidates.at(0).Energy());
	for (std::vector<TLorentzVector>::const_iterator iTau = tauCandidates.begin()+1; iTau != tauCandidates.end(); ++iTau) {
	    AODTau2.SetPtEtaPhiE(iTau->Pt(), iTau->Eta(), iTau->Phi(), iTau->Energy());
	    if (AODTau2.DeltaR(AODTau1) > 0.5) break; // if taus are not overlapped, leave the for-loop
	}
	// check that the tau didn't make it all the way through the loop without breaking
	// I think this is unlikely but it's good to be redundant
	if (AODTau1.DeltaR(AODTau2) < 0.5) continue; 
        //passDiTau_Off += 1;

	min_cutflow->Fill(3.0,1.0); // fill cutflow with events that have 2 or more good taus
	sel_cutflow->Fill(0.0,1.0); // start of smaller cutflow graph (using two for scaling purposes)

	// check kinematics and ID of jet objects, store good jets
	std::vector<TLorentzVector> jetCandidates;
	for (int iJet = 0; iJet < vecSizeAODJet; ++iJet){

            bool passJetID = false;
	    if (inTree->jetID->at(iJet) >= 6) passJetID = true; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

	    if (passJetID && inTree->jetPt->at(iJet) >= minimal_jet_pt_cut && fabs(inTree->jetEta->at(iJet) <= 4.7)) {
	      TLorentzVector jetCand;
	      jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
				     inTree->jetEta->at(iJet), 
				     inTree->jetPhi->at(iJet), 
				     inTree->jetEn->at(iJet));
	      // if a jetCandidate looks like it could be either tau we already selected, don't store it
	      bool jetCandIsTau = false;
	      if (AODTau1.DeltaR(jetCand) < 0.5 || AODTau2.DeltaR(jetCand) < 0.5) jetCandIsTau = true;

	      if (!jetCandIsTau) jetCandidates.push_back(jetCand);
            }
	}
	// check that we have at least two good jets
	int jetCandsSize = jetCandidates.size(); //ideally we now have at least 2 jets

	// fill AOD jets with pair of jets that produced the largest mjj value
	// from cout statements, AODJet1 was verified to be leading jet
	TLorentzVector AODJet1, AODJet2;
	if (jetCandsSize >= 2) {
          std::tie(AODJet1, AODJet2) = highestMassPair(jetCandidates);
        }

	min_cutflow->Fill(4.0,1.0);
	sel_cutflow->Fill(1.0,1.0);

	// -----------------------------------------L1 investigation -----------------------------//
	int oldL1JetSize = inTree->hltL1VBFDiJetOR_pt->size();
	int newL1JetSize = inTree->hltL1VBFDiJetIsoTau_jetPt->size();
	int newL1TauSize = inTree->hltL1VBFDiJetIsoTau_tauPt->size();
	int diTauL1TauSize = inTree->hltL1sDoubleTauBigOR_pt->size();
	int primL1TauSize = inTree->tauL1PrimitivesPt->size();
	int primL1JetSize = inTree->jetL1PrimitivesPt->size();
	TLorentzVector objOne, objTwo; // two objects used for invariant mass, mjj in most cases
	double twoObjMass;

	printNewL1 = false;
	printOldL1 = false;

	printPrimL1 = true;
	int primL1JetPtCut = 35;
        int primL1IsoTau32PtCut = 32;
	int primL1TauPtCut = 35;
	int primL1IsoTau40PtCut = 40;
	int primL1IsoTau45PtCut = 45;
	// testing multiple possible L1s, pay attention to the booleans,,,
	massL1Testing = true;
	bool oldVBFwL1Prim = false;
	bool newVBFwL1Prim = false;
	bool massDblJetOrJetTau_DblJetOneIsoTau = true;

	// ad hoc pass sel...
	if (triggerFlag == 4) {
            if (tauCandsSize >= 2) passDiTau_Off = 1;
	    if (jetCandsSize >= 2) {
              // common to all
              // all possible mass pairs to check
	      double mj1j2 = (AODJet1 + AODJet2).M();
	      double mj1t1 = (AODJet1 + AODTau1).M(); 
	      double mj1t2 = (AODJet1 + AODTau2).M();
	      double mj2t1 = (AODJet2 + AODTau1).M();
	      double mj2t2 = (AODJet2 + AODTau2).M();
	      //double mt1t2 = (AODTau1 + AODTau2).M();

              int pass2Mass = (mj1j2 >= 450 || mj1t1 >= 450 || mj1t2 >= 450 || mj2t1 >= 450 || mj2t2 >= 450);

              double AODJet1Pt_ = AODJet1.Pt();	
              double AODJet2Pt_ = AODJet2.Pt();	
              double AODTau1Pt_ = AODTau1.Pt();
              double AODTau2Pt_ = AODTau2.Pt();

              if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && AODTau1Pt_ >= 40 && AODTau2Pt_ >= 40) passHTT = 1;
              if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && AODTau1Pt_ >= 40 && AODTau2Pt_ >= 40 && mj1j2 >= 350) passHTT350 = 1;

	      if (AODJet1Pt_ >= 120 && AODJet2Pt_ >= 45 && AODTau1Pt_ >= 25 && AODTau2Pt_ >= 25 && mj1j2 >= 700) passOld_Off = 1;
	      
              if (AODJet1Pt_ >= 45 && AODJet2Pt_ >= 45 && AODTau1Pt_ >= 50 && AODTau2Pt_ >= 25 && mj1j2 >= 550) passNew_Off = 1;

              if (AODJet1Pt_ >= 45 && AODJet2Pt_ >= 45 && AODTau1Pt_ >= 50 && AODTau2Pt_ >= 25 && pass2Mass) passNew2_Off = 1;

            }

	} // end pass[Tag]_L1 loop

	// fill standard containers, jet container, tau container, and isoTau container
	std::vector<TLorentzVector> jetL1Primitives = hltFillWithCands(inTree, "jetL1Primitives", primL1JetSize, primL1JetPtCut);
	int jetPrimSize = jetL1Primitives.size();
	std::vector<TLorentzVector> tauL1Primitives = hltFillWithCands(inTree, "tauL1Primitives", primL1TauSize, primL1TauPtCut);
	int tauPrimSize = tauL1Primitives.size();

	std::vector<TLorentzVector> isoTau32L1Primitives;
        for (int iTau = 0; iTau < tauPrimSize; ++iTau) {
          TLorentzVector tempTau_ = tauL1Primitives.at(iTau);
          if (tempTau_.Pt() >= primL1IsoTau32PtCut && inTree->tauL1PrimitivesIso->at(iTau)) isoTau32L1Primitives.push_back(tempTau_);
        }
        int isoTau32PrimSize = isoTau32L1Primitives.size();

        std::vector<TLorentzVector> isoTau35L1Primitives;
	std::vector<TLorentzVector> isoTau40L1Primitives;
        std::vector<TLorentzVector> isoTau45L1Primitives;
	for (int iTau = 0; iTau < isoTau32PrimSize; ++iTau) {
          TLorentzVector tempTau_ = tauL1Primitives.at(iTau);
          if (tempTau_.Pt() > 35) isoTau35L1Primitives.push_back(tempTau_);
	  if (tempTau_.Pt() > primL1IsoTau40PtCut) isoTau40L1Primitives.push_back(tempTau_);
          if (tempTau_.Pt() > primL1IsoTau45PtCut) isoTau45L1Primitives.push_back(tempTau_);
	}
        int isoTau35PrimSize = isoTau35L1Primitives.size();
	int isoTau40PrimSize = isoTau40L1Primitives.size();
	int isoTau45PrimSize = isoTau45L1Primitives.size();

	// perform cross-cleaning (cc) (Wrt = with respect to)
	std::vector<TLorentzVector> crossCleanedL1PrimJetsWrtIsoTau40 = crossCleanJets(jetL1Primitives, isoTau40L1Primitives);
	int ccWrtIsoTau40L1JetPrimSize = crossCleanedL1PrimJetsWrtIsoTau40.size();

	std::vector<TLorentzVector> crossCleanedL1PrimJetsWrtIsoTau45 = crossCleanJets(jetL1Primitives, isoTau45L1Primitives);
	int ccWrtIsoTau45L1JetPrimSize = crossCleanedL1PrimJetsWrtIsoTau45.size();

        // DiTau
        if (isoTau32PrimSize >= 2) passDiTau_L1 = 1;

        // old VBF
	if (jetPrimSize >= 2) {
/***	
	  std::tie(objOne, objTwo) = highestMassPair(jetL1Primitives);
	  twoObjMass = (objOne + objTwo).M();
	  double jetOnePt = objOne.Pt();
	  double jetTwoPt = objTwo.Pt();
***/
          bool jet110Present = false;
	  for (int iJet = 0; iJet < jetPrimSize; ++iJet) {
	    if (jetL1Primitives.at(iJet).Pt() >= 110) jet110Present = true;
	  }

          float mjj_Old = 0; float tempMjj_ = 0;
          for (int iJet = 0; iJet < jetPrimSize; ++iJet) {
            for (int jJet = 0; jJet < jetPrimSize; ++jJet) {
              if (iJet >= jJet) continue;
              if (jetL1Primitives.at(iJet).Pt() < 110 && jetL1Primitives.at(jJet).Pt() < 110 && !jet110Present) continue;
              tempMjj_ = (jetL1Primitives.at(iJet) + jetL1Primitives.at(jJet)).M();
              if (tempMjj_ > mjj_Old) mjj_Old = tempMjj_;
            }
          }
          if (mjj_Old >= 620) passOld_L1 = 1;
        }
	  
	  //if (twoObjMass >= 620 && (((jetOnePt >= 110 && jetTwoPt >= 35) || (jetOnePt >= 35 && jetTwoPt >= 110))
	//		|| (jetOnePt >= 35 && jetTwoPt >= 35 && someJetGreaterThan110GeV)) ){ passOld_L1 = 1;}
	//}

        //newVBF
	if (ccWrtIsoTau45L1JetPrimSize >= 2 && isoTau45PrimSize >= 1) {
	  // check mjj
          //std::tie(objOne, objTwo) = highestMassPair(crossCleanedL1PrimJetsWrtIsoTau45);
	  //twoObjMass = (objOne + objTwo).M();
          //if (twoObjMass >= 450) {
	  //  passNew_L1 = 1;
	  //}
	  float mjj_New = 0; float tempMjj_ = 0;
          for (int iJet = 0; iJet < ccWrtIsoTau45L1JetPrimSize; ++iJet) {
            for (int jJet = 0; jJet < ccWrtIsoTau45L1JetPrimSize; ++jJet) {
              if (iJet >= jJet) continue;
              tempMjj_ = (crossCleanedL1PrimJetsWrtIsoTau45.at(iJet) + crossCleanedL1PrimJetsWrtIsoTau45.at(jJet)).M();
              if (tempMjj_ > mjj_New) mjj_New = tempMjj_;
            }
          }
          if (mjj_New >= 450) passNew_L1 = 1;
	} 

        // newVBF2
	if (ccWrtIsoTau45L1JetPrimSize >= 2 && isoTau45PrimSize >= 1) {
	  // we exclude the two tau case for this seed, but allow the two jet case.
	  // To do this, we look for the highestMassPair of just jets and then
	  // the highest mass pair using one tau and one jet. Then we take the larger of the two pairs
	  /***
	  TLorentzVector tempObjOne, tempObjTwo;
	  std::tie(tempObjOne, tempObjTwo) = highestMassPair(crossCleanedL1PrimJetsWrtIsoTau45, isoTau45L1Primitives, "OneJetOneTau");
	  double tempTwoObjMass = (tempObjOne + tempObjTwo).M();
	  std::tie(objOne, objTwo) = highestMassPair(crossCleanedL1PrimJetsWrtIsoTau45);
	  twoObjMass = (objOne + objTwo).M();
          if (tempTwoObjMass > twoObjMass) {
            twoObjMass = tempTwoObjMass; objOne = tempObjOne; objTwo = tempObjTwo;
	    //std::cout << "OneJetOneTau heavier than DiJet" << std::endl; // happens about half the time w Rmv Ol.
	  }

          if (twoObjMass >= 450) {
	    passNew2_L1 = 1;
          }
***/
          float mjj_New2 = highestMassOfPair(crossCleanedL1PrimJetsWrtIsoTau45, isoTau45L1Primitives);
          if (mjj_New2 >= 450) passNew2_L1 = 1;
	}

        passHTTCount += passHTT;
        passHTT350Count += passHTT;

        passDiTau_OffCount += passDiTau_Off;
        passOld_OffCount += passOld_Off;
        passNew_OffCount += passNew_Off;
        passNew2_OffCount += passNew2_Off;

        passDiTau_L1Count += passDiTau_L1;
        passOld_L1Count += passOld_L1;
        passNew_L1Count += passNew_L1;
        passNew2_L1Count += passNew2_L1;

        passDiTauOffORHTT += (passDiTau_Off || passHTT);
        passDiTauOffORHTT350 += (passDiTau_Off || passHTT350);
        passDiTauL1ORHTT += (passDiTau_L1 || passHTT);
        passDiTauL1ORHTT350 += (passDiTau_L1 || passHTT350);
        passDiTauOffANDHTT += (passDiTau_Off && passHTT);
        passDiTauOffANDHTT350 += (passDiTau_Off && passHTT350);
        passDiTauL1ANDHTT += (passDiTau_L1 && passHTT);
        passDiTauL1ANDHTT350 += (passDiTau_L1 && passHTT350);

        passDiTauOROld_Off += (passDiTau_Off || passOld_Off);
        passDiTauORNew2_Off += (passDiTau_Off || passNew2_Off);
        passDiTauOROldORNew2_Off += (passDiTau_Off || passOld_Off || passNew2_Off);
        passDiTauANDOld_Off += (passDiTau_Off && passOld_Off);
        passDiTauANDNew2_Off += (passDiTau_Off && passNew2_Off);
        passDiTauANDOldANDNew2_Off += (passDiTau_Off && passOld_Off && passNew2_Off);

        passOldORNew2_Off += (passOld_Off || passNew2_Off);
        passOldANDNew2_Off += (passOld_Off && passNew2_Off);

        passDiTauOROld_L1 += (passDiTau_L1 || passOld_L1);
        passDiTauORNew2_L1 += (passDiTau_L1 || passNew2_L1);
        passDiTauOROldORNew2_L1 += (passDiTau_L1 || passOld_L1 || passNew2_L1);
        passDiTauANDOld_L1 += (passDiTau_L1 && passOld_L1);
        passDiTauANDNew2_L1 += (passDiTau_L1 && passNew2_L1);
        passDiTauANDOldANDNew2_L1 += (passDiTau_L1 && passOld_L1 && passNew2_L1);

        passOldORNew2_L1 += (passOld_L1 || passNew2_L1);
        passOldANDNew2_L1 += (passOld_L1 && passNew2_L1);

        passDiTauL1ANDOff += (passDiTau_L1 && passDiTau_Off);
        passOldL1ANDOff += (passOld_L1 && passOld_Off);
        passNewL1ANDOff += (passNew_L1 && passNew_Off);
        passNew2L1ANDOff += (passNew2_L1 && passNew2_Off);

        passOldNew2L1ANDOff += (passOld_L1 && passOld_Off && passNew2_L1 && passNew2_Off);

        passDiTauL1ANDNew2L1ANDOff += (passDiTau_L1 && passNew2_L1 && passNew2_Off);

	passDiTauL1ANDOldNew2L1ANDOff += (passDiTau_L1 && passOld_L1 && passOld_Off && passNew2_L1 && passNew2_Off);
        passDiTauOldNew2L1ANDOff += (passDiTau_L1 && passOld_L1 && passNew2_L1 && passDiTau_Off && passOld_Off && passNew2_Off);

        passDiTauL1ANDHTT350ANDOldNew2L1ANDOff += (passDiTau_L1 && passHTT350 && passOld_L1 && passOld_Off && passNew2_L1 && passNew2_Off);
        passDiTauL1ANDHTT350ANDNew2L1ANDOff += (passDiTau_L1 && passHTT350 && passNew2_L1 && passNew2_Off);

        passOldORNewL1ANDOff += ((passOld_L1 && passOld_Off) || (passNew2_L1 && passNew2_Off));
        passDiTauANDHTT350ANDOldORNewL1ANDOff += ((passDiTau_L1 && passHTT350) && ((passOld_L1 && passOld_Off) || (passNew2_L1 && passNew2_Off)));


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
/***	
        // fill kine branches with matched AOD
        if (passSel) {
	    t1_pt_A = AODTau1.Pt();
	    t1_eta_A = AODTau1.Eta();
	    t1_phi_A = AODTau1.Phi();
	    t1_energy_A = AODTau1.Energy();
	    t2_pt_A = AODTau2.Pt();
	    t2_eta_A = AODTau2.Eta();
	    t2_phi_A = AODTau2.Phi();
	    t2_energy_A = AODTau2.Energy();

	    j1_pt_A = AODJet1.Pt();
	    j1_eta_A = AODJet1.Eta();
	    j1_eta_A = AODJet1.Phi();
	    j1_energy_A = AODJet1.Energy();
	    j2_pt_A = AODJet2.Pt();
	    j2_eta_A = AODJet2.Eta();
	    j2_eta_A = AODJet2.Phi();
	    j2_energy_A = AODJet2.Energy();

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
***/
        outTree->Fill();
    }// end event loop


    std::cout << "Offline Numbers" << std::endl;
    std::cout << "DiTau" << '\t' << "Old" << '\t' << "New" << '\t' << "New2" << '\t' << "Passing" << std::endl;
    std::cout << passDiTau_OffCount << '\t' << passOld_OffCount << '\t' << passNew_OffCount << '\t' << passNew2_OffCount << '\t' << "Event#" << std::endl;
    std::cout << "HTT" << '\t' << "HTT350" << std::endl;
    std::cout << passHTTCount << '\t' << passHTT350Count << std::endl;

    std::cout << passDiTauOffORHTT << '\t' << "Pass DiTau Offline OR HTT" << std::endl;
    std::cout << passDiTauOffORHTT350 << '\t' << "Pass DiTau Offline OR HTT350" << std::endl;
    std::cout << passDiTauOROld_Off << '\t' << "Pass DiTau OR Old" << std::endl;
    std::cout << passDiTauORNew2_Off << '\t' << "Pass DiTau OR New2" << std::endl;
    std::cout << passOldORNew2_Off << '\t' << "Pass Old OR New2" << std::endl;
    std::cout << passDiTauOROldORNew2_Off << '\t' << "Pass DiTau OR Old OR New2" << std::endl;

    std::cout << passDiTauOffANDHTT << '\t' << "Pass DiTau Offline AND HTT" << std::endl;
    std::cout << passDiTauOffANDHTT350 << '\t' << "Pass DiTau Offline AND HTT350" << std::endl;
    std::cout << passDiTauANDOld_Off << '\t' << "Pass DiTau AND Old" << std::endl;
    std::cout << passDiTauANDNew2_Off << '\t' << "Pass DiTau AND New2" << std::endl;
    std::cout << passOldANDNew2_Off << '\t' << "Pass Old AND New2" << std::endl;
    std::cout << passDiTauANDOldANDNew2_Off << '\t' << "Pass DiTau AND Old AND New2" << std::endl;

    std::cout << "L1 Numbers" << std::endl;
    std::cout << "DiTau" << '\t' << "Old" << '\t' << "New" << '\t' << "New2" << '\t' << "Passing" << std::endl;
    std::cout << passDiTau_L1Count << '\t' << passOld_L1Count << '\t' << passNew_L1Count << '\t' << passNew2_L1Count << '\t' << "Event#" << std::endl;

    std::cout << passDiTauL1ORHTT << '\t' << "Pass DiTau L1 OR HTT" << std::endl;
    std::cout << passDiTauL1ORHTT350 << '\t' << "Pass DiTau L1 OR HTT350" << std::endl;
    std::cout << passDiTauOROld_L1 << '\t' << "Pass DiTau OR Old" << std::endl;
    std::cout << passDiTauORNew2_L1 << '\t' << "Pass DiTau OR New2" << std::endl;
    std::cout << passOldORNew2_L1 << '\t' << "Pass Old OR New2" << std::endl;
    std::cout << passDiTauOROldORNew2_L1 << '\t' << "Pass DiTau OR Old OR New2" << std::endl;

    std::cout << passDiTauL1ANDHTT << '\t' << "Pass DiTau L1 AND HTT" << std::endl;
    std::cout << passDiTauL1ANDHTT350 << '\t' << "Pass DiTau L1 AND HTT350" << std::endl;
    std::cout << passDiTauANDOld_L1 << '\t' << "Pass DiTau AND Old" << std::endl;
    std::cout << passDiTauANDNew2_L1 << '\t' << "Pass DiTau AND New2" << std::endl;
    std::cout << passOldANDNew2_L1 << '\t' << "Pass Old AND New2" << std::endl;
    std::cout << passDiTauANDOldANDNew2_L1 << '\t' << "Pass DiTau AND Old AND New2" << std::endl;

    std::cout << "Passing L1 AND Offline" << std::endl;
    std::cout << passDiTauL1ANDOff << '\t' << "DiTau" << std::endl;
    std::cout << passOldL1ANDOff << '\t' << "Old" << std::endl;
    std::cout << passNewL1ANDOff << '\t' << "New" << std::endl;
    std::cout << passNew2L1ANDOff << '\t' << "New2" << std::endl;
    std::cout << passOldNew2L1ANDOff << '\t' << "Old AND New2" << std::endl;
    std::cout << passDiTauL1ANDNew2L1ANDOff << '\t' << "DiTau L1 AND New2 L1 AND Off" << std::endl;
    std::cout << passDiTauL1ANDOldNew2L1ANDOff << '\t' << "DiTau L1, Old AND New2 Offline AND L1" << std::endl;
    std::cout << passDiTauOldNew2L1ANDOff << '\t' << "DiTau AND Old AND New2" << std::endl;
    std::cout << passDiTauL1ANDHTT350ANDOldNew2L1ANDOff << '\t' << "Pass DiTau L1 AND HTT350, Old AND New2 Offline AND L1" << std::endl;
    std::cout << passDiTauL1ANDHTT350ANDNew2L1ANDOff << '\t' << "Pass DiTau L1 AND HTT350 AND New2 Offline AND L1" << std::endl;

    std::cout << "I'm tired" << std::endl;
    std::cout << passOldORNewL1ANDOff << '\t' << "Old OR New L1 AND Off" << std::endl;
    std::cout << passDiTauANDHTT350ANDOldORNewL1ANDOff << '\t' << "DiTau AND HTT350 AND (Old OR New2 L1 AND Offline)" << std::endl;

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
