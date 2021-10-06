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
    //int passDiTauOffORHTT = 0;
    //int passDiTauOffORHTT350 = 0;
    //int passDiTauOffANDHTT = 0;
    //int passDiTauOffANDHTT350 = 0;
    //int passDiTauL1ORHTT = 0;
    //int passDiTauL1ORHTT350 = 0;
    //int passDiTauL1ANDHTT = 0;
    //int passDiTauL1ANDHTT350 = 0;



    int passDiTau32_Off = 0;
    int passDiTau35_Off = 0;
    int passOld_Off = 0;
    int passNew_Off = 0;
    int passNew2_Off = 0;

    int passDiTau32_OffCount = 0;
    int passDiTau35_OffCount = 0;
    int passOld_OffCount = 0;
    int passNew_OffCount = 0;
    int passNew2_OffCount = 0;

    int passDiTau32_L1 = 0;
    int passDiTau35_L1 = 0;
    int passOld_L1 = 0;
    int passNew_L1 = 0;
    int passNew2_L1 = 0;

    int passDiTau32_L1Count = 0;
    int passDiTau35_L1Count = 0;
    int passOld_L1Count = 0;
    int passNew_L1Count = 0;
    int passNew2_L1Count = 0;

    int passDiTau32L1ANDOff = 0;
    int passDiTau35L1ANDOff = 0;
    int passOldL1ANDOff = 0;
    int passNewL1ANDOff = 0;
    int passNew2L1ANDOff = 0;

    // {L1, Off., Both}
    int passDiTau32_Counter[3] = {0, 0, 0};
    int passDiTau35_Counter[3] = {0, 0, 0};
    int passOld_Counter[3] = {0, 0, 0};
    int passNew_Counter[3] = {0, 0, 0};
    int passNew2_Counter[4] = {0, 0, 0, 0};
