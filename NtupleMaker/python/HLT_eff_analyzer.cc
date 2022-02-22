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
/*
    outTree->Branch("dRj1Old", &dRj1Old);
    outTree->Branch("dRj2Old", &dRj2Old);
    outTree->Branch("dRt1Old", &dRt1Old);
    outTree->Branch("dRt2Old", &dRt2Old);
    outTree->Branch("matchedJetsOld", &matchedJetsOld);
    outTree->Branch("matchedTausOld", &matchedTausOld);
    outTree->Branch("matchedBothOld", &matchedBothOld);
*/

    // variables and branches for matching
    float dRj1New, dRj2New, dRt1New, dRt2New;
    int matchedTausNew, matchedJetsNew, matchedBothNew;
/*
    outTree->Branch("dRj1New", &dRj1New);
    outTree->Branch("dRj2New", &dRj2New);
    outTree->Branch("dRt1New", &dRt1New);
    outTree->Branch("dRt2New", &dRt2New);
    outTree->Branch("matchedJetsNew", &matchedJetsNew);
    outTree->Branch("matchedTausNew", &matchedTausNew);
    outTree->Branch("matchedBothNew", &matchedBothNew);
*/

    // path for Inclusive VBF HLT
    int passhltL1VBFDiJetOR;
    int passhltHpsDoublePFTau20Old;
    int passhltHpsDoublePFTau20TrackTightChargedIsoOld;
    int passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld;
    int passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    int passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    //outTree->Branch("passhltL1VBFDiJetOR", &passhltL1VBFDiJetOR);
    //outTree->Branch("passhltHpsDoublePFTau20Old", &passhltHpsDoublePFTau20Old);
    //outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoOld", &passhltHpsDoublePFTau20TrackTightChargedIsoOld);
    //outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld", &passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld);
    //outTree->Branch("passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);
    //outTree->Branch("passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);

    // path for VBF Plus Two Tau HLT
    int passhltL1VBFDiJetIsoTau;
    int passhltHpsDoublePFTau20New;
    int passhltHpsDoublePFTau20TrackTightChargedIsoNew;
    int passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew;
    int passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
    outTree->Branch("passhltL1VBFDiJetIsoTau", &passhltL1VBFDiJetIsoTau);

    //outTree->Branch("passhltHpsDoublePFTau20New", &passhltHpsDoublePFTau20New);
    //outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoNew", &passhltHpsDoublePFTau20TrackTightChargedIsoNew);
    //outTree->Branch("passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew", &passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew);
    //outTree->Branch("passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched", &passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched);
    //outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20);

    // path for VBF Plus Two Deep Tau HLT
    int passhltL2VBFIsoTauNNFilter;
    int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
    int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
    int passhltRealDijetFilter;
    int passhltVBFLooseIDPFDummyFilter;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;
    outTree->Branch("passhltL2VBFIsoTauNNFilter", &passhltL2VBFIsoTauNNFilter);
    outTree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch);
    outTree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched);
    outTree->Branch("passhltRealDijetFilter", &passhltRealDijetFilter);
    outTree->Branch("passhltVBFLooseIDPFDummyFilter", &passhltVBFLooseIDPFDummyFilter);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20);

    //
    int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLoose;
    int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLoose;
    int passhltRealDijetFilter_VBF2DTTempLoose;
    int passhltVBFLooseIDPFDummyFilter_VBF2DTTempLoose;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLoose;
    outTree->Branch("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLoose", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLoose);
    outTree->Branch("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLoose", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLoose);
    outTree->Branch("passhltRealDijetFilter_VBF2DTTempLoose", &passhltRealDijetFilter_VBF2DTTempLoose);
    outTree->Branch("passhltVBFLooseIDPFDummyFilter_VBF2DTTempLoose", &passhltVBFLooseIDPFDummyFilter_VBF2DTTempLoose);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLoose", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLoose);

    //
    int passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_VBF2DTNoL2NN;
    int passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_VBF2DTNoL2NN;
    int passhltRealDijetFilter_VBF2DTNoL2NN;
    int passhltVBFLooseIDPFDummyFilter_VBF2DTNoL2NN;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_VBF2DTNoL2NN;
    outTree->Branch("passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_VBF2DTNoL2NN", &passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_VBF2DTNoL2NN);
    outTree->Branch("passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_VBF2DTNoL2NN", &passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_VBF2DTNoL2NN);
    outTree->Branch("passhltRealDijetFilter_VBF2DTNoL2NN", &passhltRealDijetFilter_VBF2DTNoL2NN);
    outTree->Branch("passhltVBFLooseIDPFDummyFilter_VBF2DTNoL2NN", &passhltVBFLooseIDPFDummyFilter_VBF2DTNoL2NN);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_VBF2DTNoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_VBF2DTNoL2NN);

    //
    int passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLooseNoL2NN;
    int passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLooseNoL2NN;
    int passhltRealDijetFilter_VBF2DTTempLooseNoL2NN;
    int passhltVBFLooseIDPFDummyFilter_VBF2DTTempLooseNoL2NN;
    int passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLooseNoL2NN;
    outTree->Branch("passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLooseNoL2NN", &passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLooseNoL2NN);
    outTree->Branch("passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLooseNoL2NN", &passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLooseNoL2NN);
    outTree->Branch("passhltRealDijetFilter_VBF2DTTempLooseNoL2NN", &passhltRealDijetFilter_VBF2DTTempLooseNoL2NN);
    outTree->Branch("passhltVBFLooseIDPFDummyFilter_VBF2DTTempLooseNoL2NN", &passhltVBFLooseIDPFDummyFilter_VBF2DTTempLooseNoL2NN);
    outTree->Branch("passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLooseNoL2NN", &passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLooseNoL2NN);


    // final HLT decisions (decision found separately in NtupleMaker than filter path above)
    int passInclusiveVBFHLT, passInclusiveVBFOff, passInclusiveVBFBoth;
    int passVBFPlusTwoTauHLT, passVBFPlusTwoTauOff, passVBFPlusTwoTauBoth;

    int passVBFPlusTwoDeepTauHLT, passVBFPlusTwoDeepTauBoth;
    int passVBF2DTTempLooseHLT, passVBF2DTTempLooseBoth;
    int passVBF2DTNoL2NNHLT, passVBF2DTNoL2NNBoth;
    int passVBF2DTTempLooseNoL2NNHLT, passVBF2DTTempLooseNoL2NNBoth;

    outTree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);
    outTree->Branch("passInclusiveVBFOff", &passInclusiveVBFOff);
    outTree->Branch("passInclusiveVBFBoth", &passInclusiveVBFBoth);

    outTree->Branch("passVBFPlusTwoTauHLT", &passVBFPlusTwoTauHLT);
    outTree->Branch("passVBFPlusTwoTauOff", &passVBFPlusTwoTauOff);
    outTree->Branch("passVBFPlusTwoTauBoth", &passVBFPlusTwoTauBoth);

    outTree->Branch("passVBFPlusTwoDeepTauHLT", &passVBFPlusTwoDeepTauHLT);
    outTree->Branch("passVBFPlusTwoDeepTauBoth", &passVBFPlusTwoDeepTauBoth);

    outTree->Branch("passVBF2DTTempLooseHLT", &passVBF2DTTempLooseHLT);
    outTree->Branch("passVBF2DTTempLooseBoth", &passVBF2DTTempLooseBoth);

    outTree->Branch("passVBF2DTNoL2NNHLT", &passVBF2DTNoL2NNHLT);
    outTree->Branch("passVBF2DTNoL2NNBoth", &passVBF2DTNoL2NNBoth);

    outTree->Branch("passVBF2DTTempLooseNoL2NNHLT", &passVBF2DTTempLooseNoL2NNHLT);
    outTree->Branch("passVBF2DTTempLooseNoL2NNBoth", &passVBF2DTTempLooseNoL2NNBoth);

    //

    int passDiTau32L1, passDiTau32L1DiTau35HLT, passDiTau32Off, passDiTau32Both;
    int passDiTau34L1, passDiTau34L1DiTau35HLT, passDiTau34Off, passDiTau34Both;
    int passDiTau35L1, passDiTau35L1DiTau35HLT, passDiTau35Off, passDiTau35Both;
    outTree->Branch("passDiTau32L1DiTau35HLT", &passDiTau32L1DiTau35HLT);
    outTree->Branch("passDiTau32Off", &passDiTau32Off);
    outTree->Branch("passDiTau32Both", &passDiTau32Both);
    outTree->Branch("passDiTau34L1DiTau35HLT", &passDiTau34L1DiTau35HLT);
    outTree->Branch("passDiTau34Off", &passDiTau34Off);
    outTree->Branch("passDiTau34Both", &passDiTau34Both);
    outTree->Branch("passDiTau35L1DiTau35HLT", &passDiTau35L1DiTau35HLT);
    outTree->Branch("passDiTau35Off", &passDiTau35Off);
    outTree->Branch("passDiTau35Both", &passDiTau35Both);

    int passDiTau32L1DeepDiTau35HLT;
    int passDiTau34L1DeepDiTau35HLT;
    int passDiTau35L1DeepDiTau35HLT;
    outTree->Branch("passDiTau32L1DeepDiTau35HLT", &passDiTau32L1DeepDiTau35HLT);
    outTree->Branch("passDiTau34L1DeepDiTau35HLT", &passDiTau34L1DeepDiTau35HLT);
    outTree->Branch("passDiTau35L1DeepDiTau35HLT", &passDiTau35L1DeepDiTau35HLT);

    int passDeepDiTau34Both;
    int passDeepDiTau35Both;
    outTree->Branch("passDeepDiTau34Both", &passDeepDiTau34Both);
    outTree->Branch("passDeepDiTau35Both", &passDeepDiTau35Both);

    int viableTaus, viableJets;
    outTree->Branch("viableTaus", &viableTaus);
    outTree->Branch("viableJets", &viableJets); 

    int matchedL1Jets;
    int matchedL1Tau;
    outTree->Branch("matchedL1Jets", &matchedL1Jets);
    outTree->Branch("matchedL1Tau", &matchedL1Tau);

    int matchedHLTJets;
    int matchedHLTTaus;
    outTree->Branch("matchedHLTJets", &matchedHLTJets);
    outTree->Branch("matchedHLTTaus", &matchedHLTTaus);

    int matchedHLTJets_TempLoose;
    int matchedHLTTaus_TempLoose;
    outTree->Branch("matchedHLTJets_TempLoose", &matchedHLTJets_TempLoose);
    outTree->Branch("matchedHLTTaus_TempLoose", &matchedHLTTaus_TempLoose);

    // variables without branches

    float AODJet1Pt_ = 0;
    float AODJet2Pt_ = 0;
    float AODTau1Pt_ = 0;
    float AODTau2Pt_ = 0;
    float mj1j2_ = 0;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 100001; ++iEntry) {
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


        // fill VBF Plus Two Deep Tau HLT module flags
        passhltL2VBFIsoTauNNFilter = 0;
        passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = 0;
        passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = 0;
        passhltRealDijetFilter = 0;
        passhltVBFLooseIDPFDummyFilter = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = 0;

        if (passhltL1VBFDiJetIsoTau) passhltL2VBFIsoTauNNFilter = inTree->passhltL2VBFIsoTauNNFilter;
        if (passhltL2VBFIsoTauNNFilter) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch = inTree->passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch;
        if (passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched = inTree->passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched;
        if (passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched) passhltRealDijetFilter = inTree->passhltRealDijetFilter;
        if (passhltRealDijetFilter) passhltVBFLooseIDPFDummyFilter = inTree->passhltVBFLooseIDPFDummyFilter;
        if (passhltVBFLooseIDPFDummyFilter) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20 = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20;

        passVBFPlusTwoDeepTauHLT = inTree->passVBFPlusTwoDeepTauHLT;

        // fill VBF Plus Two Deep Tau Temp Loose HLT module flags (go back and make these module flags...)
        //passhltL2VBFIsoTauNNFilter_VBF2DTTempLoose = 0;
        passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLoose = 0;
        passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLoose = 0;
        passhltRealDijetFilter_VBF2DTTempLoose = 0;
        passhltVBFLooseIDPFDummyFilter_VBF2DTTempLoose = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLoose = 0;

        //if (passhltL1VBFDiJetIsoTau) passhltL2VBFIsoTauNNFilter_VBF2DTTempLoose = inTree->passhltL2VBFIsoTauNNFilter;
        //passhltL2VBFIsoTauNNFilter_VBF2DTTempLoose
        if (passhltL2VBFIsoTauNNFilter) passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLoose = inTree->passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch;
        if (passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLoose) passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLoose = inTree->passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched;
        if (passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLoose) passhltRealDijetFilter_VBF2DTTempLoose = inTree->passhltRealDijetFilter;
        if (passhltRealDijetFilter_VBF2DTTempLoose) passhltVBFLooseIDPFDummyFilter_VBF2DTTempLoose = inTree->passhltVBFLooseIDPFDummyFilter;
        if (passhltVBFLooseIDPFDummyFilter_VBF2DTTempLoose) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLoose = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20;

        passVBF2DTTempLooseHLT = inTree->passVBF2DTTempLooseHLT;

        // fill VBF Plus Two Deep Tau NoL2NN HLT module flags (go back and make these module flags...)
        passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_VBF2DTNoL2NN = 0;
        passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_VBF2DTNoL2NN = 0;
        passhltRealDijetFilter_VBF2DTNoL2NN = 0;
        passhltVBFLooseIDPFDummyFilter_VBF2DTNoL2NN = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_VBF2DTNoL2NN = 0;

        if (passhltL1VBFDiJetIsoTau) passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_VBF2DTNoL2NN = inTree->passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatchNoL2NN;
        if (passhltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_VBF2DTNoL2NN) passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_VBF2DTNoL2NN = inTree->passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatchedNoL2NN;
        if (passhltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_VBF2DTNoL2NN) passhltRealDijetFilter_VBF2DTNoL2NN = inTree->passhltRealDijetFilter;
        if (passhltRealDijetFilter_VBF2DTNoL2NN) passhltVBFLooseIDPFDummyFilter_VBF2DTNoL2NN = inTree->passhltVBFLooseIDPFDummyFilter;
        if (passhltVBFLooseIDPFDummyFilter_VBF2DTNoL2NN) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_VBF2DTNoL2NN = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20NoL2NN;

        passVBF2DTNoL2NNHLT = inTree->passVBF2DTNoL2NNHLT;

        // fill VBF Plus Two Deep Tau Temp Loose NoL2NN HLT module flags (go back and make these module flags...)
        passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLooseNoL2NN = 0;
        passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLooseNoL2NN = 0;
        passhltRealDijetFilter_VBF2DTTempLooseNoL2NN = 0;
        passhltVBFLooseIDPFDummyFilter_VBF2DTTempLooseNoL2NN = 0;
        passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLooseNoL2NN = 0;

        if (passhltL1VBFDiJetIsoTau) passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLooseNoL2NN = inTree->passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatchNoL2NN;
        if (passhltHpsDoublePFTau20TempLooseDitauWPDeepTauNoMatch_VBF2DTTempLooseNoL2NN) passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLooseNoL2NN = inTree->passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatchedNoL2NN;
        if (passhltHpsSinglePFTau45TempLooseDitauWPDeepTauL1HLTMatched_VBF2DTTempLooseNoL2NN) passhltRealDijetFilter_VBF2DTTempLooseNoL2NN = inTree->passhltRealDijetFilter;
        if (passhltRealDijetFilter_VBF2DTTempLooseNoL2NN) passhltVBFLooseIDPFDummyFilter_VBF2DTTempLooseNoL2NN = inTree->passhltVBFLooseIDPFDummyFilter;
        if (passhltVBFLooseIDPFDummyFilter_VBF2DTTempLooseNoL2NN) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20_VBF2DTTempLooseNoL2NN = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsTempLooseDeepTauIsoPFTauHPS20NoL2NN;

        passVBF2DTTempLooseNoL2NNHLT = inTree->passVBF2DTTempLooseNoL2NNHLT;


        passDiTau32L1 = passDiTau34L1 = passDiTau35L1 = 0;
        passDiTau32L1 = inTree->passhltL1sDoubleTauBigOR;
        int sizeL1DiTau32 = 0;
        int sizeL1DiTau34 = 0;
        int sizeL1DiTau35 = 0;
        if (passDiTau32L1) sizeL1DiTau32 = inTree->hltL1sDoubleTauBigOR_pt->size();
        if (sizeL1DiTau32 >= 2) {
          for (int iL1Tau = 0; iL1Tau < sizeL1DiTau32; ++iL1Tau) {
            if (inTree->hltL1sDoubleTauBigOR_pt->at(iL1Tau) >= 34) sizeL1DiTau34 += 1;
            if (inTree->hltL1sDoubleTauBigOR_pt->at(iL1Tau) >= 35) sizeL1DiTau35 += 1;
          }
          if (sizeL1DiTau34 >= 2) passDiTau34L1 = 1;
          if (sizeL1DiTau35 >= 2) passDiTau35L1 = 1;
        }

        passDiTau32L1DiTau35HLT = 0;
        passDiTau32L1DiTau35HLT = inTree->passDiTau35HLT; // L1 32 is lowest in the L1 Tau seeds, so if HLT is passed then 32 Tau L1 must pass too
        passDiTau34L1DiTau35HLT = 0;
        passDiTau34L1DiTau35HLT = (passDiTau34L1 && inTree->passDiTau35HLT);
        passDiTau35L1DiTau35HLT = 0;
        passDiTau35L1DiTau35HLT = (passDiTau35L1 && inTree->passDiTau35HLT);

        passDiTau32L1DeepDiTau35HLT = 0;
        passDiTau32L1DeepDiTau35HLT = inTree->passDeepDiTau35HLT;
        passDiTau34L1DeepDiTau35HLT = 0;
        passDiTau34L1DeepDiTau35HLT = (passDiTau34L1 && inTree->passDeepDiTau35HLT);
        passDiTau35L1DeepDiTau35HLT = 0;
        passDiTau35L1DeepDiTau35HLT = (passDiTau35L1 && inTree->passDeepDiTau35HLT);



        // above is all that needs to run for rate
	//---------------------apply AOD selection and fill AOD objects------------------------------//

        viableTaus = 1;
        viableJets = 1;
        matchedL1Tau = 1;
        matchedL1Jets = 1;
        matchedHLTTaus = 1;
        matchedHLTJets = 1;

	int sizeAODTau = inTree->tauPt->size(); // number of taus in event
	int sizeAODJet = inTree->jetPt->size(); // number of jets in event
	// check kinematics and ID of tau objects, store isolated taus w pt>=25 and eta<=2.1 taus
	//if (sizeAODTau >= 2 && passVBFPlusTwoDeepTauHLT) twoTausCount += 1;
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
        //if (isoTauCandsSize >= 2 && passVBFPlusTwoDeepTauHLT) twoGoodTausCount += 1;

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
        // if (viableTaus && isoTauCandsSize >= 2 && passVBFPlusTwoDeepTauHLT) twoGoodViableTausCount += 1;


        // difference between 20 and 45 filters is 20 doesn't have L1HLT matching, 45 does

        std::vector<TLorentzVector> HLTTauCandsFrom20Filter;
        std::vector<std::pair<int,int>> matchedHLTAODTausFrom20Filter;
        int HLTTausFrom20FilterSize = inTree->hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch_pt->size();
        if (HLTTausFrom20FilterSize >= 2 && isoTauCandsSize >= 2) {
          HLTTauCandsFrom20Filter = hltFillWithCands(inTree, "hltHpsDoublePFTau20MediumDitauWPDeepTauNoMatch", HLTTausFrom20FilterSize);
          int HLTTauCandsFrom20FilterSize = HLTTauCandsFrom20Filter.size();
          if (HLTTauCandsFrom20FilterSize >= 2) {
            for (int iHLTTauFrom20Filter = 0; iHLTTauFrom20Filter < HLTTauCandsFrom20FilterSize; ++iHLTTauFrom20Filter) {
              for (int iAODTau = 0; iAODTau < isoTauCandsSize; ++iAODTau) {
                float dRtaus_ = isoTauCands.at(iAODTau).DeltaR(HLTTauCandsFrom20Filter.at(iHLTTauFrom20Filter));
                if (dRtaus_ <= 0.5) {
                  matchedHLTAODTausFrom20Filter.push_back(std::make_pair(iHLTTauFrom20Filter, iAODTau));
                }
              }
            }
          }
        }
        int matchedHLTAODTausFrom20FilterSize = matchedHLTAODTausFrom20Filter.size();
        if (matchedHLTAODTausFrom20FilterSize < 1) matchedHLTTaus = 0; 

        std::vector<TLorentzVector> HLTTauCandsFrom45Filter;
        std::vector<std::pair<int,int>> matchedHLTAODTausFrom45Filter;
        int HLTTausFrom45FilterSize = inTree->hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched_pt->size();
        if (HLTTausFrom45FilterSize >= 1 && isoTauCandsSize >= 2) {
          HLTTauCandsFrom45Filter = hltFillWithCands(inTree, "hltHpsSinglePFTau45MediumDitauWPDeepTauL1HLTMatched", HLTTausFrom45FilterSize);
          int HLTTauCandsFrom45FilterSize = HLTTauCandsFrom45Filter.size();
          if (HLTTauCandsFrom45FilterSize >= 1) {
            for (int iHLTTauFrom45Filter = 0; iHLTTauFrom45Filter < HLTTauCandsFrom45FilterSize; ++iHLTTauFrom45Filter) {
              for (int iAODTau = 0; iAODTau < isoTauCandsSize; ++iAODTau) {
                float dRtaus_ = isoTauCands.at(iAODTau).DeltaR(HLTTauCandsFrom45Filter.at(iHLTTauFrom45Filter));
                if (dRtaus_ <= 0.5) {
                  matchedHLTAODTausFrom45Filter.push_back(std::make_pair(iHLTTauFrom45Filter, iAODTau));
                }
              }
            }
          }
        }
        int matchedHLTAODTausFrom45FilterSize = matchedHLTAODTausFrom45Filter.size();
        if (matchedHLTAODTausFrom45FilterSize < 1) matchedHLTTaus = 0;

        // about 30 events total have 3 or 4 matched taus
        // what's odd is there are many more 4 tau events than 3 tau events?

        if (matchedHLTAODTausFrom45FilterSize == 1) {
          AODTau1 = isoTauCands.at(matchedHLTAODTausFrom45Filter.at(0).second);
          std::vector<TLorentzVector> matchedAODTausFrom20Filter;
          for (int iMatchedTau = 0; iMatchedTau < matchedHLTAODTausFrom20FilterSize; ++iMatchedTau) {
            matchedAODTausFrom20Filter.push_back(isoTauCands.at(matchedHLTAODTausFrom20Filter.at(iMatchedTau).second));
          }
          int matchedAODTausFrom20FilterSize = matchedAODTausFrom20Filter.size();
          int AODTau2Index = -1;
          float highestPtSum = -1;
          float comparePtSum = -1;
          for (int iAODTauFrom20Filter = 0; iAODTauFrom20Filter < matchedAODTausFrom20FilterSize; ++iAODTauFrom20Filter) {
            if (AODTau1.DeltaR(matchedAODTausFrom20Filter.at(iAODTauFrom20Filter)) > 0.5) {
              comparePtSum = (AODTau1.Pt() + matchedAODTausFrom20Filter.at(iAODTauFrom20Filter).Pt());
              if (comparePtSum > highestPtSum) { highestPtSum = comparePtSum; AODTau2Index = iAODTauFrom20Filter;}
            }
          }
          if (AODTau2Index != -1) AODTau2 = matchedAODTausFrom20Filter.at(AODTau2Index);
          if (AODTau2Index == -1) matchedHLTTaus = 0; 
        }

        if (matchedHLTAODTausFrom45FilterSize >= 2) {
          std::vector<TLorentzVector> matchedAODTausFrom45Filter;
          for (int iMatchedTau = 0; iMatchedTau < matchedHLTAODTausFrom45FilterSize; ++iMatchedTau) {
            matchedAODTausFrom45Filter.push_back(isoTauCands.at(matchedHLTAODTausFrom45Filter.at(iMatchedTau).second));
          }
          int matchedAODTausFrom45FilterSize = matchedAODTausFrom45Filter.size();
          int AODTau1Index = -1;
          int AODTau2Index = -1;
          float highestPtSum = -1;
          float comparePtSum = -1;
          for (int iAODTau = 0; iAODTau < matchedAODTausFrom45FilterSize; ++iAODTau) {
            for (int jAODTau = iAODTau+1; jAODTau < matchedAODTausFrom45FilterSize; ++jAODTau) {
              if (matchedAODTausFrom45Filter.at(iAODTau).DeltaR(matchedAODTausFrom45Filter.at(jAODTau)) > 0.5) {
                comparePtSum = (matchedAODTausFrom45Filter.at(iAODTau).Pt() + matchedAODTausFrom45Filter.at(jAODTau).Pt());
                if (comparePtSum > highestPtSum) { highestPtSum = comparePtSum; AODTau1Index = iAODTau; AODTau2Index = jAODTau;}
              }
            }
          }
          if (AODTau1Index != -1 && AODTau2Index != -1) {
            AODTau1 = matchedAODTausFrom45Filter.at(AODTau1Index);
            AODTau2 = matchedAODTausFrom45Filter.at(AODTau2Index);
          }
          if (AODTau1Index == -1 || AODTau2Index == -1) matchedHLTTaus = 0;
        }


        if (AODTau1.DeltaR(AODTau2) < 0.5 || AODTau1.Pt() == 0 || AODTau2.Pt() == 0) viableTaus = 0;

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
          //if (AODTau1Pt_ != 0 && AODTau2Pt_ != 0 && isoTauCandsSize >= 2 && passVBFPlusTwoDeepTauHLT) twoGoodViableMatchedTausCount += 1;
        }       

	// check kinematics and ID of jet objects, store jets w pt>=30 and eta<=4.7
	std::vector<TLorentzVector> jetCands;
	for (int iJet = 0; iJet < sizeAODJet; ++iJet){

          bool passJetID = false;
          if (inTree->jetID->at(iJet) >= 2) passJetID = true; // jetID is 2 if it passes loose, and 6 if it passes loose and tight

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

        std::vector<TLorentzVector> HLTJetCands;
        std::vector<std::pair<int,int>> matchedHLTAODJets;
        int HLTJetsSize = inTree->hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20_pt->size();
        if (HLTJetsSize >= 2 && jetCandsSize >= 2) {
          HLTJetCands = hltFillWithCands(inTree, "hltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleHpsDeepTauIsoPFTauHPS20", HLTJetsSize);
          int HLTJetCandsSize = HLTJetCands.size();
          if (HLTJetCandsSize >= 2) {
            for (int iHLTJet = 0; iHLTJet < HLTJetCandsSize; ++iHLTJet) {
              for (int iAODJet = 0; iAODJet < jetCandsSize; ++iAODJet) {
                float dRjets_ = jetCands.at(iAODJet).DeltaR(HLTJetCands.at(iHLTJet));
                if (dRjets_ <= 0.5) {
                  matchedHLTAODJets.push_back(std::make_pair(iHLTJet, iAODJet));
                }
              }
            }
          }
        }
        int matchedHLTAODJetsSize = matchedHLTAODJets.size();
        if (matchedHLTAODJetsSize < 2) matchedHLTJets = 0;

        if (matchedHLTAODJetsSize == 2) {
          AODJet1 = jetCands.at(matchedHLTAODJets.at(0).second);
          AODJet2 = jetCands.at(matchedHLTAODJets.at(1).second);
        }
        
        std::vector<TLorentzVector> matchedAODJets;
        if (matchedHLTAODJetsSize >= 3) {
          for (int iMatchedJet = 0; iMatchedJet < matchedHLTAODJetsSize; ++iMatchedJet) {
            matchedAODJets.push_back(jetCands.at(matchedHLTAODJets.at(iMatchedJet).second));
          }
          // find highest mjj pair
          int AODJet1Index = -1;
          int AODJet2Index = -1;
          std::tie(AODJet1Index, AODJet2Index) = highestMassPairNew(matchedAODJets);
          if (AODJet1Index != -1 and AODJet2Index != -1) {
            AODJet1 = matchedAODJets.at(AODJet1Index);
            AODJet2 = matchedAODJets.at(AODJet2Index);
          }
          if (AODJet1Index == -1 || AODJet2Index == -1) matchedHLTJets = 0;
        }

        if (AODJet1.DeltaR(AODJet2) < 0.5 || AODJet1.Pt() == 0 || AODJet2.Pt() == 0) viableJets = 0;
        if (AODJet1.DeltaR(AODTau1) < 0.5 || AODJet1.DeltaR(AODTau2) < 0.5 || AODJet2.DeltaR(AODTau1) < 0.5 || AODJet2.DeltaR(AODTau2) < 0.5) { viableJets = 0; viableTaus = 0;}

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
        passDiTau32Off = passDiTau34Off = passDiTau35Off = passInclusiveVBFOff = passVBFPlusTwoTauOff = 0;
        if (viableTaus && viableJets) {

          //int dEtajj = abs(AODJet1.Eta() - AODJet2.Eta());
          int offJetInc = 10; // define offline as XX increase of L1 cuts
	  int offTau1Inc = 5;
          int offTau2Inc = 5;
          int offM2Inc = 50;
 

          if (AODJet1Pt_ >= 30 && AODJet2Pt_ >= 30 && mj1j2_ >= 600) {
            if (AODTau1Pt_ >= (32+offTau1Inc) && AODTau2Pt_ >= (32+offTau2Inc) ) passDiTau32Off = 1;
            if (AODTau1Pt_ >= (34+offTau1Inc) && AODTau2Pt_ >= (34+offTau2Inc) ) passDiTau34Off = 1;
            if (AODTau1Pt_ >= (35+offTau1Inc) && AODTau2Pt_ >= (35+offTau2Inc) ) passDiTau35Off = 1;
          }

          // L1 DoubleJet_110_35_DoubleJet35_Mass_Min620
	  if (AODJet1Pt_ >= (110+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= 25 && AODTau2Pt_ >= 25 && mj1j2_ >= 700) passInclusiveVBFOff = 1;
        
          // L1 DoubleJet35_Mass_Min_450_IsoTau45er2p1_RmvOl
          if (AODJet1Pt_ >= (35+offJetInc) && AODJet2Pt_ >= (35+offJetInc) && \
              AODTau1Pt_ >= (45+offTau1Inc) && AODTau2Pt_ >= (20+offTau2Inc) && mj1j2_ >= 600) passVBFPlusTwoTauOff = 1;
          //if (AODJet1Pt_ >= 60 && AODJet2Pt_ >= 60 && AODTau1Pt_ >= 60 && AODTau2Pt_ >= 35 && mj1j2_ >= 700) passVBFPlusTwoTauOff = 1;    
          //if (AODJet1Pt_ >= 100 && AODJet2Pt_ >= 100 && AODTau1Pt_ >= 60 && AODTau2Pt_ >= 35 && mj1j2_ >= 600) passVBFPlusTwoTauOff = 1;    

        } // end viable if statement

        passDiTau32Both = passDiTau34Both = passDiTau35Both = 0;
        passDiTau32Both = (passDiTau32L1DiTau35HLT && passDiTau32Off); // this is the "normal" 35 HLT
        passDiTau34Both = (passDiTau34L1DiTau35HLT && passDiTau34Off); // new proposal, last I heard...
        passDiTau35Both = (passDiTau35L1DiTau35HLT && passDiTau35Off); // this is essentially proposed by CIEMAT

        passDeepDiTau34Both = passDeepDiTau35Both = 0;
        passDeepDiTau34Both = (passDiTau34L1DeepDiTau35HLT && passDiTau34Off);
        passDeepDiTau35Both = (passDiTau35L1DeepDiTau35HLT && passDiTau35Off);

        //---------------------------match AOD and HLT------------------------------//

        // fill branches if any offline selection is passed for AOD
        // fill branches for Old or New HLT objects if they are matched to AOD

        j1_ptAOD = j1_etaAOD = j1_phiAOD = -999;
        j2_ptAOD = j2_etaAOD = j2_phiAOD = mjjAOD = -999;
        t1_ptAOD = t1_etaAOD = t1_phiAOD = -999;
        t2_ptAOD = t2_etaAOD = t2_phiAOD = -999;

        passInclusiveVBFBoth = passVBFPlusTwoTauBoth = passVBFPlusTwoDeepTauBoth = 0;
        passVBF2DTTempLooseBoth = passVBF2DTNoL2NNBoth = passVBF2DTTempLooseNoL2NNBoth = 0;

        passInclusiveVBFBoth = (matchedBothOld && passInclusiveVBFHLT && passInclusiveVBFOff);
        passVBFPlusTwoTauBoth = (matchedBothNew && passVBFPlusTwoTauHLT && passVBFPlusTwoTauOff);
        passVBFPlusTwoDeepTauBoth = (matchedHLTTaus && matchedHLTJets && passVBFPlusTwoDeepTauHLT && passVBFPlusTwoTauOff);

        matchedHLTTaus_TempLoose = matchedHLTJets_TempLoose = 1;
        passVBF2DTTempLooseBoth = (matchedHLTTaus_TempLoose && matchedHLTJets_TempLoose && passVBF2DTTempLooseHLT && passVBFPlusTwoTauOff);
        passVBF2DTNoL2NNBoth = (matchedHLTTaus && matchedHLTJets && passVBF2DTNoL2NNHLT && passVBFPlusTwoTauOff);
        passVBF2DTTempLooseNoL2NNBoth = (matchedHLTTaus_TempLoose && matchedHLTJets_TempLoose && passVBF2DTTempLooseNoL2NNHLT && passVBFPlusTwoTauOff);

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
