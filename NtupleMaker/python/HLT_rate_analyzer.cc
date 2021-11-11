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
    int passOldVBFL1Count = 0;
    int passOldVBFHLTCount = 0;
    int passNewVBFL1Count = 0;
    int passNewVBFHLTCount = 0;

    // Event Loop
    // for-loop of fewer events is useful to test code without heavy I/O to terminal from cout statements
    //for (int iEntry = 0; iEntry < 10001; ++iEntry) {
    for (int iEntry = 0; iEntry < inTree->GetEntries(); ++iEntry) {
	inTree->GetEntry(iEntry);
	//if (iEntry % 1000000 == 0) std::cout << std::to_string(iEntry) << std::endl;

	nEvents = inTree->nEvents;
	runNumber = inTree->runNumber;
	lumiBlock = inTree->lumiBlock;
	eventNumberID = inTree->eventNumberID;

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

        outTree->Fill();

    }// end event loop

    std::cout << "From " << inTree->GetEntries() << " events" << std::endl;
    std::cout << 
              "L1" << '\t' << "HLT" << '\n' << 
              passOldVBFL1Count << '\t' << passOldVBFHLTCount << '\t' << "Old VBF" << '\n' <<
              passNewVBFL1Count << '\t' << passNewVBFHLTCount << '\t' << "New VBF" << '\n' <<
    std::endl; 

    std::string outputFileName = outName;
    TFile *fOut = TFile::Open(outputFileName.c_str(),"RECREATE");
    fOut->cd();


    outTree->Write();
    fOut->Close();
    return 0;
}