/***
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
***/

    int passL1ANDOffDiTau35ORNew2ANDHTT350 = 0;
    int passL1ANDOffDiTau32ANDHTT350 = 0;

    // {L1, Offline, Both, Both OR DiTau35}
    // jet35, tauYY
    int passJet35_Tau46_MassAnyTwo400_Counter[4] = {0, 0, 0, 0};

    int passJet35_Tau45_MassAnyTwo400_Counter[4] = {0, 0, 0, 0};

    int passJet35_Tau42_MassAnyTwo450_Counter[4] = {0, 0, 0, 0};

    int passJet35_Tau38_MassAnyTwo500_Counter[4] = {0, 0, 0, 0};

    int passJet35_Tau48_MassAnyTwo550_Counter[4] = {0, 0, 0, 0};

    int passJet35_Tau35_MassAnyTwo600_Counter[4] = {0, 0, 0, 0};
    // jet40, tauYY
    int passJet40_Tau40_MassAnyTwo400_Counter[4] = {0, 0, 0, 0};

    int passJet40_Tau36_MassAnyTwo450_Counter[4] = {0, 0, 0, 0};

    int passJet40_Tau34_MassAnyTwo500_Counter[4] = {0, 0, 0, 0};

    int passJet40_Tau32_MassAnyTwo550_Counter[4] = {0, 0, 0, 0};

    int passJet40_Tau28_MassAnyTwo600_Counter[4] = {0, 0, 0, 0};
    // jet45, tauYY
    int passJet45_Tau34_MassAnyTwo400_Counter[4] = {0, 0, 0, 0};

    int passJet45_Tau28_MassAnyTwo450_Counter[4] = {0, 0, 0, 0};

    int passJet45_Tau28_MassAnyTwo500_Counter[4] = {0, 0, 0, 0};

    int passJet45_Tau28_MassAnyTwo550_Counter[4] = {0, 0, 0, 0};
    // jet50, tauYY
    int passJet50_Tau28_MassAnyTwo400_Counter[4] = {0, 0, 0, 0};

    int passJet50_Tau25_MassAnyTwo450_Counter[4] = {0, 0, 0, 0};




    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 60001; ++iEntry) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

        passHTT = 0;
        passHTT350 = 0;

        passDiTau32_Off = 0;
        passDiTau35_Off = 0;
        passOld_Off = 0;
        passNew_Off = 0;
        passNew2_Off = 0;

        passDiTau32_L1 = 0;
        passDiTau35_L1 = 0;
        passOld_L1 = 0;
        passNew_L1 = 0;
        passNew2_L1 = 0;


	//---------------------apply base selection and fill AOD objects------------------------------//
	min_cutflow->Fill(0.0,1.0); // fill cutflow before any selection

	int vecSizeAODTau = inTree->tauPt->size(); // number of taus in event
	int vecSizeAODJet = inTree->jetPt->size(); // number of jets in event
	min_cutflow->Fill(1.0,1.0);
	min_cutflow->Fill(2.0,1.0); 
	// fill cutflow with events that have 2 taus and 2 jets
	// check kinematics and ID of tau objects, store good taus
	std::vector<TLorentzVector> isoTau25AODCands;	
	for (int iTau = 0; iTau < vecSizeAODTau; ++iTau) {
            bool passTauID = false;
	    deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
	    deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
            deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
	    if (deepTauVSjet && deepTauVSmu && deepTauVSele) passTauID = true;

	    if (passTauID && inTree->tauPt->at(iTau) >= 25 && fabs(inTree->tauEta->at(iTau) <= 2.1)) {
	      TLorentzVector tauCand;
	      tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau),
				     inTree->tauEta->at(iTau), 
				     inTree->tauPhi->at(iTau), 
				     inTree->tauEnergy->at(iTau));
	      isoTau25AODCands.push_back(tauCand);
            }
	}
        int isoTau25AODCandsSize = isoTau25AODCands.size();
        if (isoTau25AODCandsSize < 2) continue; // need two taus minimum


	// take first two AOD taus that aren't overlapped
	// isoTau25AODCands are already ordered by pt (this was checked with simple cout statements)
	TLorentzVector AODTau1, AODTau2;
	AODTau1.SetPtEtaPhiE(isoTau25AODCands.at(0).Pt(), 
                             isoTau25AODCands.at(0).Eta(), 
                             isoTau25AODCands.at(0).Phi(), 
                             isoTau25AODCands.at(0).Energy());
	for (std::vector<TLorentzVector>::const_iterator iTau = isoTau25AODCands.begin()+1; iTau != isoTau25AODCands.end(); ++iTau) {
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
	std::vector<TLorentzVector> jet30Cands;
	for (int iJet = 0; iJet < vecSizeAODJet; ++iJet){

            bool passJetID = false;
	    if (inTree->jetID->at(iJet) >= 6) passJetID = true; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

	    if (passJetID && inTree->jetPt->at(iJet) >= 30 && fabs(inTree->jetEta->at(iJet) <= 4.7)) {
	      TLorentzVector jetCand;
	      jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
				     inTree->jetEta->at(iJet), 
				     inTree->jetPhi->at(iJet), 
				     inTree->jetEn->at(iJet));
	      // if a jetCandidate looks like it could be either tau we already selected, don't store it
	      bool jetCandIsTau = false;
	      if (AODTau1.DeltaR(jetCand) < 0.5 || AODTau2.DeltaR(jetCand) < 0.5) jetCandIsTau = true;

	      if (!jetCandIsTau) jet30Cands.push_back(jetCand);
            }
	}
	// check that we have at least two good jets
	int jet30CandsSize = jet30Cands.size(); 
        if (jet30CandsSize < 2) continue;

	// fill AOD jets with pair of jets that produced the largest mjj value
	// from cout statements, AODJet1 was verified to be leading jet
	TLorentzVector AODJet1, AODJet2;
        std::tie(AODJet1, AODJet2) = highestMassPair(jet30Cands);

	min_cutflow->Fill(4.0,1.0);
	sel_cutflow->Fill(1.0,1.0);


	// ad hoc pass sel...
        // common to all
        // all possible mass pairs to check
	double mj1j2 = (AODJet1 + AODJet2).M();
	double mj1t1 = (AODJet1 + AODTau1).M(); 
	double mj1t2 = (AODJet1 + AODTau2).M();
	double mj2t1 = (AODJet2 + AODTau1).M();
	double mj2t2 = (AODJet2 + AODTau2).M();
	//double mt1t2 = (AODTau1 + AODTau2).M();

        int pass2Mass400 = (mj1j2 >= 400 || mj1t1 >= 400 || mj1t2 >= 400 || mj2t1 >= 400 || mj2t2 >= 400);
        int pass2Mass450 = (mj1j2 >= 450 || mj1t1 >= 450 || mj1t2 >= 450 || mj2t1 >= 450 || mj2t2 >= 450);
        int pass2Mass500 = (mj1j2 >= 500 || mj1t1 >= 500 || mj1t2 >= 500 || mj2t1 >= 500 || mj2t2 >= 500);
        int pass2Mass550 = (mj1j2 >= 550 || mj1t1 >= 550 || mj1t2 >= 550 || mj2t1 >= 550 || mj2t2 >= 550);
        int pass2Mass600 = (mj1j2 >= 600 || mj1t1 >= 600 || mj1t2 >= 600 || mj2t1 >= 600 || mj2t2 >= 600);
        int pass2Mass650 = (mj1j2 >= 650 || mj1t1 >= 650 || mj1t2 >= 650 || mj2t1 >= 650 || mj2t2 >= 650);

        double AODJet1Pt_ = AODJet1.Pt();	
        double AODJet2Pt_ = AODJet2.Pt();	
        double AODTau1Pt_ = AODTau1.Pt();
        double AODTau2Pt_ = AODTau2.Pt();

        if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && AODTau1Pt_ >= 40 && AODTau2Pt_ >= 40) passHTT = 1;
        passHTTCount += passHTT;
        if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && AODTau1Pt_ >= 40 && AODTau2Pt_ >= 40 && mj1j2 >= 350) passHTT350 = 1;
        passHTT350Count += passHTT350;

        //int dEtajj = abs(AODJet1.Eta() - AODJet2.Eta());
        if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && AODTau1Pt_ >= 50 && AODTau2Pt_ >= 40 && pass2Mass600) passDiTau32_Off = 1;
        passDiTau32_Counter[1] += passDiTau32_Off;
        if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && AODTau1Pt_ >= 53 && AODTau2Pt_ >= 43 && pass2Mass600) passDiTau35_Off = 1;
        passDiTau35_Counter[1] += passDiTau35_Off;

	if (AODJet1Pt_ >= 120 && AODJet2Pt_ >= 45 && AODTau1Pt_ >= 25 && AODTau2Pt_ >= 25 && mj1j2 >= 700) passOld_Off = 1;
        passOld_Counter[1] += passOld_Off;
	
        if (AODJet1Pt_ >= 45 && AODJet2Pt_ >= 45 && AODTau1Pt_ >= 50 && AODTau2Pt_ >= 25 && mj1j2 >= 550) passNew_Off = 1;
        passNew_Counter[1] += passNew_Off;

        if (AODJet1Pt_ >= (35+10) && AODJet2Pt_ >= (35+10) && AODTau1Pt_ >= (45+18) && AODTau2Pt_ >= 25 && pass2Mass450) passNew2_Off = 1;
        passNew2_Counter[1] += passNew2_Off;

        // new vbf seed variations
        // define L1 then see if the offline version is passed (+10 jets, +15 taus, +50 MassAnyTwo)
        // do literally one variation 35 46 400
        int offJetInc = 10;
	int offTauInc = 18;
        int offM2Inc = 50;

        // jet 35 variations
        int passJet35_Tau45_MassAnyTwo400_L1[4] = {35, 45, 400, 0};
        int passJet35_Tau45_MassAnyTwo400_Off[4] = {35+offJetInc, 45+offTauInc, 400+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet35_Tau45_MassAnyTwo400_Off[0] && AODJet2Pt_ >= passJet35_Tau45_MassAnyTwo400_Off[0] &&
            AODTau1Pt_ >= passJet35_Tau45_MassAnyTwo400_Off[1] && AODTau2Pt_ >= 25 && pass2Mass450) passJet35_Tau45_MassAnyTwo400_Off[3] = 1;
        passJet35_Tau45_MassAnyTwo400_Counter[1] += passJet35_Tau45_MassAnyTwo400_Off[3];

        int passJet35_Tau46_MassAnyTwo400_L1[4] = {35, 46, 400, 0};
        int passJet35_Tau46_MassAnyTwo400_Off[4] = {35+offJetInc, 46+offTauInc, 400+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet35_Tau46_MassAnyTwo400_Off[0] && AODJet2Pt_ >= passJet35_Tau46_MassAnyTwo400_Off[0] &&
            AODTau1Pt_ >= passJet35_Tau46_MassAnyTwo400_Off[1] && AODTau2Pt_ >= 25 && pass2Mass450) passJet35_Tau46_MassAnyTwo400_Off[3] = 1;
        passJet35_Tau46_MassAnyTwo400_Counter[1] += passJet35_Tau46_MassAnyTwo400_Off[3];

        int passJet35_Tau42_MassAnyTwo450_L1[4] = {35, 42, 450, 0};
        int passJet35_Tau42_MassAnyTwo450_Off[4] = {35+offJetInc, 42+offTauInc, 450+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet35_Tau42_MassAnyTwo450_Off[0] && AODJet2Pt_ >= passJet35_Tau42_MassAnyTwo450_Off[0] &&
            AODTau1Pt_ >= passJet35_Tau42_MassAnyTwo450_Off[1] && AODTau2Pt_ >= 25 && pass2Mass500) passJet35_Tau42_MassAnyTwo450_Off[3] = 1;
        passJet35_Tau42_MassAnyTwo450_Counter[1] += passJet35_Tau42_MassAnyTwo450_Off[3];

        int passJet35_Tau38_MassAnyTwo500_L1[4] = {35, 38, 500, 0}; 
        int passJet35_Tau38_MassAnyTwo500_Off[4] = {35+offJetInc, 38+offTauInc, 500+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet35_Tau38_MassAnyTwo500_Off[0] && AODJet2Pt_ >= passJet35_Tau38_MassAnyTwo500_Off[0] &&
            AODTau1Pt_ >= passJet35_Tau38_MassAnyTwo500_Off[1] && AODTau2Pt_ >= 25 && pass2Mass550) passJet35_Tau38_MassAnyTwo500_Off[3] = 1;
        passJet35_Tau38_MassAnyTwo500_Counter[1] += passJet35_Tau38_MassAnyTwo500_Off[3];

        int passJet35_Tau48_MassAnyTwo550_L1[4] = {35, 48, 550, 0};
        int passJet35_Tau48_MassAnyTwo550_Off[4] = {35+offJetInc, 48+offTauInc, 550+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet35_Tau48_MassAnyTwo550_Off[0] && AODJet2Pt_ >= passJet35_Tau48_MassAnyTwo550_Off[0] &&
            AODTau1Pt_ >= passJet35_Tau48_MassAnyTwo550_Off[1] && AODTau2Pt_ >= 25 && pass2Mass600) passJet35_Tau48_MassAnyTwo550_Off[3] = 1;
        passJet35_Tau48_MassAnyTwo550_Counter[1] += passJet35_Tau48_MassAnyTwo550_Off[3];

        int passJet35_Tau35_MassAnyTwo600_L1[4] = {35, 35, 600, 0};
        int passJet35_Tau35_MassAnyTwo600_Off[4] = {35+offJetInc, 35+offTauInc, 600+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet35_Tau35_MassAnyTwo600_Off[0] && AODJet2Pt_ >= passJet35_Tau35_MassAnyTwo600_Off[0] &&
            AODTau1Pt_ >= passJet35_Tau35_MassAnyTwo600_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet35_Tau35_MassAnyTwo600_Off[3] = 1;
        passJet35_Tau35_MassAnyTwo600_Counter[1] += passJet35_Tau35_MassAnyTwo600_Off[3];

        // jet 40 variations
        int passJet40_Tau40_MassAnyTwo400_L1[4] = {40, 40, 400, 0};
        int passJet40_Tau40_MassAnyTwo400_Off[4] = {40+offJetInc, 40+offTauInc, 400+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet40_Tau40_MassAnyTwo400_Off[0] && AODJet2Pt_ >= passJet40_Tau40_MassAnyTwo400_Off[0] &&
            AODTau1Pt_ >= passJet40_Tau40_MassAnyTwo400_Off[1] && AODTau2Pt_ >= 25 && pass2Mass450) passJet40_Tau40_MassAnyTwo400_Off[3] = 1;
        passJet40_Tau40_MassAnyTwo400_Counter[1] += passJet40_Tau40_MassAnyTwo400_Off[3];

        int passJet40_Tau36_MassAnyTwo450_L1[4] = {40, 36, 450, 0};
        int passJet40_Tau36_MassAnyTwo450_Off[4] = {40+offJetInc, 36+offTauInc, 450+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet40_Tau36_MassAnyTwo450_Off[0] && AODJet2Pt_ >= passJet40_Tau36_MassAnyTwo450_Off[0] &&
            AODTau1Pt_ >= passJet40_Tau36_MassAnyTwo450_Off[1] && AODTau2Pt_ >= 25 && pass2Mass500) passJet40_Tau36_MassAnyTwo450_Off[3] = 1;
        passJet40_Tau36_MassAnyTwo450_Counter[1] += passJet40_Tau36_MassAnyTwo450_Off[3];

        int passJet40_Tau34_MassAnyTwo500_L1[4] = {40, 34, 500, 0};
        int passJet40_Tau34_MassAnyTwo500_Off[4] = {40+offJetInc, 34+offTauInc, 500+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet40_Tau34_MassAnyTwo500_Off[0] && AODJet2Pt_ >= passJet40_Tau34_MassAnyTwo500_Off[0] &&
            AODTau1Pt_ >= passJet40_Tau34_MassAnyTwo500_Off[1] && AODTau2Pt_ >= 25 && pass2Mass550) passJet40_Tau34_MassAnyTwo500_Off[3] = 1;
        passJet40_Tau34_MassAnyTwo500_Counter[1] += passJet40_Tau34_MassAnyTwo500_Off[3];

        int passJet40_Tau32_MassAnyTwo550_L1[4] = {40, 32, 550, 0};
        int passJet40_Tau32_MassAnyTwo550_Off[4] = {40+offJetInc, 32+offTauInc, 550+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet40_Tau32_MassAnyTwo550_Off[0] && AODJet2Pt_ >= passJet40_Tau32_MassAnyTwo550_Off[0] &&
            AODTau1Pt_ >= passJet40_Tau32_MassAnyTwo550_Off[1] && AODTau2Pt_ >= 25 && pass2Mass600) passJet40_Tau32_MassAnyTwo550_Off[3] = 1;
        passJet40_Tau32_MassAnyTwo550_Counter[1] += passJet40_Tau32_MassAnyTwo550_Off[3];

        int passJet40_Tau28_MassAnyTwo600_L1[4] = {40, 28, 600, 0};
        int passJet40_Tau28_MassAnyTwo600_Off[4] = {40+offJetInc, 28+offTauInc, 600+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet40_Tau28_MassAnyTwo600_Off[0] && AODJet2Pt_ >= passJet40_Tau28_MassAnyTwo600_Off[0] &&
            AODTau1Pt_ >= passJet40_Tau28_MassAnyTwo600_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet40_Tau28_MassAnyTwo600_Off[3] = 1;
        passJet40_Tau28_MassAnyTwo600_Counter[1] += passJet40_Tau28_MassAnyTwo600_Off[3];

        // jet45 variations
        int passJet45_Tau34_MassAnyTwo400_L1[4] = {45, 34, 400, 0};
        int passJet45_Tau34_MassAnyTwo400_Off[4] = {45+offJetInc, 34+offTauInc, 400+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet45_Tau34_MassAnyTwo400_Off[0] && AODJet2Pt_ >= passJet45_Tau34_MassAnyTwo400_Off[0] &&
            AODTau1Pt_ >= passJet45_Tau34_MassAnyTwo400_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet45_Tau34_MassAnyTwo400_Off[3] = 1;
        passJet45_Tau34_MassAnyTwo400_Counter[1] += passJet45_Tau34_MassAnyTwo400_Off[3];

        int passJet45_Tau28_MassAnyTwo450_L1[4] = {45, 28, 450, 0};
        int passJet45_Tau28_MassAnyTwo450_Off[4] = {45+offJetInc, 28+offTauInc, 450+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet45_Tau28_MassAnyTwo450_Off[0] && AODJet2Pt_ >= passJet45_Tau28_MassAnyTwo450_Off[0] &&
            AODTau1Pt_ >= passJet45_Tau28_MassAnyTwo450_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet45_Tau28_MassAnyTwo450_Off[3] = 1;
        passJet45_Tau28_MassAnyTwo450_Counter[1] += passJet45_Tau28_MassAnyTwo450_Off[3];

        int passJet45_Tau28_MassAnyTwo500_L1[4] = {45, 28, 500, 0};
        int passJet45_Tau28_MassAnyTwo500_Off[4] = {45+offJetInc, 28+offTauInc, 500+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet45_Tau28_MassAnyTwo500_Off[0] && AODJet2Pt_ >= passJet45_Tau28_MassAnyTwo500_Off[0] &&
            AODTau1Pt_ >= passJet45_Tau28_MassAnyTwo500_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet45_Tau28_MassAnyTwo500_Off[3] = 1;
        passJet45_Tau28_MassAnyTwo500_Counter[1] += passJet45_Tau28_MassAnyTwo500_Off[3];

        int passJet45_Tau28_MassAnyTwo550_L1[4] = {45, 28, 550, 0};
        int passJet45_Tau28_MassAnyTwo550_Off[4] = {45+offJetInc, 28+offTauInc, 550+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet45_Tau28_MassAnyTwo550_Off[0] && AODJet2Pt_ >= passJet45_Tau28_MassAnyTwo550_Off[0] &&
            AODTau1Pt_ >= passJet45_Tau28_MassAnyTwo550_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet45_Tau28_MassAnyTwo550_Off[3] = 1;
        passJet45_Tau28_MassAnyTwo550_Counter[1] += passJet45_Tau28_MassAnyTwo550_Off[3];

        // jet50 variations
        int passJet50_Tau28_MassAnyTwo400_L1[4] = {50, 28, 400, 0};
        int passJet50_Tau28_MassAnyTwo400_Off[4] = {50+offJetInc, 28+offTauInc, 400+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet50_Tau28_MassAnyTwo400_Off[0] && AODJet2Pt_ >= passJet50_Tau28_MassAnyTwo400_Off[0] &&
            AODTau1Pt_ >= passJet50_Tau28_MassAnyTwo400_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet50_Tau28_MassAnyTwo400_Off[3] = 1;
        passJet50_Tau28_MassAnyTwo400_Counter[1] += passJet50_Tau28_MassAnyTwo400_Off[3];

        int passJet50_Tau25_MassAnyTwo450_L1[4] = {50, 25, 450, 0};
        int passJet50_Tau25_MassAnyTwo450_Off[4] = {50+offJetInc, 25+offTauInc, 450+offM2Inc, 0};
        if (AODJet1Pt_ >= passJet50_Tau25_MassAnyTwo450_Off[0] && AODJet2Pt_ >= passJet50_Tau25_MassAnyTwo450_Off[0] &&
            AODTau1Pt_ >= passJet50_Tau25_MassAnyTwo450_Off[1] && AODTau2Pt_ >= 25 && pass2Mass650) passJet50_Tau25_MassAnyTwo450_Off[3] = 1;
        passJet50_Tau25_MassAnyTwo450_Counter[1] += passJet50_Tau25_MassAnyTwo450_Off[3];


	//---------------------L1----------------------------//

	// fill object containers
	int primL1JetSize = inTree->jetL1PrimitivesPt->size();
	std::vector<TLorentzVector> jet30L1Cands = hltFillWithCands(inTree, "jetL1Primitives", primL1JetSize, 30);
	int jet30L1Size = jet30L1Cands.size();

        std::vector<TLorentzVector> jet35L1Cands;
        std::vector<TLorentzVector> jet40L1Cands;
        std::vector<TLorentzVector> jet45L1Cands;
        std::vector<TLorentzVector> jet50L1Cands;
        for (int iJet = 0; iJet < jet30L1Size; ++iJet) {
          TLorentzVector tempJet_ = jet30L1Cands.at(iJet);
          if (tempJet_.Pt() >= 35) jet35L1Cands.push_back(tempJet_);
          if (tempJet_.Pt() >= 40) jet40L1Cands.push_back(tempJet_);
          if (tempJet_.Pt() >= 45) jet45L1Cands.push_back(tempJet_);
          if (tempJet_.Pt() >= 50) jet50L1Cands.push_back(tempJet_);
        }
        int jet35L1Size = jet35L1Cands.size();
        int jet40L1Size = jet40L1Cands.size();
        int jet45L1Size = jet45L1Cands.size();
        int jet50L1Size = jet50L1Cands.size();

	int primL1TauSize = inTree->tauL1PrimitivesPt->size();

	std::vector<TLorentzVector> tau25L1Cands = hltFillWithCands(inTree, "tauL1Primitives", primL1TauSize, 25);
	int tau25L1Size = tau25L1Cands.size();

	std::vector<TLorentzVector> isoTau25L1Cands;
        for (int iTau = 0; iTau < tau25L1Size; ++iTau) {
          TLorentzVector tempTau_ = tau25L1Cands.at(iTau);
          if (tempTau_.Pt() >= 25 && inTree->tauL1PrimitivesIso->at(iTau)) isoTau25L1Cands.push_back(tempTau_);
        }
        int isoTau25L1Size = isoTau25L1Cands.size();

        std::vector<TLorentzVector> isoTau28L1Cands;
        std::vector<TLorentzVector> isoTau30L1Cands;
        std::vector<TLorentzVector> isoTau32L1Cands;
        std::vector<TLorentzVector> isoTau34L1Cands;
        std::vector<TLorentzVector> isoTau35L1Cands;
        std::vector<TLorentzVector> isoTau36L1Cands;
        std::vector<TLorentzVector> isoTau38L1Cands;
	std::vector<TLorentzVector> isoTau40L1Cands;
	std::vector<TLorentzVector> isoTau42L1Cands;
        std::vector<TLorentzVector> isoTau45L1Cands;
	std::vector<TLorentzVector> isoTau46L1Cands;
	std::vector<TLorentzVector> isoTau48L1Cands;
	for (int iTau = 0; iTau < isoTau25L1Size; ++iTau) {
          TLorentzVector tempTau_ = tau25L1Cands.at(iTau);
          if (tempTau_.Pt() > 28) isoTau28L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 30) isoTau30L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 32) isoTau32L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 34) isoTau34L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 35) isoTau35L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 36) isoTau36L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 38) isoTau38L1Cands.push_back(tempTau_);
	  if (tempTau_.Pt() > 40) isoTau40L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 42) isoTau42L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 45) isoTau45L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 46) isoTau46L1Cands.push_back(tempTau_);
          if (tempTau_.Pt() > 48) isoTau48L1Cands.push_back(tempTau_);
	}
        int isoTau28L1Size = isoTau28L1Cands.size();
        int isoTau30L1Size = isoTau30L1Cands.size();
        int isoTau32L1Size = isoTau32L1Cands.size();
        int isoTau34L1Size = isoTau34L1Cands.size();
        int isoTau35L1Size = isoTau35L1Cands.size();
        int isoTau36L1Size = isoTau36L1Cands.size();
        int isoTau38L1Size = isoTau38L1Cands.size();
	int isoTau40L1Size = isoTau40L1Cands.size();
        int isoTau42L1Size = isoTau42L1Cands.size();
	int isoTau45L1Size = isoTau45L1Cands.size();
        int isoTau46L1Size = isoTau46L1Cands.size();
        int isoTau48L1Size = isoTau48L1Cands.size();

	// perform cross-cleaning (cc) (Wrt = with respect to)
	// standard
	std::vector<TLorentzVector> jet30CandsRmvOlTauCandsIso40 = crossCleanJets(jet30L1Cands, isoTau40L1Cands);
        int jet30CandsRmvOlTauCandsIso40Size = jet30CandsRmvOlTauCandsIso40.size();

        std::vector<TLorentzVector> jet30CandsRmvOlTauCandsIso45 = crossCleanJets(jet30L1Cands, isoTau45L1Cands);
        int jet30CandsRmvOlTauCandsIso45Size = jet30CandsRmvOlTauCandsIso45.size();

        // for variations
        // jet 35, tau YY
	std::vector<TLorentzVector> jet35CandsRmvOlTauCandsIso35 = crossCleanJets(jet35L1Cands, isoTau35L1Cands);
        int jet35CandsRmvOlTauCandsIso35Size = jet35CandsRmvOlTauCandsIso35.size();

	std::vector<TLorentzVector> jet35CandsRmvOlTauCandsIso38 = crossCleanJets(jet35L1Cands, isoTau38L1Cands);
        int jet35CandsRmvOlTauCandsIso38Size = jet35CandsRmvOlTauCandsIso38.size();

	std::vector<TLorentzVector> jet35CandsRmvOlTauCandsIso42 = crossCleanJets(jet35L1Cands, isoTau42L1Cands);
        int jet35CandsRmvOlTauCandsIso42Size = jet35CandsRmvOlTauCandsIso42.size();

	std::vector<TLorentzVector> jet35CandsRmvOlTauCandsIso45 = crossCleanJets(jet35L1Cands, isoTau45L1Cands);
        int jet35CandsRmvOlTauCandsIso45Size = jet35CandsRmvOlTauCandsIso45.size();

	std::vector<TLorentzVector> jet35CandsRmvOlTauCandsIso46 = crossCleanJets(jet35L1Cands, isoTau46L1Cands);
        int jet35CandsRmvOlTauCandsIso46Size = jet35CandsRmvOlTauCandsIso46.size();

	std::vector<TLorentzVector> jet35CandsRmvOlTauCandsIso48 = crossCleanJets(jet35L1Cands, isoTau48L1Cands);
        int jet35CandsRmvOlTauCandsIso48Size = jet35CandsRmvOlTauCandsIso48.size();

        //jet 40, tau YY
        std::vector<TLorentzVector> jet40CandsRmvOlTauCandsIso40 = crossCleanJets(jet40L1Cands, isoTau40L1Cands);
        int jet40CandsRmvOlTauCandsIso40Size = jet40CandsRmvOlTauCandsIso40.size();

        std::vector<TLorentzVector> jet40CandsRmvOlTauCandsIso36 = crossCleanJets(jet40L1Cands, isoTau36L1Cands);
        int jet40CandsRmvOlTauCandsIso36Size = jet40CandsRmvOlTauCandsIso36.size();

        std::vector<TLorentzVector> jet40CandsRmvOlTauCandsIso34 = crossCleanJets(jet40L1Cands, isoTau34L1Cands);
        int jet40CandsRmvOlTauCandsIso34Size = jet40CandsRmvOlTauCandsIso34.size();

        std::vector<TLorentzVector> jet40CandsRmvOlTauCandsIso32 = crossCleanJets(jet40L1Cands, isoTau32L1Cands);
        int jet40CandsRmvOlTauCandsIso32Size = jet40CandsRmvOlTauCandsIso32.size();

        std::vector<TLorentzVector> jet40CandsRmvOlTauCandsIso28 = crossCleanJets(jet40L1Cands, isoTau28L1Cands);
        int jet40CandsRmvOlTauCandsIso28Size = jet40CandsRmvOlTauCandsIso28.size();

        //jet 45, tau YY
        std::vector<TLorentzVector> jet45CandsRmvOlTauCandsIso34 = crossCleanJets(jet45L1Cands, isoTau34L1Cands);
        int jet45CandsRmvOlTauCandsIso34Size = jet45CandsRmvOlTauCandsIso34.size();

        std::vector<TLorentzVector> jet45CandsRmvOlTauCandsIso28 = crossCleanJets(jet45L1Cands, isoTau28L1Cands);
        int jet45CandsRmvOlTauCandsIso28Size = jet45CandsRmvOlTauCandsIso28.size();

        //jet50, tau YY
        std::vector<TLorentzVector> jet50CandsRmvOlTauCandsIso28 = crossCleanJets(jet50L1Cands, isoTau28L1Cands);
        int jet50CandsRmvOlTauCandsIso28Size = jet50CandsRmvOlTauCandsIso28.size();

        std::vector<TLorentzVector> jet50CandsRmvOlTauCandsIso25 = crossCleanJets(jet50L1Cands, isoTau25L1Cands);
        int jet50CandsRmvOlTauCandsIso25Size = jet50CandsRmvOlTauCandsIso25.size();


        // all necessary collections are built, now see if they pass trigger thresholds

        // DiTaus
        if (isoTau32L1Size >= 2) passDiTau32_L1 = 1;
        passDiTau32_Counter[0] += passDiTau32_L1;
        int passBothDiTau32 = (passDiTau32_L1 && passDiTau32_Off);
        passDiTau32_Counter[2] += passBothDiTau32;

        if (isoTau35L1Size >= 2) passDiTau35_L1 = 1;
        passDiTau35_Counter[0] += passDiTau35_L1;
        int passBothDiTau35 = (passDiTau35_L1 && passDiTau35_Off);
        passDiTau35_Counter[2] += passBothDiTau35;


        // old VBF
	if (jet30L1Size >= 2) {

          bool jet110Present = false;
	  for (int iJet = 0; iJet < jet30L1Size; ++iJet) {
	    if (jet30L1Cands.at(iJet).Pt() >= 110) jet110Present = true;
	  }

          float mjj_Old = 0; float tempMjj_ = 0;
          for (int iJet = 0; iJet < jet30L1Size; ++iJet) {
            for (int jJet = 0; jJet < jet30L1Size; ++jJet) {
              if (iJet >= jJet) continue;
              if (jet30L1Cands.at(iJet).Pt() < 110 && jet30L1Cands.at(jJet).Pt() < 110 && !jet110Present) continue;
              tempMjj_ = (jet30L1Cands.at(iJet) + jet30L1Cands.at(jJet)).M();
              if (tempMjj_ > mjj_Old) mjj_Old = tempMjj_;
            }
          }
          if (mjj_Old >= 620) passOld_L1 = 1;
          passOld_Counter[0] += passOld_L1;
        }
        int passBothOld = (passOld_L1 && passOld_Off);
        passOld_Counter[2] += passBothOld;

        //newVBF
	if (jet30CandsRmvOlTauCandsIso45Size >= 2 && isoTau45L1Size >= 1) {
	  // check mjj
	  float mjj_New = 0; float tempMjj_ = 0;
          for (int iJet = 0; iJet < jet30CandsRmvOlTauCandsIso45Size; ++iJet) {
            for (int jJet = 0; jJet < jet30CandsRmvOlTauCandsIso45Size; ++jJet) {
              if (iJet >= jJet) continue;
              tempMjj_ = (jet30CandsRmvOlTauCandsIso45.at(iJet) + jet30CandsRmvOlTauCandsIso45.at(jJet)).M();
              if (tempMjj_ > mjj_New) mjj_New = tempMjj_;
            }
          }
          if (mjj_New >= 450) passNew_L1 = 1;
          passNew_Counter[0] += passNew_L1;
	} 
        int passBothNew = (passNew_L1 && passNew_Off);
        passNew_Counter[2] += passBothNew;

        // newVBF2
	if (jet35CandsRmvOlTauCandsIso45Size >= 2 && isoTau45L1Size >= 1) {
          float mjotjot_New2 = highestMassOfPair(jet35CandsRmvOlTauCandsIso45, isoTau45L1Cands);
          if (mjotjot_New2 >= 400) passNew2_L1 = 1;
          passNew2_Counter[0] += passNew2_L1;
	}
        int passBothNew2 = (passNew2_L1 && passNew2_Off);
        passNew2_Counter[2] += passBothNew2;
        passNew2_Counter[3] += (passBothNew2 || passBothDiTau35);


        // variations of newVBFSeed2
        // check if size criteria are passed, then check mass req, then increment L1 counter, 
        // then increment Both counter if L1 and Off are both passed

        // jet 35, Tau YY
        if (jet35CandsRmvOlTauCandsIso45Size >= 2 && isoTau45L1Size >= 1) {
          float mjotjot_3545400 = highestMassOfPair(jet35CandsRmvOlTauCandsIso45, isoTau45L1Cands);
          if (mjotjot_3545400 >= passJet35_Tau45_MassAnyTwo400_L1[2]) passJet35_Tau45_MassAnyTwo400_L1[3] = 1;
        }
	passJet35_Tau45_MassAnyTwo400_Counter[0] += passJet35_Tau45_MassAnyTwo400_L1[3];
        int passBoth3545400 = (passJet35_Tau45_MassAnyTwo400_L1[3] && passJet35_Tau45_MassAnyTwo400_Off[3]);
	passJet35_Tau45_MassAnyTwo400_Counter[2] += passBoth3545400;
	passJet35_Tau45_MassAnyTwo400_Counter[3] += (passBoth3545400 || passBothDiTau35);

        if (jet35CandsRmvOlTauCandsIso46Size >= 2 && isoTau46L1Size >= 1) {
          float mjotjot_3546400 = highestMassOfPair(jet35CandsRmvOlTauCandsIso46, isoTau46L1Cands);
          if (mjotjot_3546400 >= passJet35_Tau46_MassAnyTwo400_L1[2]) passJet35_Tau46_MassAnyTwo400_L1[3] = 1;
        }
	passJet35_Tau46_MassAnyTwo400_Counter[0] += passJet35_Tau46_MassAnyTwo400_L1[3];
        int passBoth3546400 = (passJet35_Tau46_MassAnyTwo400_L1[3] && passJet35_Tau46_MassAnyTwo400_Off[3]);
	passJet35_Tau46_MassAnyTwo400_Counter[2] += passBoth3546400;
	passJet35_Tau46_MassAnyTwo400_Counter[3] += (passBoth3546400 || passBothDiTau35);

        if (jet35CandsRmvOlTauCandsIso42Size >= 2 && isoTau42L1Size >= 1) {
          float mjotjot_3542450 = highestMassOfPair(jet35CandsRmvOlTauCandsIso42, isoTau42L1Cands);
          if (mjotjot_3542450 >= passJet35_Tau42_MassAnyTwo450_L1[2]) passJet35_Tau42_MassAnyTwo450_L1[3] = 1;
        }
	passJet35_Tau42_MassAnyTwo450_Counter[0] += passJet35_Tau42_MassAnyTwo450_L1[3];
	int passBoth3542450 = (passJet35_Tau42_MassAnyTwo450_L1[3] && passJet35_Tau42_MassAnyTwo450_Off[3]);
	passJet35_Tau42_MassAnyTwo450_Counter[2] += passBoth3542450;
	passJet35_Tau42_MassAnyTwo450_Counter[3] += (passBoth3542450 || passBothDiTau35);

        if (jet35CandsRmvOlTauCandsIso38Size >= 2 && isoTau38L1Size >= 1) {
          float mjotjot_3538500 = highestMassOfPair(jet35CandsRmvOlTauCandsIso38, isoTau38L1Cands);
          if (mjotjot_3538500 >= passJet35_Tau38_MassAnyTwo500_L1[2]) passJet35_Tau38_MassAnyTwo500_L1[3] = 1;
        }
	passJet35_Tau38_MassAnyTwo500_Counter[0] += passJet35_Tau38_MassAnyTwo500_L1[3];
	int passBoth3538500 = (passJet35_Tau38_MassAnyTwo500_L1[3] && passJet35_Tau38_MassAnyTwo500_Off[3]);
	passJet35_Tau38_MassAnyTwo500_Counter[2] += passBoth3538500;
	passJet35_Tau38_MassAnyTwo500_Counter[3] += (passBoth3538500 || passBothDiTau35);

        if (jet35CandsRmvOlTauCandsIso48Size >= 2 && isoTau48L1Size >= 1) {
          float mjotjot_3548550 = highestMassOfPair(jet35CandsRmvOlTauCandsIso48, isoTau48L1Cands);
          if (mjotjot_3548550 >= passJet35_Tau48_MassAnyTwo550_L1[2]) passJet35_Tau48_MassAnyTwo550_L1[3] = 1;
        }
	passJet35_Tau48_MassAnyTwo550_Counter[0] += passJet35_Tau48_MassAnyTwo550_L1[3];
	int passBoth3548550 = (passJet35_Tau48_MassAnyTwo550_L1[3] && passJet35_Tau48_MassAnyTwo550_Off[3]);
	passJet35_Tau48_MassAnyTwo550_Counter[2] += passBoth3548550;
	passJet35_Tau48_MassAnyTwo550_Counter[3] += (passBoth3548550 || passBothDiTau35);

        if (jet35CandsRmvOlTauCandsIso35Size >= 2 && isoTau35L1Size >= 1) {
          float mjotjot_3535600 = highestMassOfPair(jet35CandsRmvOlTauCandsIso35, isoTau35L1Cands);
          if (mjotjot_3535600 >= passJet35_Tau35_MassAnyTwo600_L1[2]) passJet35_Tau35_MassAnyTwo600_L1[3] = 1;
        }
	passJet35_Tau35_MassAnyTwo600_Counter[0] += passJet35_Tau35_MassAnyTwo600_L1[3];
	int passBoth3535600 = (passJet35_Tau35_MassAnyTwo600_L1[3] && passJet35_Tau35_MassAnyTwo600_Off[3]);
	passJet35_Tau35_MassAnyTwo600_Counter[2] += passBoth3535600;
	passJet35_Tau35_MassAnyTwo600_Counter[3] += (passBoth3535600 || passBothDiTau35);

        // jet 40, tau YY
        if (jet40CandsRmvOlTauCandsIso40Size >= 2 && isoTau40L1Size >= 1) {
          float mjotjot_4040400 = highestMassOfPair(jet40CandsRmvOlTauCandsIso40, isoTau40L1Cands);
          if (mjotjot_4040400 >= passJet40_Tau40_MassAnyTwo400_L1[2]) passJet40_Tau40_MassAnyTwo400_L1[3] = 1;
        }
	passJet40_Tau40_MassAnyTwo400_Counter[0] += passJet40_Tau40_MassAnyTwo400_L1[3];
	int passBoth4040400 = (passJet40_Tau40_MassAnyTwo400_L1[3] && passJet40_Tau40_MassAnyTwo400_Off[3]);
	passJet40_Tau40_MassAnyTwo400_Counter[2] += passBoth4040400;
	passJet40_Tau40_MassAnyTwo400_Counter[3] += (passBoth4040400 || passBothDiTau35);

        if (jet40CandsRmvOlTauCandsIso36Size >= 2 && isoTau36L1Size >= 1) {
          float mjotjot_4036450 = highestMassOfPair(jet40CandsRmvOlTauCandsIso36, isoTau36L1Cands);
          if (mjotjot_4036450 >= passJet40_Tau36_MassAnyTwo450_L1[2]) passJet40_Tau36_MassAnyTwo450_L1[3] = 1;
        }
	passJet40_Tau36_MassAnyTwo450_Counter[0] += passJet40_Tau36_MassAnyTwo450_L1[3];
	int passBoth4036450 = (passJet40_Tau36_MassAnyTwo450_L1[3] && passJet40_Tau36_MassAnyTwo450_Off[3]);
	passJet40_Tau36_MassAnyTwo450_Counter[2] += passBoth4036450;
	passJet40_Tau36_MassAnyTwo450_Counter[3] += (passBoth4036450 || passBothDiTau35);

        if (jet40CandsRmvOlTauCandsIso34Size >= 2 && isoTau34L1Size >= 1) {
          float mjotjot_4034500 = highestMassOfPair(jet40CandsRmvOlTauCandsIso34, isoTau34L1Cands);
          if (mjotjot_4034500 >= passJet40_Tau34_MassAnyTwo500_L1[2]) passJet40_Tau34_MassAnyTwo500_L1[3] = 1;
        }
	passJet40_Tau34_MassAnyTwo500_Counter[0] += passJet40_Tau34_MassAnyTwo500_L1[3];
	int passBoth4034500 = (passJet40_Tau34_MassAnyTwo500_L1[3] && passJet40_Tau34_MassAnyTwo500_Off[3]);
	passJet40_Tau34_MassAnyTwo500_Counter[2] += passBoth4034500;
	passJet40_Tau34_MassAnyTwo500_Counter[3] += (passBoth4034500 || passBothDiTau35);

        if (jet40CandsRmvOlTauCandsIso32Size >= 2 && isoTau32L1Size >= 1) {
          float mjotjot_4032550 = highestMassOfPair(jet40CandsRmvOlTauCandsIso32, isoTau32L1Cands);
          if (mjotjot_4032550 >= passJet40_Tau32_MassAnyTwo550_L1[2]) passJet40_Tau32_MassAnyTwo550_L1[3] = 1;
        }
	passJet40_Tau32_MassAnyTwo550_Counter[0] += passJet40_Tau32_MassAnyTwo550_L1[3];
	int passBoth4032550 = (passJet40_Tau32_MassAnyTwo550_L1[3] && passJet40_Tau32_MassAnyTwo550_Off[3]);
	passJet40_Tau32_MassAnyTwo550_Counter[2] += passBoth4032550;
	passJet40_Tau32_MassAnyTwo550_Counter[3] += (passBoth4032550 || passBothDiTau35);

        if (jet40CandsRmvOlTauCandsIso28Size >= 2 && isoTau28L1Size >= 1) {
          float mjotjot_4028600 = highestMassOfPair(jet40CandsRmvOlTauCandsIso28, isoTau28L1Cands);
          if (mjotjot_4028600 >= passJet40_Tau28_MassAnyTwo600_L1[2]) passJet40_Tau28_MassAnyTwo600_L1[3] = 1;
        }
	passJet40_Tau28_MassAnyTwo600_Counter[0] += passJet40_Tau28_MassAnyTwo600_L1[3];
	int passBoth4028600 = (passJet40_Tau28_MassAnyTwo600_L1[3] && passJet40_Tau28_MassAnyTwo600_Off[3]);
	passJet40_Tau28_MassAnyTwo600_Counter[2] += passBoth4028600;
	passJet40_Tau28_MassAnyTwo600_Counter[3] += (passBoth4028600 || passBothDiTau35);

        //jet45, tau YY
        if (jet45CandsRmvOlTauCandsIso34Size >= 2 && isoTau34L1Size >= 1) {
          float mjotjot_4534400 = highestMassOfPair(jet45CandsRmvOlTauCandsIso34, isoTau34L1Cands);
          if (mjotjot_4534400 >= passJet45_Tau34_MassAnyTwo400_L1[2]) passJet45_Tau34_MassAnyTwo400_L1[3] = 1;
        }
	passJet45_Tau34_MassAnyTwo400_Counter[0] += passJet45_Tau34_MassAnyTwo400_L1[3];
	int passBoth4534400 = (passJet45_Tau34_MassAnyTwo400_L1[3] && passJet45_Tau34_MassAnyTwo400_Off[3]);
	passJet45_Tau34_MassAnyTwo400_Counter[2] += passBoth4534400;
	passJet45_Tau34_MassAnyTwo400_Counter[3] += (passBoth4534400 || passBothDiTau35);

       if (jet45CandsRmvOlTauCandsIso28Size >= 2 && isoTau28L1Size >= 1) {
          float mjotjot_4528450 = highestMassOfPair(jet45CandsRmvOlTauCandsIso28, isoTau28L1Cands);
          if (mjotjot_4528450 >= passJet45_Tau28_MassAnyTwo450_L1[2]) passJet45_Tau28_MassAnyTwo450_L1[3] = 1;
        }
	passJet45_Tau28_MassAnyTwo450_Counter[0] += passJet45_Tau28_MassAnyTwo450_L1[3];
	int passBoth4528450 = (passJet45_Tau28_MassAnyTwo450_L1[3] && passJet45_Tau28_MassAnyTwo450_Off[3]);
	passJet45_Tau28_MassAnyTwo450_Counter[2] += passBoth4528450;
	passJet45_Tau28_MassAnyTwo450_Counter[3] += (passBoth4528450 || passBothDiTau35);

        if (jet45CandsRmvOlTauCandsIso28Size >= 2 && isoTau28L1Size >= 1) {
          float mjotjot_4528500 = highestMassOfPair(jet45CandsRmvOlTauCandsIso28, isoTau28L1Cands);
          if (mjotjot_4528500 >= passJet45_Tau28_MassAnyTwo500_L1[2]) passJet45_Tau28_MassAnyTwo500_L1[3] = 1;
        }
	passJet45_Tau28_MassAnyTwo500_Counter[0] += passJet45_Tau28_MassAnyTwo500_L1[3];
	int passBoth4528500 = (passJet45_Tau28_MassAnyTwo500_L1[3] && passJet45_Tau28_MassAnyTwo500_Off[3]);
	passJet45_Tau28_MassAnyTwo500_Counter[2] += passBoth4528500;
	passJet45_Tau28_MassAnyTwo500_Counter[3] += (passBoth4528500 || passBothDiTau35);

        if (jet45CandsRmvOlTauCandsIso28Size >= 2 && isoTau28L1Size >= 1) {
          float mjotjot_4528550 = highestMassOfPair(jet45CandsRmvOlTauCandsIso28, isoTau28L1Cands);
          if (mjotjot_4528550 >= passJet45_Tau28_MassAnyTwo550_L1[2]) passJet45_Tau28_MassAnyTwo550_L1[3] = 1;
        }
	passJet45_Tau28_MassAnyTwo550_Counter[0] += passJet45_Tau28_MassAnyTwo550_L1[3];
	int passBoth4528550 = (passJet45_Tau28_MassAnyTwo550_L1[3] && passJet45_Tau28_MassAnyTwo550_Off[3]);
	passJet45_Tau28_MassAnyTwo550_Counter[2] += passBoth4528550;
	passJet45_Tau28_MassAnyTwo550_Counter[3] += (passBoth4528550 || passBothDiTau35);

        //jet50, tau YY
        if (jet50CandsRmvOlTauCandsIso28Size >= 2 && isoTau28L1Size >= 1) {
          float mjotjot_5028400 = highestMassOfPair(jet50CandsRmvOlTauCandsIso28, isoTau28L1Cands);
          if (mjotjot_5028400 >= passJet50_Tau28_MassAnyTwo400_L1[2]) passJet50_Tau28_MassAnyTwo400_L1[3] = 1;
        }
	passJet50_Tau28_MassAnyTwo400_Counter[0] += passJet50_Tau28_MassAnyTwo400_L1[3];
	int passBoth5028400 = (passJet50_Tau28_MassAnyTwo400_L1[3] && passJet50_Tau28_MassAnyTwo400_Off[3]);
	passJet50_Tau28_MassAnyTwo400_Counter[2] += passBoth5028400;
	passJet50_Tau28_MassAnyTwo400_Counter[3] += (passBoth5028400 || passBothDiTau35);

        if (jet50CandsRmvOlTauCandsIso25Size >= 2 && isoTau25L1Size >= 1) {
          float mjotjot_5025450 = highestMassOfPair(jet50CandsRmvOlTauCandsIso25, isoTau25L1Cands);
          if (mjotjot_5025450 >= passJet50_Tau25_MassAnyTwo450_L1[2]) passJet50_Tau25_MassAnyTwo450_L1[3] = 1;
        }
	passJet50_Tau25_MassAnyTwo450_Counter[0] += passJet50_Tau25_MassAnyTwo450_L1[3];
	int passBoth5025450 = (passJet50_Tau25_MassAnyTwo450_L1[3] && passJet50_Tau25_MassAnyTwo450_Off[3]);
	passJet50_Tau25_MassAnyTwo450_Counter[2] += passBoth5025450;
	passJet50_Tau25_MassAnyTwo450_Counter[3] += (passBoth5025450 || passBothDiTau35);



        // I think Olivier wants the HTT350?
        //numerator
        passL1ANDOffDiTau35ORNew2ANDHTT350 += (((passBothDiTau35) || (passBothOld) || (passBothNew2)) && passHTT350);
        //denominator
        passL1ANDOffDiTau32ANDHTT350 += (((passBothDiTau32) || (passBothOld)) && passHTT350);

        // Keti does not want the HTT350, so all the variations we've made don't have that
        // and we just use passBothDiTau32 as the denominator


