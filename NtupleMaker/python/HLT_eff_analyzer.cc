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
    // HLT variables and branches
    float j1_pt, j1_eta, j1_phi, j1_energy; 
    float j2_pt, j2_eta, j2_phi, j2_energy; 
    float mjj;
    float t1_pt, t1_eta, t1_phi, t1_energy;
    float t2_pt, t2_eta, t2_phi, t2_energy;
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
    // AOD variables and branches, A is for AOD
    float j1_pt_A, j1_eta_A, j1_phi_A, j1_energy_A; 
    float j2_pt_A, j2_eta_A, j2_phi_A, j2_energy_A; 
    float mjj_A;
    float t1_pt_A, t1_eta_A, t1_phi_A, t1_energy_A;
    float t2_pt_A, t2_eta_A, t2_phi_A, t2_energy_A;
    int deepTauVSjet, deepTauVSmu, deepTauVSele, jetID;
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
    // variables and branches for matching
    float dRj1, dRj2, dRt1, dRt2;
    int matchedTaus, matchedJets, matchedBoth;
    outTree->Branch("dRj1", &dRj1);
    outTree->Branch("dRj2", &dRj2);
    outTree->Branch("dRt1", &dRt1);
    outTree->Branch("dRt2", &dRt2);
    outTree->Branch("matchedTaus", &matchedTaus);
    outTree->Branch("matchedJets", &matchedJets);
    outTree->Branch("matchedBoth", &matchedBoth);
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
    int passOldVBFHLT;
    int passNewVBFHLT;
    outTree->Branch("passOldVBFHLT", &passOldVBFHLT);
    outTree->Branch("passNewVBFHLT", &passNewVBFHLT);

    // variables without branches
    int passDiTau32_Off, passDiTau35_Off, passOld_Off, passNew_Off;
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

        // fix HLT filter decisions // 

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


	//---------------------apply base selection and fill AOD objects------------------------------//

	int sizeAODTau = inTree->tauPt->size(); // number of taus in event
	int sizeAODJet = inTree->jetPt->size(); // number of jets in event
	// check kinematics and ID of tau objects, store good taus
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


	// check kinematics and ID of jet objects, store good jets
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
        if (jet30CandsSize < 2) continue;

	// fill AOD jets with pair of jets that produced the largest mjj value
	// from cout statements, AODJet1 was verified to be leading jet
	TLorentzVector AODJet1, AODJet2;
        std::tie(AODJet1, AODJet2) = highestMassPair(jet30Cands);

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
	double mj1j2 = (AODJet1 + AODJet2).M();

        double AODJet1Pt_ = AODJet1.Pt();	
        double AODJet2Pt_ = AODJet2.Pt();	
        double AODTau1Pt_ = AODTau1.Pt();
        double AODTau2Pt_ = AODTau2.Pt();

        //int dEtajj = abs(AODJet1.Eta() - AODJet2.Eta());
        int offJetInc = 10;
	int offTau1Inc = 18;
        int offTau2Inc = 8;
        int offM2Inc = 50;

        passDiTau32_Off = passDiTau35_Off = passOld_Off = passNew_Off = 0;

        if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && mj1j2 >= 600) {
          if (AODTau1Pt_ >= (32+offTau1Inc) && AODTau2Pt_ >= (32+offTau2Inc) ) passDiTau32_Off = 1;
          if (AODTau1Pt_ >= (35+offTau1Inc) && AODTau2Pt_ >= (35+offTau2Inc) ) passDiTau35_Off = 1;
        }

        // L1 DoubleJet_110_35_DoubleJet35_Mass_Min620
	if (AODJet1Pt_ >= (110+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
            AODTau1Pt_ >= 25 && AODTau2Pt_ >= 25 && mj1j2 >= 700) passOld_Off = 1;
        
        // L1 DoubleJet35_Mass_Min_450_IsoTau45_RmvOl
        if (AODJet1Pt_ >= (35+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
            AODTau1Pt_ >= (45+offTau1Inc) && AODTau2Pt_ >= 25 && mj1j2 >= 500) passNew_Off = 1;

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

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();

    outTree->Write();
    fOut->Close();
    return 0;
}
