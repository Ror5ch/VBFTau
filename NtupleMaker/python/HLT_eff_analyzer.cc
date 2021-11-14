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

    // run variables and branches
    int nEvents, runNumber, lumiBlock, eventNumberID;
    outTree->Branch("nEvents", &nEvents);
    outTree->Branch("runNumber", &runNumber);
    outTree->Branch("lumiBlock", &lumiBlock);
    outTree->Branch("eventNumberID", &eventNumberID);
    // Old VBF HLT variables and branches
    float j1_ptOld, j1_etaOld, j1_phiOld, j1_energyOld; 
    float j2_ptOld, j2_etaOld, j2_phiOld, j2_energyOld; 
    float mjjOld;
    float t1_ptOld, t1_etaOld, t1_phiOld, t1_energyOld;
    float t2_ptOld, t2_etaOld, t2_phiOld, t2_energyOld;
    outTree->Branch("j1_ptOld", &j1_ptOld);
    outTree->Branch("j1_etaOld", &j1_etaOld);
    outTree->Branch("j1_phiOld", &j1_phiOld);
    outTree->Branch("j2_ptOld", &j2_ptOld);
    outTree->Branch("j2_etaOld", &j2_etaOld);
    outTree->Branch("j2_phiOld", &j2_phiOld);
    outTree->Branch("mjjOld", &mjjOld);
    outTree->Branch("t1_ptOld", &t1_ptOld);
    outTree->Branch("t1_etaOld", &t1_etaOld);
    outTree->Branch("t1_phiOld", &t1_phiOld);
    outTree->Branch("t2_ptOld", &t2_ptOld);
    outTree->Branch("t2_etaOld", &t2_etaOld);
    outTree->Branch("t2_phiOld", &t2_phiOld);

    // New VBF HLT variables and branches
    float j1_ptNew, j1_etaNew, j1_phiNew, j1_energyNew; 
    float j2_ptNew, j2_etaNew, j2_phiNew, j2_energyNew; 
    float mjjNew;
    float t1_ptNew, t1_etaNew, t1_phiNew, t1_energyNew;
    float t2_ptNew, t2_etaNew, t2_phiNew, t2_energyNew;
    outTree->Branch("j1_ptNew", &j1_ptNew);
    outTree->Branch("j1_etaNew", &j1_etaNew);
    outTree->Branch("j1_phiNew", &j1_phiNew);
    outTree->Branch("j2_ptNew", &j2_ptNew);
    outTree->Branch("j2_etaNew", &j2_etaNew);
    outTree->Branch("j2_phiNew", &j2_phiNew);
    outTree->Branch("mjjNew", &mjjNew);
    outTree->Branch("t1_ptNew", &t1_ptNew);
    outTree->Branch("t1_etaNew", &t1_etaNew);
    outTree->Branch("t1_phiNew", &t1_phiNew);
    outTree->Branch("t2_ptNew", &t2_ptNew);
    outTree->Branch("t2_etaNew", &t2_etaNew);
    outTree->Branch("t2_phiNew", &t2_phiNew);

    // AOD variables and branches
    float j1_ptAOD, j1_etaAOD, j1_phiAOD, j1_energyAOD; 
    float j2_ptAOD, j2_etaAOD, j2_phiAOD, j2_energyAOD; 
    float mjjAOD;
    float t1_ptAOD, t1_etaAOD, t1_phiAOD, t1_energyAOD;
    float t2_ptAOD, t2_etaAOD, t2_phiAOD, t2_energyAOD;
    int deepTauVSjet, deepTauVSmu, deepTauVSele, jetID;
    outTree->Branch("j1_ptAOD", &j1_ptAOD);
    outTree->Branch("j1_etaAOD", &j1_etaAOD);
    outTree->Branch("j1_phiAOD", &j1_phiAOD);
    outTree->Branch("j2_ptAOD", &j2_ptAOD);
    outTree->Branch("j2_etaAOD", &j2_etaAOD);
    outTree->Branch("j2_phiAOD", &j2_phiAOD);
    outTree->Branch("mjjAOD", &mjjAOD);
    outTree->Branch("t1_ptAOD", &t1_ptAOD);
    outTree->Branch("t1_etaAOD", &t1_etaAOD);
    outTree->Branch("t1_phiAOD", &t1_phiAOD);
    outTree->Branch("t2_ptAOD", &t2_ptAOD);
    outTree->Branch("t2_etaAOD", &t2_etaAOD);
    outTree->Branch("t2_phiAOD", &t2_phiAOD);
    outTree->Branch("deepTauVSjet", &deepTauVSjet);
    outTree->Branch("deepTauVSmu", &deepTauVSmu);
    outTree->Branch("deepTauVSele", &deepTauVSele);
    outTree->Branch("jetID", &jetID);
    // we don't have branches for energy

    // variables and branches for matching
    float dRj1Old, dRj2Old, dRt1Old, dRt2Old;
    int matchedTausOld, matchedJetsOld, matchedBothOld;
    outTree->Branch("dRj1Old", &dRj1Old);
    outTree->Branch("dRj2Old", &dRj2Old);
    outTree->Branch("dRt1Old", &dRt1Old);
    outTree->Branch("dRt2Old", &dRt2Old);
    outTree->Branch("matchedJetsOld", &matchedJetsOld);
    outTree->Branch("matchedTausOld", &matchedTausOld);
    outTree->Branch("matchedBothOld", &matchedBothOld);

    // variables and branches for matching
    float dRj1New, dRj2New, dRt1New, dRt2New;
    int matchedTausNew, matchedJetsNew, matchedBothNew;
    outTree->Branch("dRj1New", &dRj1New);
    outTree->Branch("dRj2New", &dRj2New);
    outTree->Branch("dRt1New", &dRt1New);
    outTree->Branch("dRt2New", &dRt2New);
    outTree->Branch("matchedJetsNew", &matchedJetsNew);
    outTree->Branch("matchedTausNew", &matchedTausNew);
    outTree->Branch("matchedBothNew", &matchedBothNew);

    // path for old trigger
    int passhltL1VBFDiJetOR;
    int passhltHpsDoublePFTau20Old;
    int passhltHpsDoublePFTauTightOld;
    int passhltHpsDoublePFTauAgainstMuonTightOld;
    int passhltMatchedVBFTwoTight;
    int passhltMatchedVBFOneTight;
    outTree->Branch("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    outTree->Branch("passhltHpsDoublePFTau20Old", &passhltHpsDoublePFTau20Old);
    outTree->Branch("passhltHpsDoublePFTauTightOld", &passhltHpsDoublePFTauTightOld);
    outTree->Branch("passhltHpsDoublePFTauAgainstMuonTightOld", &passhltHpsDoublePFTauAgainstMuonTightOld);
    outTree->Branch("passhltMatchedVBFTwoTight", &passhltMatchedVBFTwoTight);
    outTree->Branch("passhltMatchedVBFOneTight", &passhltMatchedVBFOneTight);

    // path for new trigger
    int passhltL1VBFDiJetIsoTau;
    int passhltHpsDoublePFTau20New;
    int passhltHpsDoublePFTauTightNew;
    int passhltHpsDoublePFTauAgainstMuonTightNew;
    int passhltHpsPFTau50Tight;
    int passhltMatchedVBFIsoTauTwoTight;
    outTree->Branch("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);
    outTree->Branch("passhltHpsDoublePFTau20New", &passhltHpsDoublePFTau20New);
    outTree->Branch("passhltHpsDoublePFTauTightNew", &passhltHpsDoublePFTauTightNew);
    outTree->Branch("passhltHpsDoublePFTauAgainstMuonTightNew", &passhltHpsDoublePFTauAgainstMuonTightNew);
    outTree->Branch("passhltHpsPFTau50Tight", &passhltHpsPFTau50Tight);
    outTree->Branch("passhltMatchedVBFIsoTauTwoTight", &passhltMatchedVBFIsoTauTwoTight);

    // final HLT decisions (decision found separately in NtupleMaker than filter path above)
    int passOldVBFHLT, passOldVBFOff, passOldVBFBoth;
    int passNewVBFHLT, passNewVBFOff, passNewVBFBoth;
    outTree->Branch("passOldVBFHLT", &passOldVBFHLT);
    outTree->Branch("passOldVBFOff", &passOldVBFOff);
    outTree->Branch("passOldVBFBoth", &passOldVBFBoth);
    outTree->Branch("passNewVBFHLT", &passNewVBFHLT);
    outTree->Branch("passNewVBFOff", &passNewVBFOff);
    outTree->Branch("passNewVBFBoth", &passNewVBFBoth);

    // variables without branches
    int passDiTau32Off, passDiTau35Off;
    int passOldVBFL1Count = 0;
    int passOldVBFHLTCount = 0;
    int passNewVBFL1Count = 0;
    int passNewVBFHLTCount = 0;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 10001; ++iEntry) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	if (iEntry % 1000000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

        //-----------------fix HLT filter decisions from NtupleMaker-----------------------// 

        // fill Old VBF HLT filter flags after correcting NtupleMaker mistake
        passhltL1VBFDiJetOR = passhltHpsDoublePFTau20Old = passhltHpsDoublePFTauTightOld = 0;
        passhltHpsDoublePFTauAgainstMuonTightOld = passhltMatchedVBFTwoTight = passhltMatchedVBFOneTight = 0;

        passhltL1VBFDiJetOR = inTree->passhltL1VBFDiJetOR;
        if (passhltL1VBFDiJetOR) passhltHpsDoublePFTau20Old = inTree->passhltHpsDoublePFTau20;
        if (passhltHpsDoublePFTau20Old) passhltHpsDoublePFTauTightOld = inTree->passhltHpsDoublePFTauTight;
        if (passhltHpsDoublePFTauTightOld) passhltHpsDoublePFTauAgainstMuonTightOld = inTree->passhltHpsDoublePFTauAgainstMuonTight;
        if (passhltHpsDoublePFTauAgainstMuonTightOld) passhltMatchedVBFTwoTight = inTree->passhltMatchedVBFTwoTight;
        if (passhltMatchedVBFTwoTight) passhltMatchedVBFOneTight = inTree->passhltMatchedVBFOneTight;

        passOldVBFHLT = inTree->passOldTrigTight;

        passOldVBFL1Count += passhltL1VBFDiJetOR;
        passOldVBFHLTCount += passOldVBFHLT;


        // fill New VBF HLT filter flags after correcting NtupleMaker mistake
        passhltL1VBFDiJetIsoTau = passhltHpsDoublePFTau20New = passhltHpsDoublePFTauTightNew = 0;
        passhltHpsDoublePFTauAgainstMuonTightNew = passhltHpsPFTau50Tight = passhltMatchedVBFIsoTauTwoTight = 0;

        passhltL1VBFDiJetIsoTau = inTree->passhltL1VBFDiJetIsoTau;
        if (passhltL1VBFDiJetIsoTau) passhltHpsDoublePFTau20New = inTree->passhltHpsDoublePFTau20;
        if (passhltHpsDoublePFTau20New) passhltHpsDoublePFTauTightNew = inTree->passhltHpsDoublePFTauTight;
        if (passhltHpsDoublePFTauTightNew) passhltHpsDoublePFTauAgainstMuonTightNew = inTree->passhltHpsDoublePFTauAgainstMuonTight;
        if (passhltHpsDoublePFTauAgainstMuonTightNew) passhltHpsPFTau50Tight = inTree->passhltHpsPFTau50Tight;
        if (passhltHpsPFTau50Tight) passhltMatchedVBFIsoTauTwoTight = inTree->passhltMatchedVBFIsoTauTwoTight;

        passNewVBFHLT = inTree->passNewTrigTight;

        passNewVBFL1Count += passhltL1VBFDiJetIsoTau;
        passNewVBFHLTCount += passNewVBFHLT;


	//---------------------apply AOD selection and fill AOD objects------------------------------//

        int viable = 1;

	int sizeAODTau = inTree->tauPt->size(); // number of taus in event
	int sizeAODJet = inTree->jetPt->size(); // number of jets in event
	// check kinematics and ID of tau objects, store isolated taus w pt>=25 and eta<=2.1 taus
	std::vector<TLorentzVector> isoTau25AODCands;	
	for (int iTau = 0; iTau < sizeAODTau; ++iTau) {
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
        if (isoTau25AODCandsSize < 2) viable = 0; //continue; // need two taus minimum


	// use first two non-overlapped AOD taus
	// isoTau25AODCands are already ordered by pt (this was checked with simple cout statements)
	TLorentzVector AODTau1, AODTau2;
	if (viable) {
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
	  if (AODTau1.DeltaR(AODTau2) < 0.5) viable = 0; //continue; 
        } // end viable if statement


	// check kinematics and ID of jet objects, store jets w pt>=30 and eta<=4.7
	std::vector<TLorentzVector> jet30Cands;
	for (int iJet = 0; iJet < sizeAODJet; ++iJet){

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
        if (jet30CandsSize < 2) viable = 0; //continue;


	// fill AOD jets with pair of jets that produced the largest mjj value
	// from cout statements, AODJet1 was verified to be leading jet
	TLorentzVector AODJet1, AODJet2;
        if (viable) std::tie(AODJet1, AODJet2) = highestMassPair(jet30Cands);

        // revisit for matching...about25% of all events have multiple possible jet pairs
        // and about 20% of those actually have more than one pair passing mjj
        // although the jets aren't overlapped with the tau, it's possible we could have jets
        // that match our L1 jets but aren't selecting them. Obviously if they're there and they match
        // L1 then we'd like to use them.
        /*
        if (jet30CandsSize >= 2) {
          std::cout << jet30CandsSize << " jetCandsAfterCleaningSize" << std::endl;
          std::cout << sizeAODJet << " AOD jet size" << std::endl;
          int tempCounter = 0;
          TLorentzVector testJet1, testJet2;
          for (int iJet = 0; iJet < jet30CandsSize; ++iJet) {
            testJet1 = jet30Cands.at(iJet);
            for (int jJet = iJet + 1; jJet < jet30CandsSize; ++jJet) {
              testJet2 = jet30Cands.at(jJet);
              float tempMjj = (testJet1 + testJet2).M();
              if (tempMjj >= 450) tempCounter += 1;
            }
          }
          if (tempCounter >= 2) {
            std::cout << "twofer!" << std::endl;
          }
        }
        */



	// Check AOD Objects Pass Offline Selection
        passDiTau32Off = passDiTau35Off = passOldVBFOff = passNewVBFOff = 0;
        if (viable) {
	  double mj1j2 = (AODJet1 + AODJet2).M();

          double AODJet1Pt_ = AODJet1.Pt();	
          double AODJet2Pt_ = AODJet2.Pt();	
          double AODTau1Pt_ = AODTau1.Pt();
          double AODTau2Pt_ = AODTau2.Pt();

          //int dEtajj = abs(AODJet1.Eta() - AODJet2.Eta());
          int offJetInc = 10; // define offline as XX above/increase of L1 cuts
	  int offTau1Inc = 18;
          int offTau2Inc = 8;
          int offM2Inc = 50;


          if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && mj1j2 >= 600) {
            if (AODTau1Pt_ >= (32+offTau1Inc) && AODTau2Pt_ >= (32+offTau2Inc) ) passDiTau32Off = 1;
            if (AODTau1Pt_ >= (35+offTau1Inc) && AODTau2Pt_ >= (35+offTau2Inc) ) passDiTau35Off = 1;
          }

          // L1 DoubleJet_110_35_DoubleJet35_Mass_Min620
	  if (AODJet1Pt_ >= (110+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= 25 && AODTau2Pt_ >= 25 && mj1j2 >= 700) passOldVBFOff = 1;
        
          // L1 DoubleJet35_Mass_Min_450_IsoTau45_RmvOl
          if (AODJet1Pt_ >= (35+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= (45+offTau1Inc) && AODTau2Pt_ >= 25 && mj1j2 >= 500) passNewVBFOff = 1;
        } // end viable if statement
        //---------------------------match AOD and HLT------------------------------//

        // matching for HLT objects from Old VBF path
        TLorentzVector oldHLTJet1, oldHLTJet2, oldHLTTau1, oldHLTTau2;
        matchedJetsOld = matchedTausOld = matchedBothOld = 0;
        if (passOldVBFHLT && passOldVBFOff) { 
          int jet40NumOld = inTree->hltMatchedVBFTwoTight_pt->size(); // number of jets w pt>=40 from HLT filter
          int jet115NumOld = inTree->hltMatchedVBFOneTight_pt->size(); // number of jets w pt>=115 from HLT filter
          int tau20NumOld = inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size(); // number of taus w pt>=20 from HLT filter
          
          if (jet40NumOld >= 2 && jet115NumOld >= 1 && tau20NumOld >= 2) {
            std::vector<TLorentzVector> oldHLTJetCands, oldHLTTauCands;
            oldHLTJetCands = hltFillWithCands(inTree, "hltMatchedVBFTwoTight", jet40NumOld);
            oldHLTTauCands = hltFillWithCands(inTree, "hltHpsDoublePFTauAgainstMuonTight", tau20NumOld);
            // when filling, an eta cut is imposed which can reduce the size of the container

            dRj1Old, dRj2Old, dRt1Old, dRt2Old = 999;
            int overlappedOld = 0;
            if (oldHLTJetCands.size() >= 2 && oldHLTTauCands.size() >= 2) {
              std::tie(oldHLTJet1, oldHLTJet2) = matchTwoObjs(oldHLTJetCands, AODJet1, AODJet2);
              dRj1Old = oldHLTJet1.DeltaR(AODJet1);
              dRj2Old = oldHLTJet2.DeltaR(AODJet2);

              mjjOld = (oldHLTJet1 + oldHLTJet2).M();

              std::tie(oldHLTTau1, oldHLTTau2) = matchTwoObjs(oldHLTTauCands, AODTau1, AODTau2);
              dRt1Old = oldHLTTau1.DeltaR(AODTau1);
              dRt2Old = oldHLTTau2.DeltaR(AODTau2);

              // check same type object overlap
              if (oldHLTJet1.DeltaR(oldHLTJet2) < 0.5 || oldHLTTau1.DeltaR(oldHLTTau2) < 0.5) overlappedOld = 1;
              // check different type object overlap
              if (oldHLTJet1.DeltaR(oldHLTTau1) < 0.5 || oldHLTJet1.DeltaR(oldHLTTau2) < 0.5 ||
                  oldHLTJet2.DeltaR(oldHLTTau1) < 0.5 || oldHLTJet2.DeltaR(oldHLTTau2) < 0.5) overlappedOld = 1;

              if (!overlappedOld) {
                if (dRj1Old < 0.5 && dRj2Old < 0.5) matchedJetsOld = 1;
                if (dRt1Old < 0.5 && dRt2Old < 0.5) matchedTausOld = 1;
                if (matchedJetsOld && matchedTausOld) matchedBothOld = 1;
              }

            } // end if for dR calculations

          } // end if checking object size requirements

        } // end if for passing HLT and offline

        // matching for HLT objects from New VBF path
        TLorentzVector newHLTJet1, newHLTJet2, newHLTTau1, newHLTTau2;
        matchedJetsNew = matchedTausNew = matchedBothNew = 0;
        if (passNewVBFHLT && passNewVBFOff) {
          int jet40NumNew = inTree->hltMatchedVBFIsoTauTwoTight_pt->size(); // number of jets w pt>=40 from HLT filter
          int tau20NumNew = inTree->hltHpsDoublePFTauAgainstMuonTight_pt->size(); // number of taus w pt>=20 from HLT filter
          int tau45NumNew = inTree->hltHpsPFTau50Tight_pt->size(); // number of taus w pt>=45 from HLT filter
          // name says 50, but pt cut is corrected by hand in HLT config file
          
          if (jet40NumNew >= 2 && tau20NumNew >= 2 && tau45NumNew >= 1) {
            std::vector<TLorentzVector> newHLTJetCands, newHLTTauCands;
            newHLTJetCands = hltFillWithCands(inTree, "hltMatchedVBFIsoTauTwoTight", jet40NumNew);
            newHLTTauCands = hltFillWithCands(inTree, "hltHpsDoublePFTauAgainstMuonTight", tau20NumNew);
            // when filling, an eta cut is imposed which can reduce the size of the container

            dRj1New, dRj2New, dRt1New, dRt2New = 999;
            int overlappedNew = 0;
            if (newHLTJetCands.size() >= 2 && newHLTTauCands.size() >= 2) {
              std::tie(newHLTJet1, newHLTJet2) = matchTwoObjs(newHLTJetCands, AODJet1, AODJet2);
              dRj1New = newHLTJet1.DeltaR(AODJet1);
              dRj2New = newHLTJet2.DeltaR(AODJet2);

              mjjNew = (newHLTJet1 + newHLTJet2).M();

              std::tie(newHLTTau1, newHLTTau2) = matchTwoObjs(newHLTTauCands, AODTau1, AODTau2);
              dRt1New = newHLTTau1.DeltaR(AODTau1);
              dRt2New = newHLTTau2.DeltaR(AODTau2);

              // check same type object overlap
              if (newHLTJet1.DeltaR(newHLTJet2) < 0.5 || newHLTTau1.DeltaR(newHLTTau2) < 0.5) overlappedNew = 1;
              // check different type object overlap
              if (newHLTJet1.DeltaR(newHLTTau1) < 0.5 || newHLTJet1.DeltaR(newHLTTau2) < 0.5 ||
                  newHLTJet2.DeltaR(newHLTTau1) < 0.5 || newHLTJet2.DeltaR(newHLTTau2) < 0.5) overlappedNew = 1;

              if (!overlappedNew) {
                if (dRj1New < 0.5 && dRj2New < 0.5) matchedJetsNew = 1;
                if (dRt1New < 0.5 && dRt2New < 0.5) matchedTausNew = 1;
                if (matchedJetsNew && matchedTausNew) matchedBothNew = 1;
              }

            } // end if for dR calculations

          } // end if checking object size requirements

        } // end if for passing HLT and offline

        // fill branches if any offline selection is passed for AOD
        // fill branhces for Old or New HLT objects if they are matched to AOD

        j1_ptAOD = j1_etaAOD = j1_phiAOD = -999;
        j2_ptAOD = j2_etaAOD = j2_phiAOD = mjjAOD = -999;
        t1_ptAOD = t1_etaAOD = t1_phiAOD = -999;
        t2_ptAOD = t2_etaAOD = t2_phiAOD = -999;

        j1_ptOld = j1_etaOld = j1_phiOld = -999;
        j2_ptOld = j2_etaOld = j2_phiOld = mjjOld =-999;
        t1_ptOld = t1_etaOld = t1_phiOld = -999;
        t2_ptOld = t2_etaOld = t2_phiOld = -999;

        j1_ptNew = j1_etaNew = j1_phiNew = -999;
        j2_ptNew = j2_etaNew = j2_phiNew = mjjNew =-999;
        t1_ptNew = t1_etaNew = t1_phiNew = -999;
        t2_ptNew = t2_etaNew = t2_phiNew = -999;

        passOldVBFBoth = passNewVBFBoth = 0;
        passOldVBFBoth = (passOldVBFHLT && passOldVBFOff);
        passNewVBFBoth = (passNewVBFHLT && passNewVBFOff);

        if (passOldVBFOff || passNewVBFOff) {
          // AOD Branches
	  j1_ptAOD = AODJet1.Pt();
	  j1_etaAOD = AODJet1.Eta();
	  j1_phiAOD = AODJet1.Phi();
	  j2_ptAOD = AODJet2.Pt();
	  j2_etaAOD = AODJet2.Eta();
	  j2_phiAOD = AODJet2.Phi();

          mjjAOD = (AODJet1 + AODJet2).M();

	  t1_ptAOD = AODTau1.Pt();
	  t1_etaAOD = AODTau1.Eta();
	  t1_phiAOD = AODTau1.Phi();
	  t2_ptAOD = AODTau2.Pt();
	  t2_etaAOD = AODTau2.Eta();
	  t2_phiAOD = AODTau2.Phi();
          
          // Old VBF HLT Branches
          j1_ptOld = oldHLTJet1.Pt();
          j1_etaOld = oldHLTJet1.Eta();
          j1_phiOld = oldHLTJet1.Phi();
          j2_ptOld = oldHLTJet2.Pt();
          j2_etaOld = oldHLTJet2.Eta();
          j2_phiOld = oldHLTJet2.Phi();

          mjjOld = (oldHLTJet1 + oldHLTJet2).M();

          t1_ptOld = oldHLTTau1.Pt();
          t1_etaOld = oldHLTTau1.Eta();
          t1_phiOld = oldHLTTau1.Phi();
          t2_ptOld = oldHLTTau2.Pt();
          t2_etaOld = oldHLTTau2.Eta();
          t2_phiOld = oldHLTTau2.Phi();
	  
          // New VBF HLT Branches
          j1_ptNew = newHLTJet1.Pt();
          j1_etaNew = newHLTJet1.Eta();
          j1_phiNew = newHLTJet1.Phi();
          j2_ptNew = newHLTJet2.Pt();
          j2_etaNew = newHLTJet2.Eta();
          j2_phiNew = newHLTJet2.Phi();

          mjjNew = (newHLTJet1 + newHLTJet2).M();

          t1_ptNew = newHLTTau1.Pt();
          t1_etaNew = newHLTTau1.Eta();
          t1_phiNew = newHLTTau1.Phi();
          t2_ptNew = newHLTTau2.Pt();
          t2_etaNew = newHLTTau2.Eta();
          t2_phiNew = newHLTTau2.Phi();

	} // end if statement to fill kinematic variables

        outTree->Fill();

    } // end event loop


    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();

    outTree->Write();
    fOut->Close();
    return 0;
}