/***
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
***/

	
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
    std::cout << "DiTau32" << '\t' << "DiTau35" << '\t' << "Old" << '\t' << "New" << '\t' << "New2" << '\t' << "Passing" << std::endl;
    std::cout << passDiTau32_Counter[1] << '\t' << passDiTau35_Counter[1] << '\t' << passOld_Counter[1] << '\t' << passNew_Counter[1] << '\t' << passNew2_Counter[1] << '\t' << "Event#" << std::endl;
    std::cout << "HTT" << '\t' << "HTT350" << std::endl;
    std::cout << passHTTCount << '\t' << passHTT350Count << std::endl;

/***
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
***/
    std::cout << "L1 Numbers" << std::endl;
    std::cout << "DiTau32" << '\t' << "DiTau35" << '\t' << "Old" << '\t' << "New" << '\t' << "New2" << '\t' << "Passing" << std::endl;
    std::cout << passDiTau32_Counter[0] << '\t' << passDiTau35_Counter[0] << '\t' << passOld_Counter[0] << '\t' << passNew_Counter[0] << '\t' << passNew2_Counter[0] << '\t' << "Event#" << std::endl;

/***
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
***/
    std::cout << "Passing L1 AND Offline" << std::endl;
    std::cout << "DiTau32" << '\t' << "DiTau35" << '\t' << "Old" << '\t' << "New" << '\t' << "New2" << '\t' << "Passing" << std::endl;
    std::cout << passDiTau32_Counter[2] << '\t' << passDiTau35_Counter[2] << '\t' << passOld_Counter[2] << '\t' << passNew_Counter[2] << '\t' << passNew2_Counter[2] << '\t' << "Event#" << std::endl;
