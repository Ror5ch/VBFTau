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
#include "trigger_functions.h"

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
    // no branches for energy

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

    // path for Inclusive VBF HLT
    int passhltL1VBFDiJetOR;
    int passhltHpsDoublePFTau20Old;
    int passhltHpsDoublePFTau20TrackTightChargedIsoOld;
    int passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld;
    int passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    int passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    outTree->Branch("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    outTree->Branch("passhltHpsDoublePFTau20Old", &passhltHpsDoublePFTau20Old);
    outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoOld", &passhltHpsDoublePFTau20TrackTightChargedIsoOld);
    outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld", &passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld);
    outTree->Branch("passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    outTree->Branch("passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);

    // path for VBF Plus Two Tau HLT
    int passhltL1VBFDiJetIsoTau;
    int passhltHpsDoublePFTau20New;
    int passhltHpsDoublePFTau20TrackTightChargedIsoNew;
    int passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew;
    int passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    outTree->Branch("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);
    outTree->Branch("passhltHpsDoublePFTau20New", &passhltHpsDoublePFTau20New);
    outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoNew", &passhltHpsDoublePFTau20TrackTightChargedIsoNew);
    outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew", &passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew);
    outTree->Branch("passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched", &passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);

    // path for VBF Plus Two Deep Tau HLT
    int passhltL2VBFIsoTauNNFilter;
    int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
    int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;
    outTree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    outTree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    outTree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);

    // final HLT decisions (decision found separately in NtupleMaker than filter path above)
    int passInclusiveVBFHLT, passInclusiveVBFOff, passInclusiveVBFBoth;
    int passVBFPlusTwoTauHLT, passVBFPlusTwoTauOff, passVBFPlusTwoTauBoth;
    int passVBFPlusTwoDeepTauHLT, passVBFPlusTwoDeepTauBoth;
    outTree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);
    outTree->Branch("passInclusiveVBFOff", &passInclusiveVBFOff);
    outTree->Branch("passInclusiveVBFBoth", &passInclusiveVBFBoth);
    outTree->Branch("passVBFPlusTwoTauHLT", &passVBFPlusTwoTauHLT);
    outTree->Branch("passVBFPlusTwoTauOff", &passVBFPlusTwoTauOff);
    outTree->Branch("passVBFPlusTwoTauBoth", &passVBFPlusTwoTauBoth);
    outTree->Branch("passVBFPlusTwoDeepTauHLT", &passVBFPlusTwoDeepTauHLT);
    outTree->Branch("passVBFPlusTwoDeepTauBoth", &passVBFPlusTwoDeepTauBoth);

    int passDiTau32L1, passDiTau32L1DiTau35HLT, passDiTau32Off, passDiTau32Both;
    int passDiTau35L1, passDiTau35L1DiTau35HLT, passDiTau35Off, passDiTau35Both;
    outTree->Branch("passDiTau32L1DiTau35HLT", &passDiTau32L1DiTau35HLT);
    outTree->Branch("passDiTau32Off", &passDiTau32Off);
    outTree->Branch("passDiTau32Both", &passDiTau32Both);
    outTree->Branch("passDiTau35L1DiTau35HLT", &passDiTau35L1DiTau35HLT);
    outTree->Branch("passDiTau35Off", &passDiTau35Off);
    outTree->Branch("passDiTau35Both", &passDiTau35Both);
    int passDiTau32L1Count = 0;
    int passDiTau35L1Count = 0;

    int passDiTau32L1DeepDiTau35HLT;
    int passDiTau35L1DeepDiTau35HLT;
    outTree->Branch("passDiTau32L1DeepDiTau35HLT", &passDiTau32L1DeepDiTau35HLT);
    outTree->Branch("passDiTau35L1DeepDiTau35HLT", &passDiTau35L1DeepDiTau35HLT);

    int viableTaus, viableJets;
    outTree->Branch("viableTaus", &viableTaus);
    outTree->Branch("viableJets", &viableJets); 
    int matchedL1Jets;
    int matchedL1Tau;
    outTree->Branch("matchedL1Jets", &matchedL1Jets);
    outTree->Branch("matchedL1Tau", &matchedL1Tau);

    // variables without branches
    int passInclusiveVBFL1Count = 0;
    int passInclusiveVBFHLTCount = 0;
    int passVBFPlusTwoTauL1Count = 0;
    int passVBFPlusTwoTauHLTCount = 0;
    int passVBFPlusTwoDeepTauHLTCount = 0;

    float AODJet1Pt_ = 0;
    float AODJet2Pt_ = 0;
    float AODTau1Pt_ = 0;
    float AODTau2Pt_ = 0;
    float mj1j2_ = 0;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 10001; ++iEntry) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	if (iEntry % 100000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

        //-----------------daisy-chain module decisions from NtupleMaker-----------------------// 

        // fill Inclusive VBF HLT module flags
        passhltL1VBFDiJetOR = 0;
        passhltHpsDoublePFTau20Old = 0;
        passhltHpsDoublePFTau20TrackTightChargedIsoOld = 0;
        passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld = 0;
        passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;
        passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;

        passhltL1VBFDiJetOR = inTree->passhltL1VBFDiJetOR;
        if (passhltL1VBFDiJetOR) passhltHpsDoublePFTau20Old = inTree->passhltHpsDoublePFTau20;
        if (passhltHpsDoublePFTau20Old) passhltHpsDoublePFTau20TrackTightChargedIsoOld = inTree->passhltHpsDoublePFTau20TrackTightChargedIso;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoOld) passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld = inTree->passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld) passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = inTree->passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
        if (passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20) passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = inTree->passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;

        passInclusiveVBFHLT = inTree->passInclusiveVBFHLT;

        passInclusiveVBFL1Count += passhltL1VBFDiJetOR;
        passInclusiveVBFHLTCount += passInclusiveVBFHLT;


        // fill VBF Plus Two Tau HLT module flags 
        passhltL1VBFDiJetIsoTau = 0;
        passhltHpsDoublePFTau20New = 0;
        passhltHpsDoublePFTau20TrackTightChargedIsoNew = 0;
        passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew = 0;
        passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;

        passhltL1VBFDiJetIsoTau = inTree->passhltL1VBFDiJetIsoTau;
        if (passhltL1VBFDiJetIsoTau) passhltHpsDoublePFTau20New = inTree->passhltHpsDoublePFTau20;
        if (passhltHpsDoublePFTau20New) passhltHpsDoublePFTau20TrackTightChargedIsoNew = inTree->passhltHpsDoublePFTau20TrackTightChargedIso;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoNew) passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew = inTree->passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew) passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched = inTree->passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched;
        if (passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;

        passVBFPlusTwoTauHLT = inTree->passVBFPlusTwoTauHLT;

        passVBFPlusTwoTauL1Count += passhltL1VBFDiJetIsoTau;
        passVBFPlusTwoTauHLTCount += passVBFPlusTwoTauHLT;

        // fill VBF Plus Two Deep Tau HLT module flags
        passhltL2VBFIsoTauNNFilter = 0;
        passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
        passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 0;

        if (passhltL1VBFDiJetIsoTau) passhltL2VBFIsoTauNNFilter = inTree->passhltL2VBFIsoTauNNFilter;
        if (passhltL2VBFIsoTauNNFilter) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = inTree->passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
        if (passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = inTree->passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
        if (passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;

        passVBFPlusTwoDeepTauHLT = inTree->passVBFPlusTwoDeepTauHLT;

        passVBFPlusTwoDeepTauHLTCount += passVBFPlusTwoDeepTauHLT;

        // fill DiTau decisions. 32 L1 and "simulated" 35 L1 TODO: look at 34

        passDiTau32L1 = passDiTau35L1 = 0;
        passDiTau32L1 = inTree->passhltL1sDoubleTauBigOR;
        int sizeL1DiTau32 = 0;
        int sizeL1DiTau35 = 0;
        if (passDiTau32L1) sizeL1DiTau32 = inTree->hltL1sDoubleTauBigOR_pt->size();
        if (sizeL1DiTau32 >= 2) {
          for (int iL1Tau = 0; iL1Tau < sizeL1DiTau32; ++iL1Tau) {
            if (inTree->hltL1sDoubleTauBigOR_pt->at(iL1Tau) >= 35) sizeL1DiTau35 += 1;
          }
          if (sizeL1DiTau35 >= 2) passDiTau35L1 = 1;
        }

        passDiTau32L1DiTau35HLT = 0;
        passDiTau32L1Count += passDiTau32L1;
        passDiTau32L1DiTau35HLT = inTree->passDiTau35HLT;
        passDiTau35L1DiTau35HLT = 0;
        passDiTau35L1Count += passDiTau35L1;
        passDiTau35L1DiTau35HLT = (passDiTau35L1 && inTree->passDiTau35HLT);

        passDiTau32L1DeepDiTau35HLT = inTree->passDeepDiTau35HLT;
        passDiTau35L1DeepDiTau35HLT = (passDiTau35L1 && inTree->passDeepDiTau35HLT);


        // above is all that needs to run for rate
	//---------------------apply AOD selection and fill AOD objects------------------------------//

        viableTaus = 1;
        viableJets = 1;
        matchedL1Tau = 1;
        matchedL1Jets = 1;

	int sizeAODTau = inTree->tauPt->size(); // number of taus in event
	int sizeAODJet = inTree->jetPt->size(); // number of jets in event
	// check kinematics and ID of tau objects, store isolated taus w pt>=25 and eta<=2.1 taus
	std::vector<TLorentzVector> isoTauCands;	
	for (int iTau = 0; iTau < sizeAODTau; ++iTau) {
          bool passTauID = false;
          deepTauVSjet = inTree->tauByMediumDeepTau2017v2p1VSjet->at(iTau) > 0.5;
          deepTauVSmu = inTree->tauByVLooseDeepTau2017v2p1VSmu->at(iTau) > 0.5;
          deepTauVSele = inTree->tauByVVVLooseDeepTau2017v2p1VSe->at(iTau) > 0.5;
	
          if (deepTauVSjet && deepTauVSmu && deepTauVSele) passTauID = true;

          if (passTauID && fabs(inTree->tauEta->at(iTau) <= 2.1) ) { //&& inTree->tauPt->at(iTau) >= 25 ) {
            TLorentzVector tauCand;
            tauCand.SetPtEtaPhiE(inTree->tauPt->at(iTau),
                                 inTree->tauEta->at(iTau), 
                                 inTree->tauPhi->at(iTau), 
                                 inTree->tauEnergy->at(iTau));
            isoTauCands.push_back(tauCand);
          }
	}
        int isoTauCandsSize = isoTauCands.size();
        if (isoTauCandsSize < 2) viableTaus = 0; // need two taus minimum


	// use first two non-overlapped AOD taus
	// isoTauAODCands are already ordered by pT
	TLorentzVector AODTau1, AODTau2;
	if (viableTaus) {

	  AODTau1.SetPtEtaPhiE(isoTauCands.at(0).Pt(), 
                             isoTauCands.at(0).Eta(), 
                             isoTauCands.at(0).Phi(),
                             isoTauCands.at(0).Energy());

	  for (std::vector<TLorentzVector>::const_iterator iTau = isoTauCands.begin()+1; iTau != isoTauCands.end(); ++iTau) {
	    AODTau2.SetPtEtaPhiE(iTau->Pt(), iTau->Eta(), iTau->Phi(), iTau->Energy());
	    if (AODTau2.DeltaR(AODTau1) > 0.5) break; // if taus are not overlapped, leave the for-loop
	  }
          // check that the tau didn't make it all the way through the loop without breaking
          // I think this is unlikely but it's good to be redundant
	  if (AODTau1.DeltaR(AODTau2) < 0.5) viableTaus = 0;
        } // end viable if statement


        // check if it is possible to match to L1 Taus
        // save pairs or L1 and AOD Tau indices is dR <= 0.5
        std::vector<TLorentzVector> L1TauCands;
        int L1TauCandsSize;
        std::vector<std::pair<int,int>> matchedL1AODTaus;
        int L1TausSize = inTree->hltL1VBFDiJetIsoTau_tauPt->size();
        if (L1TausSize >= 1 && isoTauCandsSize >= 1) {
          L1TauCands = hltFillWithCands(inTree, "hltL1VBFDiJetIsoTau_taus", L1TausSize);
          L1TauCandsSize = L1TauCands.size();
          if (L1TauCandsSize >= 1) {
            for (int iL1Tau = 0; iL1Tau < L1TauCandsSize; ++iL1Tau) {
              for (int iAODTau = 0; iAODTau < isoTauCandsSize; ++iAODTau) {
                float dRtaus_ = isoTauCands.at(iAODTau).DeltaR(L1TauCands.at(iL1Tau));
                if (dRtaus_ <= 0.5) {
                  matchedL1AODTaus.push_back(std::make_pair(iL1Tau, iAODTau));
                }
              }
            }
          }
        }

        int matchedL1AODTausSize = matchedL1AODTaus.size();
        if (matchedL1AODTausSize < 1) matchedL1Tau = 0;

        if (matchedL1AODTausSize == 1) {
          // if only one L1AOD matched Tau, make it AODTau1 and pick first non-overlapped AODTau as AODTau2
          AODTau1 = isoTauCands.at(matchedL1AODTaus.at(0).second);
          for (int iAODTau = 0; iAODTau < isoTauCandsSize; ++iAODTau) {
            if (AODTau1.DeltaR(isoTauCands.at(iAODTau)) > 0.5) {
              AODTau2 = isoTauCands.at(iAODTau);
            }
          }
        }

        if (matchedL1AODTausSize >= 2) {
          // if two or more matched Taus, make container of all matched taus
          std::vector<TLorentzVector> matchedAODTaus;
          for (int iMatchedTau = 0; iMatchedTau < matchedL1AODTausSize; ++iMatchedTau) {
            matchedAODTaus.push_back(isoTauCands.at(matchedL1AODTaus.at(iMatchedTau).second));
          }
          int matchedAODTausSize = matchedAODTaus.size();
          // pick the two L1AOD matched taus with the highest sum of pt
          int AODTau1Index = -1;
          int AODTau2Index = -1;
          float highestPtSum = -1;
          float comparePtSum = -1;
          for (int iAODTau = 0; iAODTau < matchedAODTausSize; ++iAODTau) {
            for (int jAODTau = iAODTau+1; jAODTau < matchedAODTausSize; ++jAODTau) {
              if (matchedAODTaus.at(iAODTau).DeltaR(matchedAODTaus.at(jAODTau)) > 0.5) {
                comparePtSum = (matchedAODTaus.at(iAODTau).Pt() + matchedAODTaus.at(jAODTau).Pt());
                if (comparePtSum > highestPtSum) { highestPtSum = comparePtSum; AODTau1Index = iAODTau; AODTau2Index = jAODTau;}
              }  
            }
          }
          if (AODTau1Index != -1 && AODTau2Index != -1) {
            AODTau1 = matchedAODTaus.at(AODTau1Index); 
            AODTau2 = matchedAODTaus.at(AODTau2Index);
          }
        }
        if (AODTau1.DeltaR(AODTau2) < 0.5) viableTaus = 0;

        if (viableTaus) {
          AODTau1Pt_ = AODTau1.Pt();
          AODTau2Pt_ = AODTau2.Pt();
          // make the highest pT Tau the leading Tau
          if (AODTau2Pt_ > AODTau1Pt_) {
            TLorentzVector tempTau_;
            tempTau_ = AODTau1;
            AODTau1 = AODTau2;
            AODTau2 = tempTau_;
            AODTau1Pt_ = AODTau1.Pt();
            AODTau2Pt_ = AODTau2.Pt();
          }
        }       


	// check kinematics and ID of jet objects, store jets w pt>=30 and eta<=4.7
	std::vector<TLorentzVector> jetCands;
	for (int iJet = 0; iJet < sizeAODJet; ++iJet){

          bool passJetID = false;
          if (inTree->jetID->at(iJet) >= 6) passJetID = true; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

          if (passJetID && fabs(inTree->jetEta->at(iJet) <= 4.7)) { //&& inTree->jetPt->at(iJet) >= 30 
            TLorentzVector jetCand;
            jetCand.SetPtEtaPhiE(inTree->jetPt->at(iJet), 
                                 inTree->jetEta->at(iJet), 
                                 inTree->jetPhi->at(iJet), 
                                 inTree->jetEn->at(iJet));
	      // if a jetCandidate looks like it could be either tau we already selected, don't store it
	    bool jetCandIsTau = false;
            if (AODTau1.DeltaR(jetCand) < 0.5 || AODTau2.DeltaR(jetCand) < 0.5) jetCandIsTau = true;

            if (!jetCandIsTau) jetCands.push_back(jetCand);
          }
	}
	// check that we have at least two good jets
	int jetCandsSize = jetCands.size(); 
        if (jetCandsSize < 2) viableJets = 0;
	TLorentzVector AODJet1, AODJet2;
        if (viableJets) std::tie(AODJet1, AODJet2) = highestMassPair(jetCands);

        // match AOD jets to L1 then select them
        // first fill L1 cands
        // save L1 and AOD index pairs if dR <= 0.5
        std::vector<TLorentzVector> L1JetCands;
        std::vector<std::pair<int,int>> matchedL1AODJets; 
        int L1JetsSize = inTree->hltL1VBFDiJetIsoTau_jetPt->size();
        if (L1JetsSize >= 2 && jetCandsSize >= 2) {
          L1JetCands = hltFillWithCands(inTree, "hltL1VBFDiJetIsoTau_jets", L1JetsSize);
          int L1JetCandsSize = L1JetCands.size();
          if (L1JetCandsSize >= 2) {
            for (int iL1Jet = 0; iL1Jet < L1JetCandsSize; ++iL1Jet) {
              for (int iAODJet = 0; iAODJet < jetCandsSize; ++iAODJet) {
                float dRjets_ = jetCands.at(iAODJet).DeltaR(L1JetCands.at(iL1Jet));
                if (dRjets_ <= 0.5) {
                  matchedL1AODJets.push_back(std::make_pair(iL1Jet, iAODJet));
                }
              }
            }
          }
        }
        int matchedL1AODJetsSize = matchedL1AODJets.size();
        if (matchedL1AODJetsSize < 2 ) matchedL1Jets = 0;

        // if there's only 2 jets to match, just set them. They'll be ordered later
        if (matchedL1AODJetsSize == 2) {
          AODJet1 = jetCands.at(matchedL1AODJets.at(0).second);
          AODJet2 = jetCands.at(matchedL1AODJets.at(1).second);
        }

        if (matchedL1AODJetsSize >= 3) {
          // make list of AOD jets matched to L1 jets
          std::vector<TLorentzVector> matchedAODJets;
          for (int iMatchedJet = 0; iMatchedJet < matchedL1AODJetsSize; ++iMatchedJet) {
            matchedAODJets.push_back(jetCands.at(matchedL1AODJets.at(iMatchedJet).second));
          }
          // find highest mjj pair
          int AODJet1Index = -1;
          int AODJet2Index = -1;
          std::tie(AODJet1Index, AODJet2Index) = highestMassPairNew(matchedAODJets);
          if (AODJet1Index != -1 and AODJet2Index != -1) {
            AODJet1 = matchedAODJets.at(AODJet1Index);
            AODJet2 = matchedAODJets.at(AODJet2Index);
          }
        }
        if (AODJet1.DeltaR(AODJet2) < 0.5) viableJets = 0;

        if (viableJets) {
          AODJet1Pt_ = AODJet1.Pt();
          AODJet2Pt_ = AODJet2.Pt();
          // make higher pT jet leading jet
          if (AODJet2Pt_ > AODJet1Pt_) {
            TLorentzVector tempJet_;
            tempJet_ = AODJet1;
            AODJet1 = AODJet2;
            AODJet2 = tempJet_;
            AODJet1Pt_ = AODJet1.Pt();
            AODJet2Pt_ = AODJet2.Pt();
          }
          mj1j2_ = (AODJet1 + AODJet2).M();
        }

	// Check AOD Objects Pass Offline Selection
        passDiTau32Off = passDiTau35Off = passInclusiveVBFOff = passVBFPlusTwoTauOff = 0;
        if (viableTaus && viableJets) {

          if (AODTau1Pt_ >= 50 && AODTau2Pt_ >= 25 && AODJet1Pt_ >= 45 && AODJet2Pt_ >= 45 && mj1j2_ < 200) {
            std::cout << mj1j2_ << '\t' << AODJet1Pt_ << '\t' << AODJet2Pt_ << '\t' << AODTau1Pt_ << '\t' << AODTau2Pt_ << std::endl;
          }

          //int dEtajj = abs(AODJet1.Eta() - AODJet2.Eta());
          int offJetInc = 10; // define offline as XX increase of L1 cuts
	  int offTau1Inc = 5;
          int offTau2Inc = 5;
          int offM2Inc = 50;
 

          if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && mj1j2_ >= 600) {
            if (AODTau1Pt_ >= (32+offTau1Inc) && AODTau2Pt_ >= (32+offTau2Inc) ) passDiTau32Off = 1;
            if (AODTau1Pt_ >= (35+offTau1Inc) && AODTau2Pt_ >= (35+offTau2Inc) ) passDiTau35Off = 1;
          }

          // L1 DoubleJet_110_35_DoubleJet35_Mass_Min620
	  if (AODJet1Pt_ >= (110+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= 25 && AODTau2Pt_ >= 25 && mj1j2_ >= 700) passInclusiveVBFOff = 1;
        
          // L1 DoubleJet35_Mass_Min_450_IsoTau45er2p1_RmvOl
          if (AODJet1Pt_ >= (35+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= (45+offTau1Inc) && AODTau2Pt_ >= (20+offTau2Inc) && mj1j2_ >= 600) passVBFPlusTwoTauOff = 1;

        } // end viable if statement

        passDiTau32Both = passDiTau35Both = 0;
        passDiTau32Both = (passDiTau32L1DiTau35HLT && passDiTau32Off); // this is the "normal" 35 HLT
        passDiTau35Both = (passDiTau35L1DiTau35HLT && passDiTau35Off); // this is essentially proposed by CIEMAT

        //---------------------------match AOD and HLT------------------------------//
        // matching for HLT objects from Inclusive VBF path
        TLorentzVector oldHLTJet1, oldHLTJet2, oldHLTTau1, oldHLTTau2;
        matchedJetsOld = matchedTausOld = matchedBothOld = 0;
        if (passInclusiveVBFHLT && passInclusiveVBFOff) { 
          int jet40NumOld = inTree->hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt->size(); // number of jets w pt>=40 from HLT filter
          int jet115NumOld = inTree->hltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt->size(); // number of jets w pt>=115 from HLT filter
          int tau20NumOld = inTree->hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt->size(); // number of taus w pt>=20 from HLT filter
          
          if (jet40NumOld >= 2 && jet115NumOld >= 1 && tau20NumOld >= 2) {
            std::vector<TLorentzVector> oldHLTJetCands, oldHLTTauCands;
            oldHLTJetCands = hltFillWithCands(inTree, "hltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", jet40NumOld);
            oldHLTTauCands = hltFillWithCands(inTree, "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon", tau20NumOld);
            // when filling, an eta cut is imposed which can reduce the size of the container

            dRj1Old, dRj2Old, dRt1Old, dRt2Old = 999;
            int overlappedOld = 0;
            if (oldHLTJetCands.size() >= 2 && oldHLTTauCands.size() >= 2) {
              std::tie(oldHLTJet1, oldHLTJet2) = matchTwoObjs(oldHLTJetCands, AODJet1, AODJet2);
              dRj1Old = oldHLTJet1.DeltaR(AODJet1);
              dRj2Old = oldHLTJet2.DeltaR(AODJet2);

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
        if (passVBFPlusTwoTauHLT && passVBFPlusTwoTauOff) {
          int jet40NumNew = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20_pt->size(); // number of jets w pt>=40 from HLT filter
          int tau20NumNew = inTree->hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon_pt->size(); // number of taus w pt>=20 from HLT filter
          int tau45NumNew = inTree->hltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched_pt->size(); // number of taus w pt>=45 from HLT filter
          
          if (jet40NumNew >= 2 && tau20NumNew >= 2 && tau45NumNew >= 1) {
            std::vector<TLorentzVector> newHLTJetCands, newHLTTauCands;
            newHLTJetCands = hltFillWithCands(inTree, "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", jet40NumNew);
            newHLTTauCands = hltFillWithCands(inTree, "hltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon", tau20NumNew);
            // when filling, an eta cut is imposed which can reduce the size of the container

            dRj1New, dRj2New, dRt1New, dRt2New = 999;
            int overlappedNew = 0;
            if (newHLTJetCands.size() >= 2 && newHLTTauCands.size() >= 2) {
              std::tie(newHLTJet1, newHLTJet2) = matchTwoObjs(newHLTJetCands, AODJet1, AODJet2);
              dRj1New = newHLTJet1.DeltaR(AODJet1);
              dRj2New = newHLTJet2.DeltaR(AODJet2);

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
        // fill branches for Old or New HLT objects if they are matched to AOD

        j1_ptAOD = j1_etaAOD = j1_phiAOD = -999;
        j2_ptAOD = j2_etaAOD = j2_phiAOD = mjjAOD = -999;
        t1_ptAOD = t1_etaAOD = t1_phiAOD = -999;
        t2_ptAOD = t2_etaAOD = t2_phiAOD = -999;

        passInclusiveVBFBoth = passVBFPlusTwoTauBoth = 0;
        passInclusiveVBFBoth = (passInclusiveVBFHLT && passInclusiveVBFOff);
        passVBFPlusTwoTauBoth = (passVBFPlusTwoTauHLT && passVBFPlusTwoTauOff);

        if (viableTaus && viableJets) {
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