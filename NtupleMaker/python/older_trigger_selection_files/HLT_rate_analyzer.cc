#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <iomanip>
#include <tuple>
#include <set>

#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include "trigger_tree.h"
#include "trigger_functions.h"

// example running on wisc server: ./trigger_selection.exe /hdfs/store/user/ballmond/merged_trigger_05092020/merged.root ./output.root new
// temporary file location for rate studies
// /uscms/home/ballmond/nobackup/test-dir/CMSSW_11_3_4_patch1/src/VBFTau/NtupleMaker/python/samples/fullEZB1SelectedRuns.root 1 thru 8

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

    // Final HLT filter variables and branches
    double j1_pt, j1_eta, j1_phi, j1_energy;
    double j2_pt, j2_eta, j2_phi, j2_energy;
    double mjj;
    double t1_pt, t1_eta, t1_phi, t1_energy;
    double t2_pt, t2_eta, t2_phi, t2_energy;
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

    // path for old trigger
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

    // path for new trigger
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

    // final HLT decisions (decision found separately in NtupleMaker than filter path above)
    int passInclusiveVBFHLT;
    int passVBFPlusTwoTauHLT;
    outTree->Branch("passInclusiveVBFHLT", &passInclusiveVBFHLT);
    outTree->Branch("passVBFPlusTwoTauHLT", &passVBFPlusTwoTauHLT);


    // variables without branches
    int passDiTau32L1 = 0;
    int passDiTau32L1Count = 0;
    int passDiTau35L1 = 0;
    int passDiTau35L1Count = 0;
    int passInclusiveVBFL1Count = 0;
    int passInclusiveVBFHLTCount = 0;
    int passVBFPlusTwoTauL1Count = 0;
    int passVBFPlusTwoTauHLTCount = 0;

    int passORDiTau32InclusiveProposed = 0;
    int passORDiTau35InclusiveProposed = 0;
    int passORDiTau32Inclusive = 0;
    int passORDiTau35Inclusive = 0;

    std::set<std::pair<int,int>> uniqueLumiBlocks;
    int eventsInRun = 0;
    int rateRunNumber = -1;
    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 200001; ++iEntry) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	//if (iEntry % 1000000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

        // can choose from 321755,323725,323755,323790,323841,323940,323976,323978,
        // 324021,324077,324201,324237,324245,324293,324315,324420,324747,324785,
        // 324835,324897,324970,324980,324997,325022,325057,325097-325099
        // in prinicple. Use 323755 for now since that's what we've used before
        //
        rateRunNumber = 323755;
        if (runNumber != rateRunNumber) continue;
        bool restrictLumi = true;
        if (restrictLumi && (lumiBlock < 44 || lumiBlock >= 144)) continue;
        uniqueLumiBlocks.insert(std::make_pair(runNumber,lumiBlock));
        eventsInRun += 1;

        // fill Old VBF HLT filter flags after correcting NtupleMaker mistake
        passhltL1VBFDiJetOR = passhltHpsDoublePFTau20Old = passhltHpsDoublePFTau20TrackTightChargedIsoOld = 0;
        passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld = passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;

        passhltL1VBFDiJetOR = inTree->passhltL1VBFDiJetOR;
        if (passhltL1VBFDiJetOR) passhltHpsDoublePFTau20Old = inTree->passhltHpsDoublePFTau20;
        if (passhltHpsDoublePFTau20Old) passhltHpsDoublePFTau20TrackTightChargedIsoOld = inTree->passhltHpsDoublePFTau20TrackTightChargedIso;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoOld) passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld = inTree->passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonOld) passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = inTree->passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;
        if (passhltMatchedVBFTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20) passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = inTree->passhltMatchedVBFOnePFJet2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;

        passInclusiveVBFHLT = inTree->passInclusiveVBFHLT;
        passInclusiveVBFL1Count += passhltL1VBFDiJetOR;
        passInclusiveVBFHLTCount += passInclusiveVBFHLT;


        // fill New VBF HLT filter flags after correcting NtupleMaker mistake
        passhltL1VBFDiJetIsoTau = passhltHpsDoublePFTau20New = passhltHpsDoublePFTau20TrackTightChargedIsoNew = 0;
        passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew = passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched = passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = 0;

        passhltL1VBFDiJetIsoTau = inTree->passhltL1VBFDiJetIsoTau;
        if (passhltL1VBFDiJetIsoTau) passhltHpsDoublePFTau20New = inTree->passhltHpsDoublePFTau20;
        if (passhltHpsDoublePFTau20New) passhltHpsDoublePFTau20TrackTightChargedIsoNew = inTree->passhltHpsDoublePFTau20TrackTightChargedIso;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoNew) passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew = inTree->passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuon;
        if (passhltHpsDoublePFTau20TrackTightChargedIsoAgainstMuonNew) passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched = inTree->passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched;
        if (passhltHpsPFTau45TrackPt1TightChargedIsolationL1HLTMatched) passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20 = inTree->passhltMatchedVBFIsoTauTwoPFJets2CrossCleanedFromDoubleTightChargedIsoPFTauHPS20;

        passVBFPlusTwoTauHLT = inTree->passVBFPlusTwoTauHLT;
        passVBFPlusTwoTauL1Count += passhltL1VBFDiJetIsoTau;
        passVBFPlusTwoTauHLTCount += passVBFPlusTwoTauHLT;

        passDiTau32L1 = passDiTau35L1 = 0;
        passDiTau32L1 = inTree->passhltL1sDoubleTauBigOR;
        int sizeL1DiTau32 = 0;
        int sizeL1DiTau35 = 0;
        if (passDiTau32L1) sizeL1DiTau32 = inTree->hltL1sDoubleTauBigOR_pt->size();
        if (sizeL1DiTau32 >= 2) {
          for (int iTau = 0; iTau < sizeL1DiTau32; ++iTau) {
            if (inTree->hltL1sDoubleTauBigOR_pt->at(iTau) >= 35) sizeL1DiTau35 += 1;
          }
          if (sizeL1DiTau35 >= 2) passDiTau35L1 = 1; 
        }

        passDiTau32L1Count += passDiTau32L1;
        passDiTau35L1Count += passDiTau35L1;

        // inclusive VBF L1 = passhltL1VBFDiJetOR
        // proposed/new VBF L1 = passhltL1VBFDiJetIsoTau
        if (passDiTau32L1 || passhltL1VBFDiJetOR || passhltL1VBFDiJetIsoTau) passORDiTau32InclusiveProposed += 1;
        if (passDiTau32L1 || passhltL1VBFDiJetOR) passORDiTau32Inclusive += 1;

        if (passDiTau35L1 || passhltL1VBFDiJetOR || passhltL1VBFDiJetIsoTau) passORDiTau35InclusiveProposed += 1;
        if (passDiTau35L1 || passhltL1VBFDiJetOR) passORDiTau35Inclusive += 1;

        outTree->Fill();

    }// end event loop

    std::cout << "Total dataset has " << inTree->GetEntries() << " events" << std::endl;

    std::cout << rateRunNumber << '\t' << "run number" << '\n'
              << eventsInRun << '\t' << "events in run" << '\n'
              << uniqueLumiBlocks.size() << '\t' << "number of unique lumi blocks" << '\n'
              << std::endl;

    std::cout << "from OMS, lumi at LS = 44 is 1.849E34 and drops by 4\% after 100 LS (at 143 it is 1.775E34)" << std::endl;
    std::cout << "this makes the avg lumi = 1.812E34, which is what is used as the denominator lumi in the scaling" << std::endl;
    float rateFactor = 2544 * 11255.6 * (2.0 / 1.812) * (1 / float(eventsInRun)); // using avg lumi from OMS, 2.0E34 is ~60PU
    std::cout << rateFactor << '\t' << "rate factor" << std::endl;

    std::cout << 
              "L1" << '\t' << "L1 Rate" << '\t' << "HLT" << '\n' << 
              passDiTau32L1Count << '\t' << passDiTau32L1Count*rateFactor << '\t' << "DiTau 32" << '\n' <<
              passDiTau35L1Count << '\t' << passDiTau35L1Count*rateFactor << '\t' << "DiTau 35" << '\n' <<
              passInclusiveVBFL1Count << '\t' << passInclusiveVBFL1Count*rateFactor << '\t' << passInclusiveVBFHLTCount << '\t' << "Old VBF" << '\n' <<
              passVBFPlusTwoTauL1Count << '\t' << passVBFPlusTwoTauL1Count*rateFactor << '\t' << passVBFPlusTwoTauHLTCount << '\t' << "New VBF" << '\n' <<
    std::endl; 

    int pureProposedFromDiTau32 = passORDiTau32InclusiveProposed - passORDiTau32Inclusive;
    int pureProposedFromDiTau35 = passORDiTau35InclusiveProposed - passORDiTau35Inclusive;
    std::cout << 
              "3OR -" << '\t' << "2OR" << '\t' << "=" << '\t' << "pure New VBF L1" << '\t' << "-->" << '\t' << "Pure rate" << '\n' <<
              passORDiTau32InclusiveProposed << '\t' << passORDiTau32Inclusive << '\t' << '\t' << pureProposedFromDiTau32 << '\t' << '\t' <<
              pureProposedFromDiTau32*rateFactor << '\n' << 
              passORDiTau35InclusiveProposed << '\t' << passORDiTau35Inclusive << '\t' << '\t' << pureProposedFromDiTau35 << '\t' << '\t' <<
              pureProposedFromDiTau35*rateFactor << '\n' << 
    std::endl;

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();


    outTree->Write();
    fOut->Close();
    return 0;
}