/***
    std::cout << passOldNew2L1ANDOff << '\t' << "Old AND New2" << std::endl;
    std::cout << passDiTauL1ANDNew2L1ANDOff << '\t' << "DiTau L1 AND New2 L1 AND Off" << std::endl;
    std::cout << passDiTauL1ANDOldNew2L1ANDOff << '\t' << "DiTau L1, Old AND New2 Offline AND L1" << std::endl;
    std::cout << passDiTauOldNew2L1ANDOff << '\t' << "DiTau AND Old AND New2" << std::endl;
    std::cout << passDiTauL1ANDHTT350ANDOldNew2L1ANDOff << '\t' << "Pass DiTau L1 AND HTT350, Old AND New2 Offline AND L1" << std::endl;
    std::cout << passDiTauL1ANDHTT350ANDNew2L1ANDOff << '\t' << "Pass DiTau L1 AND HTT350 AND New2 Offline AND L1" << std::endl;
***/
    //std::cout << "I'm tired" << std::endl;
    //std::cout << passOldORNewL1ANDOff << '\t' << "Old OR New L1 AND Off" << std::endl;
    //std::cout << passDiTauANDHTT350ANDOldORNewL1ANDOff << '\t' << "DiTau AND HTT350 AND (Old OR New2 L1 AND Offline)" << std::endl;
    std::cout << passL1ANDOffDiTau35ORNew2ANDHTT350 << " num = pass L1 and Off for (DiTau35 or New2) and Htt" << std::endl;
    std::cout << passL1ANDOffDiTau32ANDHTT350 << " denom = pass L1 and Off for (DiTau32) and Htt" << std::endl;
    std::cout << "New2 DoubleJet35_IsoTau45_MassAnyTwo400_RmvOl" << std::endl;
    std::cout << "L1" << '\t' << "Off." << '\t' << "Both" << '\t' << "Both & DiTau35" << std::endl;
    std::cout << passNew2_Counter[0]
              << '\t' << passNew2_Counter[1] 
              << '\t' << passNew2_Counter[2]
              << '\t' << passNew2_Counter[3] 
              << '\t' << "from 35 45 400 L1, add 10 15 50 for offline" << std::endl;
    std::cout << "variations passing" << std::endl;
    std::cout << "L1" << '\t' << "Off." << '\t' << "Both" << '\t' << "Both & DiTau35" << std::endl;
    std::cout << passJet35_Tau45_MassAnyTwo400_Counter[0] 
              << '\t' << passJet35_Tau45_MassAnyTwo400_Counter[1] 
              << '\t' << passJet35_Tau45_MassAnyTwo400_Counter[2] 
              << '\t' << passJet35_Tau45_MassAnyTwo400_Counter[3] 
              << '\t' << " from 35 45 400 L1, add 10 15 50 for offline (STANDARD)" << std::endl;
    std::cout << passJet35_Tau46_MassAnyTwo400_Counter[0] 
              << '\t' << passJet35_Tau46_MassAnyTwo400_Counter[1] 
              << '\t' << passJet35_Tau46_MassAnyTwo400_Counter[2] 
              << '\t' << passJet35_Tau46_MassAnyTwo400_Counter[3] 
              << '\t' << " from 35 46 400 L1, add 10 15 50 for offline" << std::endl;
    std::cout << passJet35_Tau42_MassAnyTwo450_Counter[0] 
              << '\t' << passJet35_Tau42_MassAnyTwo450_Counter[1] 
              << '\t' << passJet35_Tau42_MassAnyTwo450_Counter[2] 
              << '\t' << passJet35_Tau42_MassAnyTwo450_Counter[3] 
              << '\t' << " from 35 42 450 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet35_Tau38_MassAnyTwo500_Counter[0] 
              << '\t' << passJet35_Tau38_MassAnyTwo500_Counter[1] 
              << '\t' << passJet35_Tau38_MassAnyTwo500_Counter[2] 
              << '\t' << passJet35_Tau38_MassAnyTwo500_Counter[3] 
              << '\t' << " from 35 38 500 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet35_Tau48_MassAnyTwo550_Counter[0] 
              << '\t' << passJet35_Tau48_MassAnyTwo550_Counter[1] 
              << '\t' << passJet35_Tau48_MassAnyTwo550_Counter[2] 
              << '\t' << passJet35_Tau48_MassAnyTwo550_Counter[3] 
              << '\t' << " from 35 48 550 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet35_Tau35_MassAnyTwo600_Counter[0] 
              << '\t' << passJet35_Tau35_MassAnyTwo600_Counter[1] 
              << '\t' << passJet35_Tau35_MassAnyTwo600_Counter[2] 
              << '\t' << passJet35_Tau35_MassAnyTwo600_Counter[3] 
              << '\t' << " from 35 35 600 L1, add 10 15 50 for offline " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << passJet40_Tau40_MassAnyTwo400_Counter[0] 
              << '\t' << passJet40_Tau40_MassAnyTwo400_Counter[1] 
              << '\t' << passJet40_Tau40_MassAnyTwo400_Counter[2] 
              << '\t' << passJet40_Tau40_MassAnyTwo400_Counter[3] 
              << '\t' << " from 40 40 400 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet40_Tau36_MassAnyTwo450_Counter[0] 
              << '\t' << passJet40_Tau36_MassAnyTwo450_Counter[1] 
              << '\t' << passJet40_Tau36_MassAnyTwo450_Counter[2] 
              << '\t' << passJet40_Tau36_MassAnyTwo450_Counter[3] 
              << '\t' << " from 40 36 450 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet40_Tau34_MassAnyTwo500_Counter[0] 
              << '\t' << passJet40_Tau34_MassAnyTwo500_Counter[1] 
              << '\t' << passJet40_Tau34_MassAnyTwo500_Counter[2] 
              << '\t' << passJet40_Tau34_MassAnyTwo500_Counter[3] 
              << '\t' << " from 40 34 500 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet40_Tau32_MassAnyTwo550_Counter[0] 
              << '\t' << passJet40_Tau32_MassAnyTwo550_Counter[1] 
              << '\t' << passJet40_Tau32_MassAnyTwo550_Counter[2] 
              << '\t' << passJet40_Tau32_MassAnyTwo550_Counter[3] 
              << '\t' << " from 40 32 550 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet40_Tau28_MassAnyTwo600_Counter[0] 
              << '\t' << passJet40_Tau28_MassAnyTwo600_Counter[1] 
              << '\t' << passJet40_Tau28_MassAnyTwo600_Counter[2] 
              << '\t' << passJet40_Tau28_MassAnyTwo600_Counter[3] 
              << '\t' << " from 40 28 600 L1, add 10 15 50 for offline " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << passJet45_Tau34_MassAnyTwo400_Counter[0] 
              << '\t' << passJet45_Tau34_MassAnyTwo400_Counter[1] 
              << '\t' << passJet45_Tau34_MassAnyTwo400_Counter[2] 
              << '\t' << passJet45_Tau34_MassAnyTwo400_Counter[3] 
              << '\t' << " from 45 34 400 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet45_Tau28_MassAnyTwo450_Counter[0] 
              << '\t' << passJet45_Tau28_MassAnyTwo450_Counter[1] 
              << '\t' << passJet45_Tau28_MassAnyTwo450_Counter[2] 
              << '\t' << passJet45_Tau28_MassAnyTwo450_Counter[3] 
              << '\t' << " from 45 28 450 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet45_Tau28_MassAnyTwo500_Counter[0] 
              << '\t' << passJet45_Tau28_MassAnyTwo500_Counter[1] 
              << '\t' << passJet45_Tau28_MassAnyTwo500_Counter[2] 
              << '\t' << passJet45_Tau28_MassAnyTwo500_Counter[3] 
              << '\t' << " from 45 28 500 L1, add 10 15 50 for offline " << std::endl;
    std::cout << passJet45_Tau28_MassAnyTwo550_Counter[0] 
              << '\t' << passJet45_Tau28_MassAnyTwo550_Counter[1] 
              << '\t' << passJet45_Tau28_MassAnyTwo550_Counter[2] 
              << '\t' << passJet45_Tau28_MassAnyTwo550_Counter[3] 
              << '\t' << " from 45 28 550 L1, add 10 15 50 for offline " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << passJet50_Tau28_MassAnyTwo400_Counter[0] 
              << '\t' << passJet50_Tau28_MassAnyTwo400_Counter[1] 
              << '\t' << passJet50_Tau28_MassAnyTwo400_Counter[2] 
              << '\t' << passJet50_Tau28_MassAnyTwo400_Counter[3] 
              << '\t' << " from 50 28 400 L1, add 10 15 50 for offline " << std::endl;
     std::cout << passJet50_Tau25_MassAnyTwo450_Counter[0] 
              << '\t' << passJet50_Tau25_MassAnyTwo450_Counter[1] 
              << '\t' << passJet50_Tau25_MassAnyTwo450_Counter[2] 
              << '\t' << passJet50_Tau25_MassAnyTwo450_Counter[3] 
              << '\t' << " from 50 25 450 L1, add 10 15 50 for offline " << std::endl;
 


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
